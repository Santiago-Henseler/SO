#ifndef STDINT_H
#define STDINT_H

typedef char  int8;
typedef short int16;
typedef int   int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long long uint64;

#define ALIGN(addr, align) (((int)(addr) + ((align) - 1)) & ~((align) - 1))

#endif