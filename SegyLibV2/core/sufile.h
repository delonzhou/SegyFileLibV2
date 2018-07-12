#ifndef SUFILE_H
#define SUFILE_H

#include "types.h"
#include "utils.h"
#include "itracedataheaderfile.h"
#include "iheaderfile.h"
#include "sutraceheader.h"
#include "loadstrategies.h"
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include "cache.h"
#include "tetraka.h"

template <class TraceElementType=TraceElement,class TraceCacheType=LruCache<long long, std::vector<TraceElementType> >,class TraceHeaderCacheType=LruCache<long long, SuTraceHeader>>
class SuFile :public ITraceDataHeaderFile<std::vector<TraceElementType> >,public IObserver
{

public:
    typedef std::vector<TraceElementType> Trace;
    typedef std::shared_ptr< std::vector<TraceElementType> > TracePtr;
    typedef std::shared_ptr<const std::vector<TraceElementType> > TraceConstPtr;

    SuFile(const FieldMapper suTraceHeaderMapper = FieldMapper()):
        _isOpen(false)
    {
        initTraceHeaderMapper(suTraceHeaderMapper);
        _traceCache.addObserver(this);
        _headerCache.addObserver(this);
    }

    SuFile(String path,size_t sampleCount,String mode="rw", const FieldMapper suTraceHeaderMapper = FieldMapper(),Format format=Format::FORMAT_IBM, Endian endian = Endian::ENDIAN_BIG):
        _isOpen(false)
    {
        initTraceHeaderMapper(suTraceHeaderMapper);
        _traceCache.addObserver(this);
        _headerCache.addObserver(this);
        openFile(path, sampleCount, mode,format, endian);
    }

    virtual ~SuFile(){
        fflush();
    }


    void openFile(String path, size_t sampleCount, String mode = "rw", Format format=Format::FORMAT_IBM, Endian endian = Endian::ENDIAN_BIG){
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


        _format = format;
        _sampleCount = sampleCount;


        _file->seekg(0, std::ios_base::end);
        long long pos = _file->tellg();
        _totalTraceCount = perfomSuTraceCount(pos, _sampleCount, getFormatSize(_format));
    }

    void closeFile(){
        fflush();
        _traceCache.clear();
        _headerCache.clear();
        _changedTraces.clear();
        _changedTraceHeaders.clear();
        _file.reset();
        _isOpen = false;
    }
    //
    bool isOpen()const{
        return _isOpen;
    }


    void setTraceHeaderMapper(const FieldMapper& mapper){
        fflushHeaders();
        _headerCache.clear();
        initTraceHeaderMapper(mapper);
    }

    void fflush(){
        fflushHeaders();
        fflushTraces();
    }

    int getSampleCount()const{
        return _sampleCount;
    }


    static SuFile<TraceElementType>* createSu(String path, size_t sampleCount, Format format, const Endian endian, const FieldMapper * mapper=0){
        //if (tetraka::isFileExist(path.c_str()))throw;
        std::fstream f(path, std::fstream::out | std::fstream::binary);
        f.seekg(0, std::ios_base::beg);
        f.close();

        FieldMapper mmapper;
        if (mapper == 0){
            mmapper = SuTraceHeader::mapperInfo;
        }
        else{
            mmapper = *mapper;
        }

        return new SuFile<TraceElementType>(path, sampleCount, "rw", mmapper, format, endian);
    }

    //ITraceFile interface
public:

    virtual long long getTraceCount()const{
        return _totalTraceCount;
    }

    //ITraceDataFile interface
public:

    virtual TraceConstPtr getTrace(long long traceNum)const{
        if (!_mode.read) throw;
        if (_traceCache.hasElement(traceNum)) return _traceCache.get(traceNum);

        std::shared_ptr<Trace> tracePtr = std::shared_ptr<Trace>(new Trace(_sampleCount, 0));
        readTrace(traceNum, *(tracePtr.get()));
        _traceCache.add(traceNum, tracePtr);
        return tracePtr;
    }

    virtual bool setTrace(long long traceNum, const Trace& trace){
        if (!_mode.write) return false;
        _traceCache.add(traceNum, std::shared_ptr<Trace>(new Trace(trace)));
        _changedTraces.insert(traceNum);
        return true;
    }

    //ITraceHeaderFile interface
public:

    virtual const SuTraceHeader& getTraceHeader(long long traceNum)const{
        if (!_mode.read) throw;
        if (_headerCache.hasElement(traceNum)) return *_headerCache.get(traceNum).get();

        std::shared_ptr<SuTraceHeader> sh = std::shared_ptr<SuTraceHeader>(new SuTraceHeader());
        readTraceHeader(traceNum, *sh.get());
        _headerCache.add(traceNum, sh);
        return *_headerCache.get(traceNum).get();
    }

    virtual bool setTraceHeader(long long traceNum, const IHeader& traceHeader){
        if (!_mode.write) return false;
        const SuTraceHeader& segth = dynamic_cast<const SuTraceHeader&>(traceHeader);
        std::shared_ptr<SuTraceHeader> sth=std::shared_ptr<SuTraceHeader>(new SuTraceHeader(segth));
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
                //if(!_traceCache.hasElement(keys[i])){
                    fflushTrace(keys[i]);
                //}
            }
        }
        if (_changedTraceHeaders.size() > 0 && _headerCache.deletedSize() > 0){
            std::vector<long long> keys = _headerCache.getDeletedElements();
            for (size_t i = 0; i < keys.size(); ++i){
                //if(!_headerCache.hasElement(keys[i])){
                    fflushTraceHeader(keys[i]);
                //}
            }
        }
    }

public:
    static const int traceHeaderSize = 240;

protected:
#ifdef TESTING
public:
#endif
    //��������� ������������ ������ ������
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


    void fflushTraces()const{
        std::set<long long>::iterator it;
        for (it = _changedTraces.begin(); it != _changedTraces.end(); ++it){
            writeTraceToFile(*it, *_traceCache.get(*it).get());
        }
        _traceCache.clear();
    }

    void fflushHeaders()const{
        std::set<long long>::iterator it;
        for (it = _changedTraceHeaders.begin(); it != _changedTraceHeaders.end(); ++it){
            writeTraceHeaderToFile(*it, *_headerCache.get(*it).get());
        }
        _headerCache.clear();
    }

    void initTraceHeaderMapper(const FieldMapper& SuTraceHeaderMapper){
        _traceHeaderMapper = SuTraceHeader::mapperInfo;

        for (FieldMapper::const_iterator it = SuTraceHeaderMapper.begin(); it != SuTraceHeaderMapper.end(); ++it){
            if (_traceHeaderMapper.count(it->first) > 0)_traceHeaderMapper[it->first] = it->second;
        }
    }

    void readTraceHeader(long long traceNum,SuTraceHeader& traceHeader)const{
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

    void writeTraceHeaderToFile(long long trace, const SuTraceHeader& header)const{
        if (!isOpen()&&!_mode.write)throw;
        std::shared_ptr<char> headerBuff(new char[traceHeaderSize]);
        suTraceHeaderToBinary(header, _traceHeaderMapper, _endian, headerBuff.get());
        _file->seekg(getTraceOffset(trace), std::fstream::beg);
        _file->write(headerBuff.get(), traceHeaderSize);
    }

    static void suTraceHeaderToBinary(const SuTraceHeader& header, FieldMapper mapper, Endian endian, char* buff){
        std::fill(buff, buff + traceHeaderSize, 0);
        const std::vector<std::string>& fields = header.getFieldNames();
        for (size_t i = 0; i < fields.size(); ++i){
            intToBytesSignedInt(boost::any_cast<int>(header.get(fields[i])), (byte*)buff + mapper.find(fields[i])->second.startPos, mapper.find(fields[i])->second.length, endian);
        }
    }

    long long getTraceOffset(long long trace)const{
        long long traceLength = getSampleCount()*getFormatSize(_format);
        return trace*(traceHeaderSize + traceLength);
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
};


#endif // SUFILE_H
