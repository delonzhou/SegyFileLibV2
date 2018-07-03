#ifndef LOADSTRATEGIES_H
#define LOADSTRATEGIES_H

#include <list>
#include <algorithm>

class ITraceStrategy{
public:
	virtual bool canAppendTrace(long long traceNum)=0;//Можно ли загрузить трассу traceNum без отгрузки других трасс
    virtual bool canLoadTrace(long long traceNum)=0;//Можно ли загрузить трассу даже если придётся отгрузить другие трассы
    virtual void loadTrace(long long traceNum)=0;//Вызывается, что бы уведомить, что трасса была загружена
    virtual long long getUnloadTrace()=0;//Возвращает трассу, которую следует отгрузить, если таковой нет возвращает -1
    virtual void clear()=0; //Очищает список загруженных трасс
	virtual ~ITraceStrategy() {}
};

class OneTraceStrategy:public ITraceStrategy{
public:
    OneTraceStrategy();
	bool canAppendTrace(long long traceNum);
	bool canLoadTrace(long long traceNum);
	void loadTrace(long long traceNum);
	long long getUnloadTrace();
    void clear();
private:
	long long _loadedTrace;
	long long _unloadTrace;
};

template<long long traceCount>
class MultipleTraceStrategy:public ITraceStrategy{
public:
	MultipleTraceStrategy() :_unloadTrace(-1){}
	bool canAppendTrace(long long traceNum){
		return _loadedTraces.size()<traceCount;
	}
	bool canLoadTrace(long long traceNum){
		return true;
	}
	void loadTrace(long long traceNum){
		std::list<long long>::iterator it = std::find(_loadedTraces.begin(), _loadedTraces.end(), traceNum);

		if (it != _loadedTraces.end()){
			_unloadTrace = -1;
		}
		else{
			if (_loadedTraces.size()<traceCount) _unloadTrace = -1;
			else{
				_unloadTrace = _loadedTraces.front();
				_loadedTraces.pop_front();
			}
			_loadedTraces.push_back(traceNum);
		}
	}
	long long getUnloadTrace(){
		long long temp = _unloadTrace;
		_unloadTrace = -1;
		return temp;
	}
	void clear(){
		_loadedTraces.clear();
		_unloadTrace = -1;
	}
private:
	std::list<long long> _loadedTraces;
	long long _unloadTrace;
};

class AllTraceStrategy:public ITraceStrategy{
public:
    AllTraceStrategy();
	bool canAppendTrace(long long traceNum);
	bool canLoadTrace(long long traceNum);
	void loadTrace(long long traceNum);
	long long getUnloadTrace();
    void clear();
};

#endif // LOADSTRATEGIES_H
