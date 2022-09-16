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

#include "Michka/Core/Container/Rect.h"
#include "Michka/Core/Container/String.h"

namespace Michka
{
    template<typename T>
    FORCE_INLINE RectTemplate<T>::RectTemplate() :
        x(0),
        y(0),
        width(0),
        height(0)
    {
        //
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>::RectTemplate(const PositionTemplate<T>& _position, const SizeTemplate<T>& _size) :
        x(_position.x),
        y(_position.y),
        width(_size.width),
        height(_size.height)
    {
        //
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>::RectTemplate(const T& _x, const T& _y, const T& _width, const T& _height) :
        x(_x),
        y(_y),
        width(_width),
        height(_height)
    {
        //
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>::RectTemplate(const RectTemplate<T>& _other) :
        x(_other.x),
        y(_other.y),
        width(_other.width),
        height(_other.height)
    {
        //
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::set(const T& _x, const T& _y, const T& _width, const T& _height)
    {
        x = _x;
        y = _y;
        width = _width;
        height = _height;

        return *this;
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::setHeight(const T& _height)
    {
        height = _height;
        return *this;
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::setPosition(const PositionTemplate<T>& _position)
    {
        x = _position.x;
        y = _position.y;

        return *this;
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::setSize(const SizeTemplate<T>& _size)
    {
        width = _size.width;
        height = _size.height;

        return *this;
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::setWidth(const T& _width)
    {
        width = _width;
        return *this;
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::setX(const T& _x)
    {
        x = _x;
        return *this;
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::setY(const T& _y)
    {
        y = _y;
        return *this;
    }

    template<typename T>
    String RectTemplate<T>::toString() const
    {
        return String("Rect(position=") + position.toString() + ", size=" + size.toString() + ")";
    }

    template<typename T>
    FORCE_INLINE RectTemplate<T>& RectTemplate<T>::operator = (const RectTemplate<T>& _other)
    {
        x = _other.x;
        y = _other.y;
        width = _other.width;
        height = _other.height;

        return *this;
    }

    template<typename T>
    FORCE_INLINE bool RectTemplate<T>::operator == (const RectTemplate<T>& _other) const
    {
        return x == _other.x && y == _other.y && width == _other.width && height == _other.height;
    }

    template<typename T>
    FORCE_INLINE bool RectTemplate<T>::operator != (const RectTemplate<T>& _other) const
    {
        return !(*this == _other);
    }
}
