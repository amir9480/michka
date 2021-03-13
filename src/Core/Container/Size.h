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

#ifndef __SIZE_H__
#define __SIZE_H__

#include "Core/Helpers.h"
#include "MichkaGenerated/Core/Container/Size.generated.h"

namespace Michka
{
    template<typename T>
    class SizeTemplate
    {
        MICHKA_CLASS(SizeTemplate<T>);
    public:
        FORCE_INLINE SizeTemplate();
        FORCE_INLINE SizeTemplate(const T& _width, const T& _height);
        FORCE_INLINE SizeTemplate(const SizeTemplate<T>& _other);

        /**
         * @brief Set width and height.
         *
         * @return Self
         */
        FORCE_INLINE SizeTemplate<T>& set(const T& _width, const T& _height);

        /**
         * @brief Set height.
         *
         * @return Self
         */
        FORCE_INLINE SizeTemplate<T>& setHeight(const T& _height);

        /**
         * @brief Set width.
         *
         * @return Self
         */
        FORCE_INLINE SizeTemplate<T>& setWidth(const T& _width);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE SizeTemplate<T>& operator = (const SizeTemplate<T>& _other);

        FORCE_INLINE bool operator == (const SizeTemplate<T>& _other) const;
        FORCE_INLINE bool operator != (const SizeTemplate<T>& _other) const;

    public:
        T width = 0;
        T height = 0;
    };

    typedef SizeTemplate<u32> Size;
    typedef SizeTemplate<f32> SizeFloat;
}

#include "Size.inl"

#endif // __SIZE_H__
