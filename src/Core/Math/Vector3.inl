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

#include "Michka/Core/Math/Vector3.h"
#include "Michka/Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Vector3::Vector3() :
        x(0.0f),
        y(0.0f),
        z(0.0f)
    {
        //
    }

    FORCE_INLINE Vector3::Vector3(const f32& _x, const f32& _y, const f32& _z) :
        x(_x),
        y(_y),
        z(_z)
    {
        //
    }

    FORCE_INLINE Vector3::Vector3(const Vector3& _other)
    {
        *this = _other;
    }

    FORCE_INLINE f32 Vector3::angle(const Vector3& _a, const Vector3& _b)
    {
        return Math::acos(dotProduct(_a.getNormalized(), _b.getNormalized()));
    }

    FORCE_INLINE Vector3 Vector3::crossProduct(const Vector3& _a, const Vector3& _b)
    {
        return Vector3(
             (_a.y*_b.z - _a.z*_b.y),
            -(_a.x*_b.z - _a.z*_b.x),
             (_a.x*_b.y - _a.y*_b.x)
        );
    }

    FORCE_INLINE f32 Vector3::distance(const Vector3& _a, const Vector3& _b)
    {
        f32 dx = _a.x - _b.x;
        f32 dy = _a.y - _b.y;
        f32 dz = _a.z - _b.z;
        return Math::sqrt(dx*dx + dy*dy + dz*dz);
    }

    FORCE_INLINE f32 Vector3::dotProduct(const Vector3& _a, const Vector3& _b)
    {
        return _a.x*_b.x + _a.y*_b.y + _a.z*_b.z;
    }

    FORCE_INLINE f32 Vector3::getAngleFrom(const Vector3& _other) const
    {
        return angle(*this, _other);
    }

    FORCE_INLINE Vector3 Vector3::getCrossProduct(const Vector3& _other) const
    {
        return crossProduct(*this, _other);
    }

    FORCE_INLINE f32 Vector3::getDistanceFrom(const Vector3& _other) const
    {
        return distance(*this, _other);
    }

    FORCE_INLINE f32 Vector3::getDotProduct(const Vector3& _other) const
    {
        return dotProduct(*this, _other);
    }

    FORCE_INLINE f32 Vector3::getLength() const
    {
        return Math::sqrt(x*x + y*y + z*z);
    }

    FORCE_INLINE Vector3 Vector3::getNormalized() const
    {
        Vector3 temp = *this;
        if (temp.normalize() == false)
        {
            return zero;
        }

        return temp;
    }

    FORCE_INLINE Vector3 Vector3::getReflected(const Vector3& _normal) const
    {
        return (*this) - (2.0f * dotProduct(*this, _normal) * _normal);
    }

    FORCE_INLINE f32 Vector3::getSqauredLength() const
    {
        return x*x + y*y + z*z;
    }

    FORCE_INLINE bool Vector3::isNormalizable() const
    {
        return getLength() > 0.0f;
    }

    FORCE_INLINE bool Vector3::isNormalized() const
    {
        return Math::equals(getSqauredLength(), 1.0f);
    }

    FORCE_INLINE Vector3 Vector3::lerp(const Vector3& _a, const Vector3& _b, const f32& _position)
    {
        return _a + (_position * (_b - _a));
    }

    FORCE_INLINE bool Vector3::normalize()
    {
        f32 length = getLength();
        if (length <= 0.0f)
        {
            return false;
        }
        f32 lengthInv = 1.0f / length;
        x *= lengthInv;
        y *= lengthInv;
        z *= lengthInv;

        return true;
    }

    FORCE_INLINE Vector3& Vector3::reflect(const Vector3& _normal)
    {
        *this = getReflected(_normal);

        return *this;
    }

    FORCE_INLINE Vector3& Vector3::set(const f32& _x, const f32& _y, const f32& _z)
    {
        x = _x;
        y = _y;
        z = _z;

        return *this;
    }

    FORCE_INLINE Vector3& Vector3::setX(const f32& _x)
    {
        x = _x;
        return *this;
    }

    FORCE_INLINE Vector3& Vector3::setY(const f32& _y)
    {
        y = _y;
        return *this;
    }

    FORCE_INLINE Vector3& Vector3::setZ(const f32& _z)
    {
        z = _z;
        return *this;
    }

    FORCE_INLINE Vector3& Vector3::operator = (const Vector3& _other)
    {
        x = _other.x;
        y = _other.y;
        z = _other.z;

        return *this;
    }

    FORCE_INLINE bool Vector3::operator == (const Vector3& _other) const
    {
        return Math::equals(x, _other.x) && Math::equals(y, _other.y) && Math::equals(z, _other.z);
    }

    FORCE_INLINE bool Vector3::operator != (const Vector3& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE f32& Vector3::operator [] (const u8& _d)
    {
        return asArray[_d];
    }

    FORCE_INLINE f32 Vector3::operator [] (const u8& _d) const
    {
        return asArray[_d];
    }

    FORCE_INLINE Vector3 Vector3::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator - () const
    {
        return Vector3(-x, -y, -z);
    }

    FORCE_INLINE Vector3& Vector3::operator += (const f32& _scaler)
    {
        x += _scaler;
        y += _scaler;
        z += _scaler;

        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator + (const f32& _scaler) const
    {
        Michka::Vector3 out = *this;
        out += _scaler;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator += (const Vector3& _other)
    {
        x += _other.x;
        y += _other.y;
        z += _other.z;

        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator + (const Vector3& _other) const
    {
        Michka::Vector3 out = *this;
        out += _other;

        return out;
    }

    FORCE_INLINE Vector3 operator + (const f32& _a, const Vector3& _b)
    {
        Michka::Vector3 out = _b;
        out.x = _a + out.x;
        out.y = _a + out.y;
        out.z = _a + out.z;

        return out;
    }

    FORCE_INLINE Vector3 Vector3::operator - (const Vector3& _other) const
    {
        Michka::Vector3 out = *this;
        out -= _other;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator -= (const Vector3& _other)
    {
        x -= _other.x;
        y -= _other.y;
        z -= _other.z;

        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator - (const f32& _scaler) const
    {
        Michka::Vector3 out = *this;
        out -= _scaler;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator -= (const f32& _scaler)
    {
        x -= _scaler;
        y -= _scaler;
        z -= _scaler;

        return *this;
    }

    FORCE_INLINE Vector3 operator - (const f32& _a, const Vector3& _b)
    {
        Michka::Vector3 out = _b;
        out.x = _a - out.x;
        out.y = _a - out.y;
        out.z = _a - out.z;

        return out;
    }

    FORCE_INLINE Vector3 operator * (const f32& _a, const Vector3& _b)
    {
        Vector3 out = _b;
        out *= _a;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator *= (const f32& _scaler)
    {
        x *= _scaler;
        y *= _scaler;
        z *= _scaler;

        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator * (const f32& _scaler) const
    {
        Vector3 out = *this;
        out *= _scaler;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator *= (const Vector3& _other)
    {
        x *= _other.x;
        y *= _other.y;
        z *= _other.z;

        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator * (const Vector3& _other) const
    {
        Vector3 out = *this;
        out *= _other;

        return out;
    }

    FORCE_INLINE Vector3 Vector3::operator / (const Vector3& _other) const
    {
        Vector3 out = *this;
        out /= _other;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator /= (const Vector3& _other)
    {
        x /= _other.x;
        y /= _other.y;
        z /= _other.z;

        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator / (const f32& _scaler) const
    {
        Vector3 out = *this;
        out /= _scaler;

        return out;
    }

    FORCE_INLINE Vector3& Vector3::operator /= (const f32& _scaler)
    {
        f32 scalerInv = 1.0f / _scaler;
        x *= scalerInv;
        y *= scalerInv;
        z *= scalerInv;

        return *this;
    }

    FORCE_INLINE Vector3 operator / (const f32& _a, const Vector3& _b)
    {
        Vector3 out = _b;
        out.x = _a / out.x;
        out.y = _a / out.y;
        out.z = _a / out.z;

        return out;
    }
}
