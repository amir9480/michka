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

#ifndef __COLOR_H__
#define __COLOR_H__

#include "Core/Defines.h"
#include "Core/Reflection/ReflectionClass.h"

namespace Michka
{
    class Vector3;
    class Vector4;

    class MICHKA_API Color
    {
        MICHKA_CLASS(Color);
    public:
        FORCE_INLINE Color();
        FORCE_INLINE Color(const u8& _red, const u8& _green, const u8& _blue, const u8& _alpha = 255);
        FORCE_INLINE Color(const u32& _hex);
        FORCE_INLINE Color(const Color& _other);

        /**
         * @brief Set Color.
         *
         * @param _red
         * @param _green
         * @param _blue
         * @param _alpha
         * @return Self
         */
        FORCE_INLINE Color& set(const u8& _red, const u8& _green, const u8& _blue, const u8& _alpha = 255);

        /**
         * @brief Set color from hex.
         *
         * @param _hex
         * @return Self
         */
        FORCE_INLINE Color& set(const u32& _hex);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Color& operator = (const Color& _other);
        FORCE_INLINE Color& operator = (const u32& _hex);

        FORCE_INLINE bool operator == (const Color& _other) const;
        FORCE_INLINE bool operator != (const Color& _other) const;

        FORCE_INLINE u8& operator [] (const u8& _d);
        FORCE_INLINE u8 operator [] (const u8& _d) const;

        operator Vector3 () const;
        operator Vector4 () const;

    public:
        static const Color transparent;
        static const Color black;
        static const Color white;
        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color yellow;
        static const Color cyan;
        static const Color magenta;

    public:
        union
        {
            struct
            {
                u8 r;
                u8 g;
                u8 b;
                u8 a;
            };
            u8 asArray[4];
            u32 hex;
        };
    };
}

#include "Color.inl"

#endif // __COLOR_H__
