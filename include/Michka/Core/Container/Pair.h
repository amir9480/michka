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

#ifndef __PAIR_H__
#define __PAIR_H__

#include <utility>
#include "Michka/Core/Helpers.h"

namespace Michka
{
    template<typename T1, typename T2>
    struct Pair
    {
        FORCE_INLINE Pair();
        FORCE_INLINE Pair(const T1& _first, const T2& _second);
        FORCE_INLINE Pair(T1&& _first, T2&& _second);
        FORCE_INLINE Pair(const Pair<T1, T2>& _other);
        FORCE_INLINE Pair(Pair<T1, T2>&& _other);
        FORCE_INLINE ~Pair();

        FORCE_INLINE Pair<T1, T2>& operator = (const Pair<T1, T2>& _other);
        FORCE_INLINE Pair<T1, T2>& operator = (Pair<T1, T2>&& _other);

        T1 first;
        T2 second;
    };
}

#include "Core/Container/Pair.inl"

#endif // __PAIR_H__