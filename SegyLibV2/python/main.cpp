#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>
#include "segyheaderwrapper.h"
#include "segytraceheaderwrapper.h"
#include "segyfilewrapper.h"
#include "sutraceheader.h"
#include "sufilewrapper.h"
//#include "TbinFileWrapper.h"
#include "types.h"



using namespace boost::python;


/*template<class T>
struct VecToList
{
    static PyObject* convert(const std::vector<T>& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
            (*l).append(vec[i]);

        return l->ptr();
    }
};*/


BOOST_PYTHON_MODULE(SegyV2)
{
    scope().attr("BIG_ENDIAN") = static_cast<int>(Endian::ENDIAN_BIG);
    scope().attr("LITTLE_ENDIAN") = static_cast<int>(Endian::ENDIAN_LITTLE);
    scope().attr("IBM_FORMAT") = static_cast<int>(Format::FORMAT_IBM);
    scope().attr("INT4_FORMAT") = static_cast<int>(Format::FORMAT_4INT);
    scope().attr("INT2_FORMAT") = static_cast<int>(Format::FORMAT_2INT);
    scope().attr("FIXPOINT4_FORMAT") = static_cast<int>(Format::FORMAT_4FIXEDPOINT);
    scope().attr("IEEE4_FORMAT") = static_cast<int>(Format::FORMAT_4IEEE);
    scope().attr("INT1_FORMAT") = static_cast<int>(Format::FORMAT_1INT);
    scope().attr("IEEE8_FORMAT") = static_cast<int>(Format::FORMAT_8IEEE);
	class_< std::vector<std::string> >("VectorOfStr")
    .def(vector_indexing_suite< std::vector<std::string> >() )
    ;

    class_<SegyHeaderWrapper>("SegyHeader")
        .def("get",&SegyHeaderWrapper::get,args("name"))
        .def("set",&SegyHeaderWrapper::set,args("name","value"))
        .def("getFieldList",&SegyHeaderWrapper::getFieldList).staticmethod("getFieldList")
        .def("getFullFieldName",&SegyHeaderWrapper::getFullFieldName,args("name")).staticmethod("getFullFieldName")
        .def("getFieldDescription",&SegyHeaderWrapper::getFieldDescription,args("name")).staticmethod("getFieldDescription")
        .def("getDefaultFieldLocation",&SegyHeaderWrapper::getDefaultFieldLocation,args("name")).staticmethod("getDefaultFieldLocation")
;
    class_<SegyTraceHeaderWrapper>("SegyTraceHeader")
        .def("get",&SegyTraceHeaderWrapper::get,args("name"))
        .def("set",&SegyTraceHeaderWrapper::set,args("name","value"))
        .def("getFieldList",&SegyTraceHeaderWrapper::getFieldList).staticmethod("getFieldList")
        .def("getFullFieldName",&SegyTraceHeaderWrapper::getFullFieldName,args("name")).staticmethod("getFullFieldName")
        .def("getFieldDescription",&SegyTraceHeaderWrapper::getFieldDescription,args("name")).staticmethod("getFieldDescription")
        .def("getDefaultFieldLocation",&SegyTraceHeaderWrapper::getDefaultFieldLocation,args("name")).staticmethod("getDefaultFieldLocation")
;

	//to_python_converter<std::vector<double,class std::allocator<double> >, VecToList<double> >();
	//class_<TraceData>("TraceData").def(vector_indexing_suite<TraceData>() );
	class_<SegyFileWrapper>("SegyFile")
		.def(init<String,String>(args("file","mode")))
		.def(init<String>(args("file")))
		.def("openFile", &SegyFileWrapper::openFile, args("file"))
		.def("closeFile", &SegyFileWrapper::closeFile)
		.def("isOpen", &SegyFileWrapper::isOpen)
		.def("getSampleCount", &SegyFileWrapper::getSampleCount)
		.def("getEbcidicHeader",&SegyFileWrapper::getEbcidicHeader)
		.def("getTraceHeader", &SegyFileWrapper::getTraceHeader, args("traceNum"))
		.def("setTraceHeader", &SegyFileWrapper::setTraceHeader, args("traceNum","traceHeader"))
		.def("getTrace", &SegyFileWrapper::getTrace,args("traceNum"))
		.def("setTrace", &SegyFileWrapper::setTrace, args("traceNum","traceData"))
		.def("getTraceCount", &SegyFileWrapper::getTraceCount)
		.def("getHeader", &SegyFileWrapper::getHeader)
		.def("setHeader", &SegyFileWrapper::setHeader)
		.def("fflush",&SegyFileWrapper::fflush)
		.def("createSegy", &SegyFileWrapper::createSegy,return_value_policy<manage_new_object>()).staticmethod("createSegy")
    ;


    class_<SegyTraceHeaderWrapper>("SuTraceHeader")
        .def("get",&SegyTraceHeaderWrapper::get,args("name"))
        .def("set",&SegyTraceHeaderWrapper::set,args("name","value"))
        .def("getFieldList",&SegyTraceHeaderWrapper::getFieldList).staticmethod("getFieldList")
        .def("getFullFieldName",&SegyTraceHeaderWrapper::getFullFieldName,args("name")).staticmethod("getFullFieldName")
        .def("getFieldDescription",&SegyTraceHeaderWrapper::getFieldDescription,args("name")).staticmethod("getFieldDescription")
        .def("getDefaultFieldLocation",&SegyTraceHeaderWrapper::getDefaultFieldLocation,args("name")).staticmethod("getDefaultFieldLocation")
    ;

    //to_python_converter<std::vector<double,class std::allocator<double> >, VecToList<double> >();
    //class_<TraceData>("TraceData").def(vector_indexing_suite<TraceData>() );
    class_<SuFileWrapper>("SuFile")
        .def(init<String,size_t,String>(args("file","sampleCount","mode")))
        .def(init<String,size_t>(args("file","sampleCount")))
        .def("openFile", &SuFileWrapper::openFile, args("file","sampleCount"))
        .def("closeFile", &SuFileWrapper::closeFile)
        .def("isOpen", &SuFileWrapper::isOpen)
        .def("getSampleCount", &SuFileWrapper::getSampleCount)
        .def("getTraceHeader", &SuFileWrapper::getTraceHeader, args("traceNum"))
        .def("setTraceHeader", &SuFileWrapper::setTraceHeader, args("traceNum","traceHeader"))
        .def("getTrace", &SuFileWrapper::getTrace,args("traceNum"))
        .def("setTrace", &SuFileWrapper::setTrace, args("traceNum","traceData"))
        .def("getTraceCount", &SuFileWrapper::getTraceCount)
        .def("fflush",&SuFileWrapper::fflush)
        .def("createSu", &SuFileWrapper::createSu,return_value_policy<manage_new_object>()).staticmethod("createSegy")
    ;

}
