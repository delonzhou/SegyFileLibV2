#include "iheader.h"

IHeader::IHeader()
{

}

bool operator==(const FieldMappingInfo &c1, const FieldMappingInfo &c2)
{
    return (c1.startPos==c2.startPos &&
            c1.length== c2.length);
}

bool compareMappers(const FieldMapper &lhs, const FieldMapper &rhs) {
    return lhs.size() == rhs.size()
            && std::equal(lhs.begin(), lhs.end(),
                          rhs.begin());
}
