#ifndef TYPES_H
#define TYPES_H

typedef char int8;
typedef unsigned char uint8;

typedef short int16;
typedef unsigned short uint16;

typedef int int32;
typedef unsigned int uint32;

typedef long long int64;
typedef unsigned long long uint64;

#define bitfield(x,bits) unsigned x : bits;

typedef uint32 paddr; /* Will do until PAE arrives */

#define NULL 0

#endif /* TYPES_H */
