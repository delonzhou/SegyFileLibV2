#ifndef CONCURRENTSEGYFILE_H
#define CONCURRENTSEGYFILE_H

#include "segyfile.h"
#include <mutex>

template <class TraceElementType=TraceElement,class TraceCacheType=LruCache<long long, std::vector<TraceElementType> >,class TraceHeaderCacheType=LruCache<long long, SegyTraceHeader>>
class ConcurrentSegyFile:public SegyFile<TraceElementType,TraceCacheType,TraceHeaderCacheType>{
public:
    typedef SegyFile<TraceElementType,TraceCacheType,TraceHeaderCacheType> Parent;

    ConcurrentSegyFile(const FieldMapper segyHeaderMapper = FieldMapper(), const FieldMapper segyTraceHeaderMapper = FieldMapper()):Parent(segyHeaderMapper,segyTraceHeaderMapper)
    {}

    ConcurrentSegyFile(String path,String mode="rw", const FieldMapper segyHeaderMapper = FieldMapper(), const FieldMapper segyTraceHeaderMapper = FieldMapper(), Endian endian = Endian::ENDIAN_BIG):
        Parent(path,mode,segyHeaderMapper,segyTraceHeaderMapper,endian)
    {}

    virtual void openFile(String path, String mode, Endian endian){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        Parent::openFile(path,mode,endian);
    }

    virtual void closeFile(){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        Parent::closeFile();
    }

    virtual bool isOpen(){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::isOpen();
    }

    virtual void setHeaderMapper(const FieldMapper &mapper){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        Parent::setHeaderMapper(mapper);
    }

    virtual void setTraceHeaderMapper(const FieldMapper &mapper){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        Parent::setTraceHeaderMapper(mapper);
    }

    virtual void fflush(){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        Parent::fflush();
    }

    virtual const char* getEbcidicHeader()const{
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::getEbcidicHeader();
    }

    virtual int getSampleCount()const{
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::getSampleCount();
    }

    virtual const SegyHeader& getHeader()const{
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::getHeader();
    }

    virtual bool setHeader(const IHeader &header){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::setHeader(header);
    }

    virtual long long getTraceCount()const{
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::getTraceCount();
    }

    virtual typename Parent::TraceConstPtr getTrace(long long traceNum) const{
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::getTrace(traceNum);
    }

    virtual bool setTrace(long long traceNum, const typename Parent::Trace &trace){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::setTrace(traceNum,trace);
    }

    virtual const SegyTraceHeader& getTraceHeader(long long traceNum) const{
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::getTraceHeader(traceNum);
    }

    virtual bool setTraceHeader(long long traceNum, const IHeader &traceHeader){
        std::lock_guard<std::recursive_mutex>lock(_mutex);
        return Parent::setTraceHeader(traceNum,traceHeader);
    }
private:
    mutable std::recursive_mutex _mutex;
};

#endif // CONCURRENTSEGYFILE_H
