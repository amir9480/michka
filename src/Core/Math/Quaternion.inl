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

#include "Michka/Core/Math/Quaternion.h"
#include "Michka/Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Quaternion::Quaternion() :
        x(0.0f),
        y(0.0f),
        z(0.0f),
        w(1.0f)
    {
        //
    }

    FORCE_INLINE Quaternion::Quaternion(const f32& _x, const f32& _y, const f32& _z, const f32& _w) :
        x(_x),
        y(_y),
        z(_z),
        w(_w)
    {
        //
    }

    FORCE_INLINE Quaternion::Quaternion(const Quaternion& _other) :
        x(_other.x),
        y(_other.y),
        z(_other.z),
        w(_other.w)
    {
        //
    }

    FORCE_INLINE Quaternion& Quaternion::conjugate()
    {
        x = -x;
        y = -y;
        z = -z;

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::crossProduct(const Quaternion& _a, const Quaternion& _b)
    {
        return Quaternion(
            _a.w*_b.x + _a.x*_b.w + _a.y*_b.z - _a.z*_b.y,
            _a.w*_b.y + _a.y*_b.w + _a.z*_b.x - _a.x*_b.z,
            _a.w*_b.z + _a.z*_b.w + _a.x*_b.y - _a.y*_b.x,
            _a.w*_b.w - _a.x*_b.x - _a.y*_b.y - _a.z*_b.z
        );
    }

    FORCE_INLINE f32 Quaternion::dotProduct(const Quaternion& _a, const Quaternion& _b)
    {
        return _a.x*_b.x + _a.y*_b.y + _a.z*_b.z + _a.w*_b.w;
    }

    FORCE_INLINE Quaternion Quaternion::getConjugated() const
    {
        Quaternion temp = *this;
        temp.conjugate();

        return temp;
    }

    FORCE_INLINE Quaternion Quaternion::getCrossProduct(const Quaternion& _other) const
    {
        return crossProduct(*this, _other);
    }

    FORCE_INLINE f32 Quaternion::getDotProduct(const Quaternion& _other) const
    {
        return dotProduct(*this, _other);
    }

    FORCE_INLINE Quaternion Quaternion::getInversed() const
    {
        Quaternion temp = *this;
        temp.inverse();

        return temp;
    }

    FORCE_INLINE f32 Quaternion::getLength() const
    {
        return Math::sqrt(x*x + y*y + z*z + w*w);
    }

    FORCE_INLINE Quaternion Quaternion::getNormalized() const
    {
        Quaternion temp = *this;
        temp.normalize();

        return temp;
    }

    FORCE_INLINE f32 Quaternion::getSqauredLength() const
    {
        return x*x + y*y + z*z + w*w;
    }

    FORCE_INLINE bool Quaternion::isIdentity() const
    {
        return *this == identity;
    }

    FORCE_INLINE bool Quaternion::isInversable() const
    {
        return (getSqauredLength() > 0.0f);
    }

    FORCE_INLINE bool Quaternion::isNormalizable() const
    {
        return (getSqauredLength() > 0.0f);
    }

    FORCE_INLINE bool Quaternion::isNormalized() const
    {
        return getSqauredLength() == 1.0f;
    }

    FORCE_INLINE Quaternion Quaternion::lerp(const Quaternion& _a, const Quaternion& _b, const f32& _position, const bool& _shortestPath)
    {
        f32 cosAngle = dotProduct(_a, _b);
        if (cosAngle < 0.0f && _shortestPath)
        {
            return (_a + (_position * (-_b - _a))).getNormalized();
        }
        return (_a + ((_b - _a) * _position)).getNormalized();
    }

    FORCE_INLINE bool Quaternion::normalize()
    {
        f32 length = getLength();
        if(Math::equals(length, 0.0f) == false)
        {
            length = 1.0f / length;
            x *= length;
            y *= length;
            z *= length;
            w *= length;

            return true;
        }

        return false;
    }

    FORCE_INLINE Quaternion& Quaternion::set(const f32& _x, const f32& _y, const f32& _z, const f32& _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;

        return *this;
    }

    FORCE_INLINE Quaternion& Quaternion::operator = (const Quaternion& _other)
    {
        x = _other.x;
        y = _other.y;
        z = _other.z;
        w = _other.w;

        return *this;
    }

    FORCE_INLINE bool Quaternion::operator == (const Quaternion& _other) const
    {
        return (
            Math::equals(x, _other.x),
            Math::equals(y, _other.y),
            Math::equals(z, _other.z),
            Math::equals(w, _other.w)
        );
    }

    FORCE_INLINE bool Quaternion::operator != (const Quaternion& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE f32 Quaternion::operator [] (const u8& _d) const
    {
        return m[_d];
    }

    FORCE_INLINE f32& Quaternion::operator [] (const u8& _d)
    {
        return m[_d];
    }

    FORCE_INLINE Quaternion& Quaternion::operator += (const Quaternion& _other)
    {
        x += _other.x;
        y += _other.y;
        z += _other.z;
        w += _other.w;

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator + (const Quaternion& _other) const
    {
        Quaternion out = *this;
        out += _other;

        return out;
    }

    FORCE_INLINE Quaternion& Quaternion::operator -= (const Quaternion& _other)
    {
        x -= _other.x;
        y -= _other.y;
        z -= _other.z;
        w -= _other.w;

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator - (const Quaternion& _other) const
    {
        Quaternion out = *this;
        out -= _other;

        return out;
    }

    FORCE_INLINE Quaternion& Quaternion::operator *= (const f32& _scaler)
    {
        x *= _scaler;
        y *= _scaler;
        z *= _scaler;
        w *= _scaler;

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator * (const f32& _scaler) const
    {
        Quaternion out = *this;
        out *= _scaler;

        return out;
    }

    FORCE_INLINE Quaternion& Quaternion::operator *= (const Quaternion& _other)
    {
        *this = getCrossProduct(_other);

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator * (const Quaternion& _other) const
    {
        Quaternion out = *this;
        out *= _other;

        return out;
    }

    FORCE_INLINE Quaternion& Quaternion::operator /= (const Quaternion& _other)
    {
        *this *= _other.getInversed();

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator / (const Quaternion& _other) const
    {
        Quaternion out = *this;
        out /= _other;

        return out;
    }

    FORCE_INLINE Quaternion& Quaternion::operator /= (const f32& _scaler)
    {
        x /= _scaler;
        y /= _scaler;
        z /= _scaler;
        w /= _scaler;

        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator / (const f32& _scaler) const
    {
        Quaternion out = *this;
        out /= _scaler;

        return out;
    }

    FORCE_INLINE Quaternion operator * (const f32& _a, const Quaternion& _b)
    {
        return _b * _a;
    }

    FORCE_INLINE Quaternion operator / (const f32& _a, const Quaternion& _b)
    {
        Quaternion out = _b;
        out.x = _a / out.x;
        out.y = _a / out.y;
        out.z = _a / out.z;
        out.w = _a / out.w;

        return out;
    }

    FORCE_INLINE Quaternion Quaternion::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Quaternion Quaternion::operator - () const
    {
        return Quaternion(-x, -y, -z, -w);
    }
}
