#include <boost/python.hpp>
#include <iostream>
#include "segyfile.h"
#include "segyheaderwrapper.h"
#include "segytraceheader.h"
#include "loadstrategies.h"

class SegyFileWrapper{
public:
    SegyFileWrapper(){}

    SegyFileWrapper(String path):_sf(path,"rw",FieldMapper(),FieldMapper(),Endian::ENDIAN_BIG){
        //std::cout<<_sf.getTraceCount()<<std::endl;
    }

    SegyFileWrapper(String path,String mode):_sf(path,mode,FieldMapper(),FieldMapper(),Endian::ENDIAN_BIG){
        //std::cout<<_sf.getTraceCount()<<std::endl;
    }

     void openFile(String path){
         _sf.openFile(path);
     }
     bool closeFile(){
         _sf.closeFile();
         return true;
     }
     bool isOpen(){
         return _sf.isOpen();
     }
     void fflush(){
         _sf.fflush();
     }
     int getSampleCount(){
         return _sf.getSampleCount();
     }

     const char* getEbcidicHeader(){
         return _sf.getEbcidicHeader();
     }

     SegyTraceHeader getTraceHeader(long long traceNum){
         return SegyTraceHeader(static_cast<const SegyTraceHeader&>(_sf.getTraceHeader(traceNum)));
     }
     bool setTraceHeader(long long traceNum, const SegyTraceHeader traceHeader){
         return _sf.setTraceHeader(traceNum,traceHeader);
     }

     PyObject* getTrace(long long traceNum){
         boost::python::list* l = new boost::python::list();
         SegyFile<double>::TraceConstPtr trace=_sf.getTrace(traceNum);
         for(int i=0;i<_sf.getSampleCount();++i)(*l).append(trace->at(i));
         return l->ptr();
     }
     void setTrace(long long traceNum,PyObject* ll){
         SegyFile<double>::Trace trace;
         if (PyTuple_Check(ll)) {
             for(Py_ssize_t i = 0; i < PyTuple_Size(ll); i++) {
                 PyObject *value = PyTuple_GetItem(ll, i);
                 trace.push_back(PyFloat_AsDouble(value));
             }
         } else {
             if (PyList_Check(ll)) {
                 for(Py_ssize_t i = 0; i < PyList_Size(ll); i++) {
                     PyObject *value = PyList_GetItem(ll, i);
                     trace.push_back(PyFloat_AsDouble(value));
                 }
             }
         }
         _sf.setTrace(traceNum,trace);
     }

     long long getTraceCount(){
        return _sf.getTraceCount();
     }

     SegyHeaderWrapper getHeader(){
         return SegyHeaderWrapper(SegyHeader(static_cast<const SegyHeader&>(_sf.getHeader())));
     }
     bool setHeader(const SegyHeaderWrapper& header){
         return _sf.setHeader(header._sh);
     }

     static SegyFileWrapper* createSegy(String path,const SegyHeader header,int endian){
         SegyFile<double> * sf=SegyFile<double>::createSegy(path,header,(Endian)endian);
         delete sf;
         return new SegyFileWrapper(path);
     }
private:
    SegyFile<double> _sf;
};
