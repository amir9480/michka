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

#ifndef __RECT_H__
#define __RECT_H__

#include "Core/Defines.h"
#include "Position.h"
#include "Size.h"
#include "Core/Reflection/ReflectionClass.h"
#include "MichkaGenerated/Core/Container/Rect.generated.h"

namespace Michka
{
    /**
     * @brief Rectangle class.
     *
     * Position
     *          *------ width ------+
     *          |                   |
     *       height              height
     *          |                   |
     *          +------ width ------+
     */
    template<typename T>
    class MICHKA_API RectTemplate
    {
        MICHKA_CLASS(RectTemplate<T>);
    public:
        FORCE_INLINE RectTemplate();
        FORCE_INLINE RectTemplate(const PositionTemplate<T>& _position, const SizeTemplate<T>& _size);
        FORCE_INLINE RectTemplate(const T& _x, const T& _y, const T& _width, const T& _height);
        FORCE_INLINE RectTemplate(const RectTemplate<T>& _other);

        /**
         * @brief Set rect.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& set(const T& _x, const T& _y, const T& _width, const T& _height);

        /**
         * @brief Set height.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& setHeight(const T& _height);

        /**
         * @brief Set position.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& setPosition(const PositionTemplate<T>& _position);

        /**
         * @brief Set size.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& setSize(const SizeTemplate<T>& _size);

        /**
         * @brief Set width.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& setWidth(const T& _width);

        /**
         * @brief Set x.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& setX(const T& _x);

        /**
         * @brief Set y.
         *
         * @return Self
         */
        FORCE_INLINE RectTemplate<T>& setY(const T& _y);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE RectTemplate<T>& operator = (const RectTemplate<T>& _other);

        FORCE_INLINE bool operator == (const RectTemplate<T>& _other) const;
        FORCE_INLINE bool operator != (const RectTemplate<T>& _other) const;

    public:
        union
        {
            struct
            {
                PositionTemplate<T> position;
                SizeTemplate<T> size;
            };
            struct
            {
                T x;
                T y;
                T width;
                T height;
            };
        };
    };

    typedef RectTemplate<u32> Rect;
    typedef RectTemplate<f32> RectFloat;
}

#include "Rect.inl"

#endif // __RECT_H__
