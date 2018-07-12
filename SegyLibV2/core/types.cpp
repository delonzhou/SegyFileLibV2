#include "types.h"

int n=1;
const Endian currentEndian=(*(char *)&n == 1) ? Endian::ENDIAN_LITTLE : Endian::ENDIAN_BIG;
