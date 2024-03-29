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

#include "Michka/Core/Container/Position.h"
#include "Michka/Core/Container/String.h"

namespace Michka
{
    template<typename T>
    FORCE_INLINE PositionTemplate<T>::PositionTemplate()
    {
        //
    }

    template<typename T>
    FORCE_INLINE PositionTemplate<T>::PositionTemplate(const T& _x, const T& _y) :
        x(_x),
        y(_y)
    {
        //
    }

    template<typename T>
    FORCE_INLINE PositionTemplate<T>::PositionTemplate(const PositionTemplate<T>& _other) :
        x(_other.x),
        y(_other.y)
    {
        //
    }

    template<typename T>
    FORCE_INLINE PositionTemplate<T>& PositionTemplate<T>::set(const T& _x, const T& _y)
    {
        x = _x;
        y = _y;

        return *this;
    }

    template<typename T>
    FORCE_INLINE PositionTemplate<T>& PositionTemplate<T>::setY(const T& _y)
    {
        y = _y;
        return *this;
    }

    template<typename T>
    String PositionTemplate<T>::toString() const
    {
        return String("Position(") + String::number(x) + ", " + String::number(y) + ")";
    }

    template<typename T>
    FORCE_INLINE PositionTemplate<T>& PositionTemplate<T>::setX(const T& _x)
    {
        x = _x;
        return *this;
    }

    template<typename T>
    FORCE_INLINE PositionTemplate<T>& PositionTemplate<T>::operator = (const PositionTemplate<T>& _other)
    {
        x = _other.x;
        y = _other.y;

        return *this;
    }

    template<typename T>
    FORCE_INLINE bool PositionTemplate<T>::operator == (const PositionTemplate<T>& _other) const
    {
        return x == _other.x && y == _other.y;
    }

    template<typename T>
    FORCE_INLINE bool PositionTemplate<T>::operator != (const PositionTemplate<T>& _other) const
    {
        return !(*this == _other);
    }
}
