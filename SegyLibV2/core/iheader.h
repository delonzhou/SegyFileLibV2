#ifndef AHEADER_H
#define AHEADER_H

#include <string>
#include <vector>
#include <map>
#include <boost/any.hpp>

struct FieldMappingInfo{
    int startPos;
    int length;
    FieldMappingInfo(int sp, int l) :startPos(sp), length(l){}
    FieldMappingInfo() :startPos(0), length(0){}
};

bool operator== (const FieldMappingInfo &c1, const FieldMappingInfo &c2);

struct FieldDetailInfo{
    std::string fullFieldName;
    std::string fieldDescription;
    FieldDetailInfo(std::string ffn = std::string(), std::string fd = std::string()) :fullFieldName(ffn), fieldDescription(fd){}
};

typedef std::map < std::string, FieldMappingInfo > FieldMapper;

bool compareMappers (FieldMapper const &lhs, FieldMapper const &rhs);

class IHeader
{
public:
    IHeader();
    virtual boost::any get(const std::string& fieldName)const=0;
    virtual void set(const std::string& fieldName, boost::any value)=0;
    virtual const std::vector<std::string>& getFieldNames()const = 0;
};

#endif // AHEADER_H
