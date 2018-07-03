#include "types.h"
/*
template <class TraceElementType = TraceElement>
class BinaryFile :public ITraceDataFile<std::vector<TraceElementType> >
{
public:
	BinaryFile(String path, String mode = "rw", const FieldMapper segyHeaderMapper = FieldMapper(), const FieldMapper segyTraceHeaderMapper = FieldMapper(), Endian endian = ENDIAN_BIG, ITraceStrategy *traceStrategy = new MultipleTraceStrategy<500>(), ITraceStrategy *headerStrategy = new MultipleTraceStrategy<500>()) :
		_traceLoadStrategy(traceStrategy), _traceHeaderLoadStrategy(headerStrategy),
		_isOpen(false)
	{
		initHeaderMapper(segyHeaderMapper);
		initTraceHeaderMapper(segyTraceHeaderMapper);
		openFile(path, mode, endian);
	}
};*/