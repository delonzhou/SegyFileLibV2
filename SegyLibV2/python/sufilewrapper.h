#ifndef SUFILEWRAPPER_H
#define SUFILEWRAPPER_H

#include <boost/python.hpp>
#include <iostream>
#include "sufile.h"
#include "sutraceheader.h"
#include "loadstrategies.h"

class SuFileWrapper{
public:
    SuFileWrapper(){}

    SuFileWrapper(String path,size_t sampleCount):_sf(path,sampleCount,"rw",FieldMapper(),FORMAT_IBM, ENDIAN_BIG){
        //std::cout<<_sf.getTraceCount()<<std::endl;
    }

    SuFileWrapper(String path,size_t sampleCount,String mode):_sf(path,sampleCount,mode,FieldMapper(),FORMAT_IBM,ENDIAN_BIG){
        //std::cout<<_sf.getTraceCount()<<std::endl;
    }

     void openFile(String path,size_t sampleCount){
         _sf.openFile(path,sampleCount);
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

     SuTraceHeader getTraceHeader(long long traceNum){
         return SuTraceHeader(static_cast<const SuTraceHeader&>(_sf.getTraceHeader(traceNum)));
     }

     bool setTraceHeader(long long traceNum, const SuTraceHeader traceHeader){
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

     static SuFileWrapper* createSu(String path,size_t sampleCount,int endian){
         SuFile<double> * sf=SuFile<double>::createSu(path,sampleCount,(Format)0,(Endian)endian);
         delete sf;
         return new SuFileWrapper(path,sampleCount);
     }
private:
    SuFile<double> _sf;
};

#endif // SUFILEWRAPPER_H
