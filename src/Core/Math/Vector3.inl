#include "Vector3.h"
#include "Core/Math/Utility.h"

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

    FORCE_INLINE f32 Vector3::getSqauredLength() const
    {
        return x*x + y*y + z*z;
    }

    FORCE_INLINE bool Vector3::isNormalized() const
    {
        return Math::equals(getSqauredLength(), 1.0f);
    }

    FORCE_INLINE bool Vector3::normalize()
    {
        f32 length = getLength();
        if (length <= 0.0f)
        {
            return false;
        }
        x /= length;
        y /= length;
        z /= length;

        return true;
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
        x /= _scaler;
        y /= _scaler;
        z /= _scaler;

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
