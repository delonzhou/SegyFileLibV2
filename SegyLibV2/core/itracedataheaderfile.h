#ifndef ITRACEDATAHEADERFILE_H
#define ITRACEDATAHEADERFILE_H

#include "types.h"
#include "itracedatafile.h"
#include "itraceheaderfile.h"

template <class TraceType>
class ITraceDataHeaderFile :public ITraceDataFile<TraceType>,public ITraceHeaderFile
{
};

#endif // ITRACEDATAHEADERFILE_H
