#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>

typedef double TraceElement;

typedef std::string String;
typedef unsigned char byte;

enum class Endian:int{ENDIAN_UNDEFINED,ENDIAN_BIG,ENDIAN_LITTLE};

extern const Endian currentEndian;

enum class Format:int{FORMAT_UNDEFINED=0,FORMAT_IBM=1,FORMAT_4INT,FORMAT_2INT,FORMAT_4FIXEDPOINT,FORMAT_4IEEE,FORMAT_NU1,FORMAT_NU2,FORMAT_1INT,FORMAT_8IEEE};

#endif // TYPES_H
