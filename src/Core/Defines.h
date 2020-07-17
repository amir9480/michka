// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
//                                                                                 //
// Permission is hereby granted, free of charge, to any person obtaining a copy    //
// of this software and associated documentation files (the "Software"), to deal   //
// in the Software without restriction, including without limitation the rights    //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       //
// copies of the Software, and to permit persons to whom the Software is           //
// furnished to do so, subject to the following conditions:                        //
//                                                                                 //
// The above copyright notice and this permission notice shall be included in all  //
// copies or substantial portions of the Software.                                 //
//                                                                                 //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
// SOFTWARE.                                                                       //
// ------------------------------------------------------------------------------- //

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
typedef float                  f32;
typedef double                 f64;
typedef long double            f96;

/* --------------------- Custom new and delete operators -------------------- */

#if MICHKA_DEBUG
#   define MICHKA_NEW new(__FILE__, __LINE__)
#else
#   define MICHKA_NEW new
#endif // MICHKA_DEBUG

#define new MICHKA_NEW

#include "Memory/Memory.h"

/* --------------------------- Forward declartions -------------------------- */

namespace Michka
{
    template<typename T>
    class StringTemplate;

    typedef StringTemplate<char> String8;
    typedef StringTemplate<wchar_t> String;
    typedef StringTemplate<char32_t> String32;
}

#endif // __DEFINES_H__
