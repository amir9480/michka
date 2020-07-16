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

#include "Vector4.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Vector4::Vector4() :
        x(0.0f),
        y(0.0f),
        z(0.0f),
        w(1.0f)
    {
        //
    }

    FORCE_INLINE Vector4::Vector4(const f32& _x, const f32& _y, const f32& _z, const f32& _w) :
        x(_x),
        y(_y),
        z(_z),
        w(_w)
    {
        //
    }

    FORCE_INLINE Vector4::Vector4(const Vector4& _other)
    {
        *this = _other;
    }

    FORCE_INLINE f32 Vector4::dotProduct(const Vector4& _a, const Vector4& _b)
    {
        return _a.x*_b.x + _a.y*_b.y + _a.z*_b.z + _a.w*_b.w;
    }

    FORCE_INLINE f32 Vector4::getDotProduct(const Vector4& _other) const
    {
        return dotProduct(*this, _other);
    }

    FORCE_INLINE f32 Vector4::getLength() const
    {
        return Math::sqrt(x*x + y*y + z*z + w*w);
    }

    FORCE_INLINE f32 Vector4::getSqauredLength() const
    {
        return x*x + y*y + z*z + w*w;
    }

    FORCE_INLINE Vector4& Vector4::set(const f32& _x, const f32& _y, const f32& _z, const f32& _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;

        return *this;
    }

    FORCE_INLINE Vector4& Vector4::setX(const f32& _x)
    {
        x = _x;
        return *this;
    }

    FORCE_INLINE Vector4& Vector4::setY(const f32& _y)
    {
        y = _y;
        return *this;
    }

    FORCE_INLINE Vector4& Vector4::setZ(const f32& _z)
    {
        z = _z;
        return *this;
    }

    FORCE_INLINE Vector4& Vector4::setW(const f32& _w)
    {
        w = _w;
        return *this;
    }

    FORCE_INLINE Vector4& Vector4::operator = (const Vector4& _other)
    {
        x = _other.x;
        y = _other.y;
        z = _other.z;
        w = _other.w;

        return *this;
    }

    FORCE_INLINE bool Vector4::operator == (const Vector4& _other) const
    {
        return Math::equals(x, _other.x) && Math::equals(y, _other.y) && Math::equals(z, _other.z) && Math::equals(w, _other.w);
    }

    FORCE_INLINE bool Vector4::operator != (const Vector4& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE f32& Vector4::operator [] (const u8& _d)
    {
        return asArray[_d];
    }

    FORCE_INLINE f32 Vector4::operator [] (const u8& _d) const
    {
        return asArray[_d];
    }

    FORCE_INLINE Vector4 Vector4::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator - () const
    {
        return Vector4(-x, -y, -z, -w);
    }

    FORCE_INLINE Vector4& Vector4::operator += (const f32& _scaler)
    {
        x += _scaler;
        y += _scaler;
        z += _scaler;
        w += _scaler;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator + (const f32& _scaler) const
    {
        Michka::Vector4 out = *this;
        out += _scaler;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator += (const Vector4& _other)
    {
        x += _other.x;
        y += _other.y;
        z += _other.z;
        w += _other.w;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator + (const Vector4& _other) const
    {
        Michka::Vector4 out = *this;
        out += _other;

        return out;
    }

    FORCE_INLINE Vector4 operator + (const f32& _a, const Vector4& _b)
    {
        Michka::Vector4 out = _b;
        out.x = _a + out.x;
        out.y = _a + out.y;
        out.z = _a + out.z;
        out.w = _a + out.w;

        return out;
    }

    FORCE_INLINE Vector4 Vector4::operator - (const Vector4& _other) const
    {
        Michka::Vector4 out = *this;
        out -= _other;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator -= (const Vector4& _other)
    {
        x -= _other.x;
        y -= _other.y;
        z -= _other.z;
        w -= _other.w;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator - (const f32& _scaler) const
    {
        Michka::Vector4 out = *this;
        out -= _scaler;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator -= (const f32& _scaler)
    {
        x -= _scaler;
        y -= _scaler;
        z -= _scaler;
        w -= _scaler;

        return *this;
    }

    FORCE_INLINE Vector4 operator - (const f32& _a, const Vector4& _b)
    {
        Michka::Vector4 out = _b;
        out.x = _a - out.x;
        out.y = _a - out.y;
        out.z = _a - out.z;
        out.w = _a - out.w;

        return out;
    }

    FORCE_INLINE Vector4 operator * (const f32& _a, const Vector4& _b)
    {
        Vector4 out = _b;
        out *= _a;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator *= (const f32& _scaler)
    {
        x *= _scaler;
        y *= _scaler;
        z *= _scaler;
        w *= _scaler;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator * (const f32& _scaler) const
    {
        Vector4 out = *this;
        out *= _scaler;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator *= (const Vector4& _other)
    {
        x *= _other.x;
        y *= _other.y;
        z *= _other.z;
        w *= _other.w;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator * (const Vector4& _other) const
    {
        Vector4 out = *this;
        out *= _other;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator *= (const Matrix& _other)
    {
        *this = *this * _other;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator / (const Vector4& _other) const
    {
        Vector4 out = *this;
        out /= _other;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator /= (const Vector4& _other)
    {
        x /= _other.x;
        y /= _other.y;
        z /= _other.z;
        w /= _other.w;

        return *this;
    }

    FORCE_INLINE Vector4 Vector4::operator / (const f32& _scaler) const
    {
        Vector4 out = *this;
        out /= _scaler;

        return out;
    }

    FORCE_INLINE Vector4& Vector4::operator /= (const f32& _scaler)
    {
        f32 scalerInv = 1.0f / _scaler;
        x *= scalerInv;
        y *= scalerInv;
        z *= scalerInv;
        w *= scalerInv;

        return *this;
    }

    FORCE_INLINE Vector4 operator / (const f32& _a, const Vector4& _b)
    {
        Vector4 out = _b;
        out.x = _a / out.x;
        out.y = _a / out.y;
        out.z = _a / out.z;
        out.w = _a / out.w;

        return out;
    }
}
