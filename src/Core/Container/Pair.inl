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

#include "Pair.h"

namespace Michka
{
    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>::Pair()
    {
        //
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>::Pair(const T1& _first, const T2& _second):
        first(_first),
        second(_second)
    {
        //
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>::Pair(T1&& _first, T2&& _second) :
        first(std::forward<T1>(_first)),
        second(std::forward<T2>(_second))
    {
        //
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>::Pair(const Pair<T1, T2>& _other):
        first(_other.first),
        second(_other.second)
    {
        //
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>::Pair(Pair<T1, T2>&& _other):
        first(std::move(_other.first)),
        second(std::move(_other.second))
    {
        //
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>::~Pair()
    {
        //
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>& Pair<T1, T2>::operator = (const Pair<T1, T2>& _other)
    {
        first = _other.first;
        second = _other.second;

        return *this;
    }

    template<typename T1, typename T2>
    FORCE_INLINE Pair<T1, T2>& Pair<T1, T2>::operator = (Pair<T1, T2>&& _other)
    {
        first = std::move(_other.first);
        second = std::move(_other.second);

        return *this;
    }
}
