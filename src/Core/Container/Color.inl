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

#include "Michka/Core/Container/Color.h"
#include "Michka/Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Color::Color() :
        r(0),
        g(0),
        b(0),
        a(255)
    {
        //
    }

    FORCE_INLINE Color::Color(const u8& _red, const u8& _green, const u8& _blue, const u8& _alpha) :
        r(_red),
        g(_green),
        b(_blue),
        a(_alpha)
    {
        //
    }

    FORCE_INLINE Color::Color(const u32& _hex)
    {
        set(_hex);
    }

    FORCE_INLINE Color::Color(const Color& _other)
    {
        hex = _other.hex;
    }

    FORCE_INLINE Color& Color::set(const u8& _red, const u8& _green, const u8& _blue, const u8& _alpha)
    {
        r = _red;
        g = _green;
        b = _blue;
        a = _alpha;

        return *this;
    }

    FORCE_INLINE Color& Color::set(const u32& _hex)
    {
        r = (_hex & 0xff000000) >> 24;
        g = (_hex & 0x00ff0000) >> 16;
        b = (_hex & 0x0000ff00) >> 8;
        a = (_hex & 0x000000ff);

        return *this;
    }

    FORCE_INLINE Color& Color::operator = (const Color& _other)
    {
        hex = _other.hex;

        return *this;
    }

    FORCE_INLINE Color& Color::operator = (const u32& _hex)
    {
        return set(_hex);
    }

    FORCE_INLINE bool Color::operator == (const Color& _other) const
    {
        return (Math::diff(r, _other.r) <= 5) &&
               (Math::diff(g, _other.g) <= 5) &&
               (Math::diff(b, _other.b) <= 5) &&
               (Math::diff(a, _other.a) <= 5);
    }

    FORCE_INLINE bool Color::operator != (const Color& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE u8 Color::operator [] (const u8& _d) const
    {
        return asArray[_d];
    }

    FORCE_INLINE u8& Color::operator [] (const u8& _d)
    {
        return asArray[_d];
    }
}
