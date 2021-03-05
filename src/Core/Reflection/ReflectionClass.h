// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2021 amir alizadeh.                                          //
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

#ifndef __REFLECTION_CLASS_H__
#define __REFLECTION_CLASS_H__

#include "Core/Helpers.h"

#define __MICHKA_PARENT_CLASSES(...)                                                  MICHKA_OVERLOADED_MACRO(___MICHKA_PARENT_CLASSES, __VA_ARGS__)
#define ___MICHKA_PARENT_CLASSES0()                                                   typedef void Parent;
#define ___MICHKA_PARENT_CLASSES1(_T1)                                                typedef _T1 Parent;
#define ___MICHKA_PARENT_CLASSES2(_T1, _T2)                                           typedef _T1 Parent; typedef _T2 Parent2;
#define ___MICHKA_PARENT_CLASSES3(_T1, _T2, _T3)                                      typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3;
#define ___MICHKA_PARENT_CLASSES4(_T1, _T2, _T3, _T4)                                 typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4;
#define ___MICHKA_PARENT_CLASSES5(_T1, _T2, _T3, _T4, _T5)                            typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4; typedef _T5 Parent5;
#define ___MICHKA_PARENT_CLASSES6(_T1, _T2, _T3, _T4, _T5, _T6)                       typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4; typedef _T5 Parent5; typedef _T6 Parent6;
#define ___MICHKA_PARENT_CLASSES7(_T1, _T2, _T3, _T4, _T5, _T6, _T7)                  typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4; typedef _T5 Parent5; typedef _T6 Parent6; typedef _T7 Parent7;
#define ___MICHKA_PARENT_CLASSES8(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8)             typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4; typedef _T5 Parent5; typedef _T6 Parent6; typedef _T7 Parent7; typedef _T8 Parent8;
#define ___MICHKA_PARENT_CLASSES9(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9)        typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4; typedef _T5 Parent5; typedef _T6 Parent6; typedef _T7 Parent7; typedef _T8 Parent8; typedef _T9 Parent9;
#define ___MICHKA_PARENT_CLASSES10(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10) typedef _T1 Parent; typedef _T2 Parent2; typedef _T3 Parent3; typedef _T4 Parent4; typedef _T5 Parent5; typedef _T6 Parent6; typedef _T7 Parent7; typedef _T8 Parent8; typedef _T9 Parent9; typedef _T10 Parent10;

#define __MICHKA_STRUCT_GENERATED_BODY

#define MICHKA_STRUCT_WITH_NAME(_TYPE, _NAME, ...) \
    __MICHKA_PARENT_CLASSES(__VA_ARGS__); \
    typedef _TYPE Self; \
    static inline const char* className() \
    { \
        return _NAME; \
    } \
    __MICHKA_STRUCT_GENERATED_BODY

#define MICHKA_CLASS_WITH_NAME(_TYPE, _NAME, ...) \
    public: \
        MICHKA_STRUCT_WITH_NAME(_TYPE, _NAME, __VA_ARGS__) \
    private:

#define MICHKA_STRUCT(_TYPE, ...) \
    MICHKA_STRUCT_WITH_NAME(_TYPE, #_TYPE, __VA_ARGS__)

#define MICHKA_CLASS(_TYPE, ...) \
    MICHKA_CLASS_WITH_NAME(_TYPE, #_TYPE, __VA_ARGS__)

namespace Michka
{

}

#endif // __REFLECTION_CLASS_H__
