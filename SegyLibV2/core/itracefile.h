#ifndef ITRACEFILE_H
#define ITRACEFILE_H

#include "types.h"

class ITraceFile
{
public:
	//Возвращает количество трасс
    virtual long long getTraceCount()const=0;
};

#endif // ITRACEFILE_H
