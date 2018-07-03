#include "types.h"

int n=1;
const Endian currentEndian=(*(char *)&n == 1) ? ENDIAN_LITTLE :ENDIAN_BIG;
