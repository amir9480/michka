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

#ifndef __POSITION_H__
#define __POSITION_H__

#include "Core/Helpers.h"
#include "MichkaGenerated/Core/Container/Position.generated.h"

namespace Michka
{
    template<typename T>
    class MICHKA_API PositionTemplate
    {
        MICHKA_CLASS();

    public:
        FORCE_INLINE PositionTemplate();
        FORCE_INLINE PositionTemplate(const T& _x, const T& _y);
        FORCE_INLINE PositionTemplate(const PositionTemplate<T>& _other);

        /**
         * @brief Set position.
         *
         * @return Self
         */
        FORCE_INLINE PositionTemplate<T>& set(const T& _x, const T& _y);

        /**
         * @brief Set x.
         *
         * @return Self
         */
        FORCE_INLINE PositionTemplate<T>& setX(const T& _x);

        /**
         * @brief Set y.
         *
         * @return Self
         */
        FORCE_INLINE PositionTemplate<T>& setY(const T& _y);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE PositionTemplate<T>& operator = (const PositionTemplate<T>& _other);

        FORCE_INLINE bool operator == (const PositionTemplate<T>& _other) const;
        FORCE_INLINE bool operator != (const PositionTemplate<T>& _other) const;

    public:
        T x = 0;
        T y = 0;
    };

    typedef PositionTemplate<u32> Position;
    typedef PositionTemplate<f32> PositionFloat;
}

#include "Position.inl"

#endif // __POSITION_H__
