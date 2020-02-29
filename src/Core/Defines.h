#ifndef __DEFINES_H__
#define __DEFINES_H__

#define MISHKA_NAME "Mishka"
#define MISHKA_VERSION "0.0.1"
#define MISHKA_VERSION_NUMBER 1
#define MISHKA_DEBUG _DEBUG

#define MISHKA_COMPILER_MSVC 1

#ifdef _MSC_VER
#   define MISHKA_COMPILER MISHKA_COMPILER_MSVC
#   define MISHKA_COMPILER_NAME "Microsoft Visual Studio"

#   define FORCE_INLINE __forceinline
#   pragma warning(disable:5033)
#endif

typedef char                   i8;
typedef short int              i16;
typedef int                    i32;
typedef long long int          i64;
typedef unsigned char          u8;
typedef unsigned short int     u16;
typedef unsigned int           u32;
typedef unsigned long long int u64;

#endif // __DEFINES_H__
