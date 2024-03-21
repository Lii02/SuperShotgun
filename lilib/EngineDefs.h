#ifndef ENGINEDEFS_H
#define ENGINEDEFS_H

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#define ENGINEAPI __declspec(dllexport)
#elif
#define ENGINEAPI
#endif

#define LILIB_STRINGIFY(x) #x
#define LILIB_BIT(x) (1 << x)

typedef unsigned char ubyte;
typedef char libyte;
typedef float float32;
typedef double float64;
typedef const char* cstring;
typedef const short* cwstring;
typedef unsigned char* ubytebuffer;
typedef char* bytebuffer;
typedef bool bool8;
typedef float float32;
typedef double float64;
typedef uint32_t timestamp_t;

#endif