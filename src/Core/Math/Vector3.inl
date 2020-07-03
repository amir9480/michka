#include "Vector3.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Vector3::Vector3()
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
        switch(_d)
        {
        case 1:
            return y;
        case 2:
            return z;
        }
        return x;
    }

    FORCE_INLINE f32 Vector3::operator [] (const u8& _d) const
    {
        switch(_d)
        {
        case 1:
            return y;
        case 2:
            return z;
        }
        return x;
    }

    FORCE_INLINE Vector3 Vector3::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Vector3 Vector3::operator - () const
    {
        return Vector3(-x, -y, -z);
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
}
