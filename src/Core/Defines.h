#ifndef __DEFINES_H__
#define __DEFINES_H__

/* ---------------------------------- Info ---------------------------------- */

#define MICHKA_NAME "Michka"
#define MICHKA_VERSION "0.0.1"
#define MICHKA_VERSION_NUMBER 1
#define MICHKA_DEBUG _DEBUG

/* -------------------------------- Compiler -------------------------------- */

#define MICHKA_COMPILER_MSVC 1

#ifdef _MSC_VER
#   define MICHKA_COMPILER MICHKA_COMPILER_MSVC
#   define MICHKA_COMPILER_NAME "Microsoft Visual Studio"

#   define FORCE_INLINE __forceinline
#   pragma warning(disable:5033)
#endif

/* -------------------------------- Platform -------------------------------- */

#define MICHKA_PLATFORM_WIN32 1

#if defined(WIN32) || defined(_WIN32)
#   define MICHKA_PLATFORM MICHKA_PLATFORM_WIN32
#   define MICHKA_PLATFORM_NAME "Windows"
#   define MICHKA_API __declspec(dllexport)
#endif

/* ---------------------------------- Types --------------------------------- */

typedef char                   i8;
typedef short int              i16;
typedef int                    i32;
typedef long long int          i64;
typedef unsigned char          u8;
typedef unsigned short int     u16;
typedef unsigned int           u32;
typedef unsigned long long int u64;

/* --------------------- Custom new and delete operators -------------------- */

#if MICHKA_DEBUG
#   define MICHKA_NEW new(__FILE__, __LINE__)
#else
#   define MICHKA_NEW new
#endif // MICHKA_DEBUG

#define new MICHKA_NEW

#include "Memory/Memory.h"

#endif // __DEFINES_H__
