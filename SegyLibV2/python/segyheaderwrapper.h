#ifndef SEGYHEADERWRAPPER_H
#define SEGYHEADERWRAPPER_H

#include "segyheader.h"
#include <vector>
#include <string>
#include <boost/python.hpp>
#include <boost/any.hpp>

class SegyHeaderWrapper{
public:
    SegyHeaderWrapper(const SegyHeader& sh):_sh(sh){}
    SegyHeaderWrapper(){}
    int get(const std::string& field){
        return boost::any_cast<int>(_sh.get(field));
    }
    void set(const std::string& field,int value){
        _sh.set(field,value);
    }

    static PyObject* getFieldList(){
        boost::python::list* l = new boost::python::list();
        std::vector<std::string> trace=SegyHeader::fieldNames;
        for(size_t i=0;i<trace.size();++i)(*l).append(trace.at(i));
        return l->ptr();
    }

    static std::string getFullFieldName(const std::string& field){
        return SegyHeader::detailInfo.at(field).fullFieldName;
    }

    static std::string getFieldDescription(const std::string& field){
        return SegyHeader::detailInfo.at(field).fieldDescription;
    }

    static PyObject* getDefaultFieldLocation(const std::string& field){
        boost::python::dict *l=new boost::python::dict();
        auto gh=SegyHeader::mapperInfo.at(field);
        (*l)["start"]=gh.startPos;
        (*l)["length"]=gh.length;
        return l->ptr();
    }

    SegyHeader _sh;
};

#endif // SEGYHEADERWRAPPER_H
