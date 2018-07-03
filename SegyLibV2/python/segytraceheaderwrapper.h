#ifndef SEGYTRACEHEADERWRAPPER_H
#define SEGYTRACEHEADERWRAPPER_H

#include "segytraceheader.h"
#include "boost/any.hpp"

class SegyTraceHeaderWrapper{
public:
    SegyTraceHeaderWrapper(const SegyTraceHeader& sth):_sth(sth){}
    SegyTraceHeaderWrapper(){}
    int get(const std::string& field){
        return boost::any_cast<int>(_sth.get(field));
    }
    void set(const std::string& field,int value){
        _sth.set(field,value);
    }

    static PyObject* getFieldList(){
        boost::python::list* l = new boost::python::list();
        std::vector<std::string> trace=SegyTraceHeader::fieldNames;
        for(size_t i=0;i<trace.size();++i)(*l).append(trace.at(i));
        return l->ptr();
    }

    static std::string getFullFieldName(const std::string& field){
        return SegyTraceHeader::detailInfo.at(field).fullFieldName;
    }

    static std::string getFieldDescription(const std::string& field){
        return SegyTraceHeader::detailInfo.at(field).fieldDescription;
    }

    static PyObject* getDefaultFieldLocation(const std::string& field){
        boost::python::dict *l=new boost::python::dict();
        auto gh=SegyTraceHeader::mapperInfo.at(field);
        (*l)["start"]=gh.startPos;
        (*l)["length"]=gh.length;
        return l->ptr();
    }

    SegyTraceHeader _sth;
};


#endif // SEGYTRACEHEADERWRAPPER_H
