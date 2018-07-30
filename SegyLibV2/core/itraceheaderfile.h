#ifndef ITRACEHEADERFILE_H
#define ITRACEHEADERFILE_H

#include "iheader.h"
#include "itracefile.h"
#include <memory>

class ITraceHeaderFile :public virtual ITraceFile
{
public:
    //Возвращает заголовок трассы
    virtual const IHeader& getTraceHeader(long long traceNum)const=0;
    //Задаёт заголовок трассы
    virtual bool setTraceHeader(long long traceNum,const IHeader& traceHeader)=0;
};

#endif // ITRACEHEADERFILE_H
