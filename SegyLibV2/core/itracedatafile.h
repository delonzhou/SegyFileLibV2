#ifndef ITRACEDATAFILE_H
#define ITRACEDATAFILE_H

#include "types.h"
#include "itracefile.h"
#include <memory>

template<class TraceType>
class ITraceDataFile :public virtual ITraceFile
{
public:
    //Возвращает трассу
    virtual std::shared_ptr<const TraceType> getTrace(long long traceNum)const = 0;
    //Задаёт значение трассы
    virtual bool setTrace(long long traceNum, const TraceType& trace) = 0;
};

#endif // ITRACEDATAFILE_H
