#ifndef SEGYFILE
#define SEGYFILE

#include "types.h"
#include "utils.h"
#include "itracedataheaderfile.h"
#include "iheaderfile.h"
#include "segyheader.h"
#include "segytraceheader.h"
#include "loadstrategies.h"
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include "cache.h"
#include "tetraka.h"

template <class TraceElementType=TraceElement,class TraceCacheType=LruCache<long long, std::vector<TraceElementType> >,class TraceHeaderCacheType=LruCache<long long, SegyTraceHeader>>
class SegyFile :public IHeaderFile, public ITraceDataHeaderFile<std::vector<TraceElementType> >,public IObserver
{	

public:
	typedef std::vector<TraceElementType> Trace;
	typedef std::shared_ptr< std::vector<TraceElementType> > TracePtr;
	typedef std::shared_ptr<const std::vector<TraceElementType> > TraceConstPtr;

	SegyFile(const FieldMapper segyHeaderMapper = FieldMapper(), const FieldMapper segyTraceHeaderMapper = FieldMapper()):
        _isOpen(false)
	{
		initHeaderMapper(segyHeaderMapper);
        initTraceHeaderMapper(segyTraceHeaderMapper);
        _traceCache.addObserver(this);
        _headerCache.addObserver(this);
	}

    SegyFile(String path,String mode="rw", const FieldMapper segyHeaderMapper = FieldMapper(), const FieldMapper segyTraceHeaderMapper = FieldMapper(), Endian endian = Endian::ENDIAN_BIG):
        _isOpen(false)
	{
		initHeaderMapper(segyHeaderMapper);
		initTraceHeaderMapper(segyTraceHeaderMapper);
        _traceCache.addObserver(this);
        _headerCache.addObserver(this);
		openFile(path, mode, endian);
	}

	virtual ~SegyFile(){
		fflush();
	}


    virtual void openFile(String path, String mode = "rw", Endian endian = Endian::ENDIAN_BIG){
		if (isOpen())throw;
        _endian = (endian == Endian::ENDIAN_UNDEFINED) ? Endian::ENDIAN_BIG : endian;
		if (mode == "w") _mode = Mode(false, true);
		else if (mode == "r")_mode = Mode(true, false);
		else if (mode == "rw" || mode == "wr") _mode = Mode(true, true);
		else _mode = Mode(true, true);
		
		_file.reset(new std::fstream(path,std::fstream::binary | std::fstream::in | (_mode.write ? std::fstream::out : std::fstream::binary)));
		if (!_file->good()){
			throw;
		}
		_isOpen = true;
		_file->seekg(0, std::ios_base::beg);

		//Считывание ebcidic заголовка
		_file->read(_ebcidicHeader, 3200);
		ebcdicToAscii((unsigned char*)_ebcidicHeader, (unsigned char*)_ebcidicHeader, 3200);

		//Считывание заголовка файла
		readHeader(_header);
        _format = (Format)boost::any_cast<int>(_header.get(SegyHeader::type));
        _sampleCount = boost::any_cast<int>(_header.get(SegyHeader::sampleCount));

		//Рассчет количества трасс
		_file->seekg(0, std::ios_base::end);
		long long pos = _file->tellg();
		_totalTraceCount = perfomSegyTraceCount(pos, _sampleCount, getFormatSize(_format));
	}

    virtual void closeFile(){
		fflush();
		_traceCache.clear();
		_headerCache.clear();
        _changedTraces.clear();
        _changedTraceHeaders.clear();
		_file.reset();
		_isOpen = false;
	}

    virtual bool isOpen()const{
		return _isOpen;
	}

	//Устанавливает маппер для заголовка segy файла
    virtual void setHeaderMapper(const FieldMapper& mapper){
		this->_headerMapper = mapper;
		if (isOpen())
			this->readHeader(_header);
	}
	//Устанавливает маппер для заголовков трасс segy файлов
    virtual void setTraceHeaderMapper(const FieldMapper& mapper){
		fflushHeaders();
		_headerCache.clear();
		initTraceHeaderMapper(mapper);
	}
	//Запись изменений в файл
    virtual void fflush(){
		fflushHeaders();
		fflushTraces();
	}
	//Возвращает ebcidic заголовок
    virtual const char* getEbcidicHeader()const{
		return _ebcidicHeader;
	}
	//Возвращает количество сэмплов в каждой трассе
    virtual int getSampleCount()const{
		return _sampleCount;
	}

	//Создание segy файла
	static SegyFile<TraceElementType>* createSegy(String path, const char* ebcidicHeader, const SegyHeader header, const Endian endian, const FieldMapper * mapper=0){
        //if (tetraka::isFileExist(path.c_str()))throw;
		std::fstream f(path, std::fstream::out | std::fstream::binary);

		f.seekg(0, std::ios_base::beg);

		if (ebcidicHeader != 0)f.write(ebcidicHeader, ebcidicHeaderSize);

		byte buff[lineHeaderSize];
		memset(buff, 0, lineHeaderSize);

        FieldMapper mmapper=SegyHeader::mapperInfo;
        //if (mapper == 0){
        //    mmapper = SegyHeader::mapperInfo;
        //}
        if(mapper!=0){
			mmapper = *mapper;
        }

        segyHeaderToBinary(header, mmapper, endian,(char*) buff);

		f.seekg(ebcidicHeaderSize, std::ios_base::beg);
		f.write((char*)buff, lineHeaderSize);

		f.close();

		return new SegyFile<TraceElementType>(path,"rw", mmapper, FieldMapper(), endian);
	}

	//IHeader interface
public:
	//Возвращает заголовок файла
	virtual const SegyHeader& getHeader()const{
		return _header;
	}
	//Задаёт заголовок файла
	virtual bool setHeader(const IHeader& header){
		_header = dynamic_cast<const SegyHeader&>(header);
		writeHeaderToFile(_header);
		return true;
	}

	//ITraceFile interface
public:
	//Возвращает количество трасс
	virtual long long getTraceCount()const{
		return _totalTraceCount;
	}

	//ITraceDataFile interface
public:
	//Возвращает трассу
	virtual TraceConstPtr getTrace(long long traceNum)const{
		if (!_mode.read) throw;
		if (_traceCache.hasElement(traceNum))return _traceCache.get(traceNum);

		std::shared_ptr<Trace> tracePtr = std::shared_ptr<Trace>(new Trace(_sampleCount, 0));
		readTrace(traceNum, *(tracePtr.get()));
		_traceCache.add(traceNum, tracePtr);
		return tracePtr;
	}
	//Задаёт значение трассы
	virtual bool setTrace(long long traceNum, const Trace& trace){
		if (!_mode.write) return false;
		_traceCache.add(traceNum, std::shared_ptr<Trace>(new Trace(trace)));
		_changedTraces.insert(traceNum);
		return true;
	}

	//ITraceHeaderFile interface
public:
	//Возвращает заголовок трассы
	virtual const SegyTraceHeader& getTraceHeader(long long traceNum)const{
		if (!_mode.read) throw;
		if (_headerCache.hasElement(traceNum)) return *_headerCache.get(traceNum).get();

		std::shared_ptr<SegyTraceHeader> sh = std::shared_ptr<SegyTraceHeader>(new SegyTraceHeader());
		readTraceHeader(traceNum, *sh.get());
		_headerCache.add(traceNum, sh);
		return *_headerCache.get(traceNum).get();
	}
	//Задаёт заголовок трассы
	virtual bool setTraceHeader(long long traceNum, const IHeader& traceHeader){
		if (!_mode.write) return false;
		const SegyTraceHeader& segth = dynamic_cast<const SegyTraceHeader&>(traceHeader);
		std::shared_ptr<SegyTraceHeader> sth=std::shared_ptr<SegyTraceHeader>(new SegyTraceHeader(segth));
		_headerCache.add(traceNum, sth);
		_changedTraceHeaders.insert(traceNum);
		return true;
	}

	//IObserver interface
public:
	virtual void handleEvent(){
		if (_changedTraces.size() > 0 && _traceCache.deletedSize() > 0){
			std::vector<long long> keys = _traceCache.getDeletedElements();
			for (size_t i = 0; i < keys.size(); ++i){
                if(!_traceCache.hasElement(keys[i])){
                    fflushTrace(keys[i]);
                }
			}
		}
		if (_changedTraceHeaders.size() > 0 && _headerCache.deletedSize() > 0){
			std::vector<long long> keys = _headerCache.getDeletedElements();
			for (size_t i = 0; i < keys.size(); ++i){
                if(!_headerCache.hasElement(keys[i])){
                    fflushTraceHeader(keys[i]);
                }
			}
		}
	}

public:
	static const int ebcidicHeaderSize = 3200;
	static const int lineHeaderSize = 400;
	static const int traceHeaderSize = 240;

protected:
#ifdef TESTING
public:
#endif
	//Проверяет корректность номера трассы
	bool isValidTraceNum(long long traceNum)const{
		return traceNum < getTraceCount();
	}
	
	bool isTraceChanged(long long traceNum)const{
        std::set<long long>::const_iterator it = std::find(_changedTraces.begin(), _changedTraces.end(), traceNum);
		return (it != _changedTraces.end());
	}

	bool isTraceHeaderChanged(long long traceNum)const{
        std::set<long long>::const_iterator it = std::find(_changedTraceHeaders.begin(), _changedTraceHeaders.end(), traceNum);
		return (it != _changedTraceHeaders.end());
	}

	void fflushTrace(long long traceNum)const{
		if (_changedTraces.count(traceNum)){
            if(_traceCache.hasElement(traceNum)){
                writeTraceToFile(traceNum, *_traceCache.get(traceNum).get());
            }else if(_traceCache.hasDeletedElement(traceNum)){
                 writeTraceToFile(traceNum, *_traceCache.getDeleted(traceNum).get());
            }
			_changedTraces.erase(traceNum);
		}
	}

	void fflushTraceHeader(long long traceNum)const{
        if (_changedTraceHeaders.count(traceNum)){
            if(_headerCache.hasElement(traceNum)){
                writeTraceHeaderToFile(traceNum, *_headerCache.get(traceNum).get());
            }else if(_headerCache.hasDeletedElement(traceNum)){
                writeTraceHeaderToFile(traceNum, *_headerCache.getDeleted(traceNum).get());
            }
            _changedTraceHeaders.erase(traceNum);
        }
	}
	
	//Запись измененных трасс на диск
	void fflushTraces()const{
		std::set<long long>::iterator it;
		for (it = _changedTraces.begin(); it != _changedTraces.end(); ++it){
			writeTraceToFile(*it, *_traceCache.get(*it).get());
		}
		_traceCache.clear();
	}
	//Запись изменных заголовков трасс на диск
	void fflushHeaders()const{
		std::set<long long>::iterator it;
		for (it = _changedTraceHeaders.begin(); it != _changedTraceHeaders.end(); ++it){
			writeTraceHeaderToFile(*it, *_headerCache.get(*it).get());
		}
		_headerCache.clear();
	}

	void initHeaderMapper(const FieldMapper& segyHeaderMapper){
		_headerMapper = SegyHeader::mapperInfo;
		for (FieldMapper::const_iterator it = segyHeaderMapper.begin(); it != segyHeaderMapper.end(); ++it){
			if (_headerMapper.count(it->first) > 0)_headerMapper[it->first] = it->second;
		}
	}

	void initTraceHeaderMapper(const FieldMapper& segyTraceHeaderMapper){
		_traceHeaderMapper = SegyTraceHeader::mapperInfo;

		for (FieldMapper::const_iterator it = segyTraceHeaderMapper.begin(); it != segyTraceHeaderMapper.end(); ++it){
			if (_traceHeaderMapper.count(it->first) > 0)_traceHeaderMapper[it->first] = it->second;
		}
	}

	void readHeader(SegyHeader& header)const{
		if (!isOpen())throw;
		_file->seekg(ebcidicHeaderSize, std::ios_base::beg);
		unsigned char *buff = new unsigned char[lineHeaderSize];
		std::shared_ptr<unsigned char> buffS(buff);
		_file->read((char*)buff, lineHeaderSize);

		const std::vector<std::string>& fields = header.getFieldNames();

        for (size_t i = 0; i < fields.size(); ++i){
            header.set(fields[i],bytesToSignedInt(buff + _headerMapper.at(fields[i]).startPos, _headerMapper.at(fields[i]).length, _endian));
		}
	}

	void readTraceHeader(long long traceNum,SegyTraceHeader& traceHeader)const{
		if (!isOpen() && !isValidTraceNum(traceNum))throw;
		_file->seekg(getTraceOffset(traceNum), std::fstream::beg);
		unsigned char *buff = new unsigned char[traceHeaderSize];
		std::shared_ptr<unsigned char> buffS(buff);
		_file->read((char*)buff, traceHeaderSize);

		const std::vector < std::string>& fields = traceHeader.getFieldNames();
        for (size_t i = 0; i < fields.size(); ++i){
            traceHeader.set(fields[i],bytesToSignedInt(buff + _traceHeaderMapper.at(fields[i]).startPos, _traceHeaderMapper.at(fields[i]).length, _endian));
		}
	}

	void readTrace(long long traceNum, Trace& trace)const{
		if (!isOpen() && !isValidTraceNum(traceNum))throw;
		_file->seekg(getTraceOffset(traceNum) + traceHeaderSize, std::fstream::beg);
		int formatSize = getFormatSize(_format);
		int length =  getSampleCount();
		unsigned char *buff = new unsigned char[formatSize*length];
		std::shared_ptr<unsigned char> buffS(buff);//Warning!
		_file->read((char*)buff, formatSize*length);

		for (int i = 0; i<length; ++i)
			trace[i] = bytesToDouble(buff + i*(formatSize), _format, _endian);
	}

	void writeTraceToFile(long long traceNum, const Trace& trace)const{
		if (!isOpen()&&!_mode.write)throw;
		int formatSize = getFormatSize(_format), sampleCount = getSampleCount();
		std::shared_ptr<char> traceBuf(new char[sampleCount*formatSize]);
		for (int i = 0; i < sampleCount; ++i){
			doubleToBytes(trace[i], (byte*)traceBuf.get() + i*formatSize, _format, _endian);
		}
		_file->seekg(getTraceOffset(traceNum)+traceHeaderSize, std::fstream::beg);
		_file->write(traceBuf.get(), sampleCount*formatSize);
	}

	void writeTraceHeaderToFile(long long trace, const SegyTraceHeader& header)const{
		if (!isOpen()&&!_mode.write)throw;
		std::shared_ptr<char> headerBuff(new char[traceHeaderSize]);
		segyTraceHeaderToBinary(header, _traceHeaderMapper, _endian, headerBuff.get());
		_file->seekg(getTraceOffset(trace), std::fstream::beg);
		_file->write(headerBuff.get(), traceHeaderSize);
	}

	void writeHeaderToFile(const SegyHeader& header)const{
		if (!isOpen()&&!_mode.write)throw;
		std::shared_ptr<char> headerBuff(new char[traceHeaderSize]);
		segyHeaderToBinary(header, _headerMapper, _endian, headerBuff.get());
		_file->seekg(ebcidicHeaderSize, std::fstream::beg);
		_file->write(headerBuff.get(), lineHeaderSize);
	}

	static void segyTraceHeaderToBinary(const SegyTraceHeader& header, FieldMapper mapper, Endian endian, char* buff){
		std::fill(buff, buff + traceHeaderSize, 0);
		const std::vector<std::string>& fields = header.getFieldNames();
        for (size_t i = 0; i < fields.size(); ++i){
            intToBytesSignedInt(boost::any_cast<int>(header.get(fields[i])), (byte*)buff + mapper.find(fields[i])->second.startPos, mapper.find(fields[i])->second.length, endian);
		}
	}

	static void segyHeaderToBinary(const SegyHeader& header,FieldMapper mapper,Endian endian, char* buff){
		std::fill(buff, buff + traceHeaderSize, 0);
		const std::vector<std::string>& fields = header.getFieldNames();
        for (size_t i = 0; i < fields.size(); ++i){
            intToBytesSignedInt(boost::any_cast<int>(header.get(fields[i])), (byte*)buff + mapper.find(fields[i])->second.startPos, mapper.find(fields[i])->second.length, endian);
		}
	}

	long long getTraceOffset(long long trace)const{
		long long traceLength = getSampleCount()*getFormatSize(_format);
		return ebcidicHeaderSize + lineHeaderSize + trace*(traceHeaderSize + traceLength);
	}

protected:
#ifdef TESTING
public:
#endif
	struct Mode{
		bool read, write;
		Mode() :read(true), write(true){}
		Mode(bool r, bool w) :read(r), write(w){ }
	};

	mutable std::shared_ptr < std::fstream> _file;
	bool _isOpen;
	Mode _mode;
	long long _totalTraceCount;
	int _sampleCount;
	char _ebcidicHeader[3200];
    //mutable LruCache<long long, Trace> _traceCache;
    //mutable LruCache<long long, SegyTraceHeader> _headerCache;
    mutable TraceCacheType _traceCache;
    mutable TraceHeaderCacheType _headerCache;
	mutable std::set<long long> _changedTraces;
	mutable std::set<long long> _changedTraceHeaders;

	Endian _endian;	
	Format _format;
	FieldMapper _headerMapper;
	FieldMapper _traceHeaderMapper;
	SegyHeader _header;
};


#endif
