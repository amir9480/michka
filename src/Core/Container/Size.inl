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

#include "Michka/Core/Container/Size.h"
#include "Michka/Core/Container/String.h"

namespace Michka
{
    template<typename T>
    FORCE_INLINE SizeTemplate<T>::SizeTemplate()
    {
        //
    }

    template<typename T>
    FORCE_INLINE SizeTemplate<T>::SizeTemplate(const T& _width, const T& _height) :
        width(_width),
        height(_height)
    {
        //
    }

    template<typename T>
    FORCE_INLINE SizeTemplate<T>::SizeTemplate(const SizeTemplate<T>& _other) :
        width(_other.width),
        height(_other.height)
    {
        //
    }

    template<typename T>
    FORCE_INLINE SizeTemplate<T>& SizeTemplate<T>::set(const T& _width, const T& _height)
    {
        width = _width;
        height = _height;

        return *this;
    }

    template<typename T>
    FORCE_INLINE SizeTemplate<T>& SizeTemplate<T>::setHeight(const T& _height)
    {
        height = _height;
        return *this;
    }

    template<typename T>
    FORCE_INLINE SizeTemplate<T>& SizeTemplate<T>::setWidth(const T& _width)
    {
        width = _width;
        return *this;
    }

    template<typename T>
    String SizeTemplate<T>::toString() const
    {
        return String("Size(") + String::number(width) + ", " + String::number(height) + ")";
    }

    template<typename T>
    FORCE_INLINE SizeTemplate<T>& SizeTemplate<T>::operator = (const SizeTemplate<T>& _other)
    {
        width = _other.width;
        height = _other.height;

        return *this;
    }

    template<typename T>
    FORCE_INLINE bool SizeTemplate<T>::operator == (const SizeTemplate<T>& _other) const
    {
        return width == _other.width && height == _other.height;
    }

    template<typename T>
    FORCE_INLINE bool SizeTemplate<T>::operator != (const SizeTemplate<T>& _other) const
    {
        return !(*this == _other);
    }
}
