#include "Vector2.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Vector2::Vector2() :
        x(0.0f),
        y(0.0f)
    {
        //
    }

    FORCE_INLINE Vector2::Vector2(const f32& _x, const f32& _y) :
        x(_x),
        y(_y)
    {
        //
    }

    FORCE_INLINE Vector2::Vector2(const Vector2& _other)
    {
        *this = _other;
    }

    FORCE_INLINE f32 Vector2::angle(const Vector2& _a, const Vector2& _b)
    {
        return Math::acos(dotProduct(_a.getNormalized(), _b.getNormalized()));
    }

    FORCE_INLINE f32 Vector2::distance(const Vector2& _a, const Vector2& _b)
    {
        f32 dx = _a.x - _b.x;
        f32 dy = _a.y - _b.y;
        return Math::sqrt(dx*dx + dy*dy);
    }

    FORCE_INLINE f32 Vector2::dotProduct(const Vector2& _a, const Vector2& _b)
    {
        return _a.x*_b.x + _a.y*_b.y;
    }

    FORCE_INLINE f32 Vector2::getAngleFrom(const Vector2& _other) const
    {
        return angle(*this, _other);
    }

    FORCE_INLINE f32 Vector2::getDistanceFrom(const Vector2& _other) const
    {
        return distance(*this, _other);
    }

    FORCE_INLINE f32 Vector2::getDotProduct(const Vector2& _other) const
    {
        return dotProduct(*this, _other);
    }

    FORCE_INLINE f32 Vector2::getLength() const
    {
        return Math::sqrt(x*x + y*y);
    }

    FORCE_INLINE Vector2 Vector2::getNormalized() const
    {
        Vector2 temp = *this;
        if (temp.normalize() == false)
        {
            return zero;
        }

        return temp;
    }

    FORCE_INLINE Vector2 Vector2::getReflected(const Vector2& _normal) const
    {
        return (*this) - (2.0f * dotProduct(*this, _normal) * _normal);
    }

    FORCE_INLINE f32 Vector2::getSqauredLength() const
    {
        return x*x + y*y;
    }

    FORCE_INLINE bool Vector2::isNormalizable() const
    {
        return getLength() > 0.0f;
    }

    FORCE_INLINE bool Vector2::isNormalized() const
    {
        return Math::equals(getSqauredLength(), 1.0f);
    }

    FORCE_INLINE bool Vector2::normalize()
    {
        f32 length = getLength();
        if (length <= 0.0f)
        {
            return false;
        }
        x /= length;
        y /= length;

        return true;
    }

    FORCE_INLINE Vector2& Vector2::reflect(const Vector2& _normal)
    {
        *this = getReflected(_normal);

        return *this;
    }

    FORCE_INLINE Vector2& Vector2::set(const f32& _x, const f32& _y)
    {
        x = _x;
        y = _y;

        return *this;
    }

    FORCE_INLINE Vector2& Vector2::setX(const f32& _x)
    {
        x = _x;
        return *this;
    }

    FORCE_INLINE Vector2& Vector2::setY(const f32& _y)
    {
        y = _y;
        return *this;
    }

    FORCE_INLINE Vector2& Vector2::operator = (const Vector2& _other)
    {
        x = _other.x;
        y = _other.y;

        return *this;
    }

    FORCE_INLINE bool Vector2::operator == (const Vector2& _other) const
    {
        return Math::equals(x, _other.x) && Math::equals(y, _other.y);
    }

    FORCE_INLINE bool Vector2::operator != (const Vector2& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE f32& Vector2::operator [] (const u8& _d)
    {
        return asArray[_d];
    }

    FORCE_INLINE f32 Vector2::operator [] (const u8& _d) const
    {
        return asArray[_d];
    }

    FORCE_INLINE Vector2 Vector2::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator - () const
    {
        return Vector2(-x, -y);
    }

    FORCE_INLINE Vector2& Vector2::operator += (const f32& _scaler)
    {
        x += _scaler;
        y += _scaler;

        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator + (const f32& _scaler) const
    {
        Michka::Vector2 out = *this;
        out += _scaler;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator += (const Vector2& _other)
    {
        x += _other.x;
        y += _other.y;

        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator + (const Vector2& _other) const
    {
        Michka::Vector2 out = *this;
        out += _other;

        return out;
    }

    FORCE_INLINE Vector2 operator + (const f32& _a, const Vector2& _b)
    {
        Michka::Vector2 out = _b;
        out.x = _a + out.x;
        out.y = _a + out.y;

        return out;
    }

    FORCE_INLINE Vector2 Vector2::operator - (const Vector2& _other) const
    {
        Michka::Vector2 out = *this;
        out -= _other;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator -= (const Vector2& _other)
    {
        x -= _other.x;
        y -= _other.y;

        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator - (const f32& _scaler) const
    {
        Michka::Vector2 out = *this;
        out -= _scaler;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator -= (const f32& _scaler)
    {
        x -= _scaler;
        y -= _scaler;

        return *this;
    }

    FORCE_INLINE Vector2 operator - (const f32& _a, const Vector2& _b)
    {
        Michka::Vector2 out = _b;
        out.x = _a - out.x;
        out.y = _a - out.y;

        return out;
    }

    FORCE_INLINE Vector2 operator * (const f32& _a, const Vector2& _b)
    {
        Vector2 out = _b;
        out *= _a;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator *= (const f32& _scaler)
    {
        x *= _scaler;
        y *= _scaler;

        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator * (const f32& _scaler) const
    {
        Vector2 out = *this;
        out *= _scaler;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator *= (const Vector2& _other)
    {
        x *= _other.x;
        y *= _other.y;

        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator * (const Vector2& _other) const
    {
        Vector2 out = *this;
        out *= _other;

        return out;
    }

    FORCE_INLINE Vector2 Vector2::operator / (const Vector2& _other) const
    {
        Vector2 out = *this;
        out /= _other;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator /= (const Vector2& _other)
    {
        x /= _other.x;
        y /= _other.y;

        return *this;
    }

    FORCE_INLINE Vector2 Vector2::operator / (const f32& _scaler) const
    {
        Vector2 out = *this;
        out /= _scaler;

        return out;
    }

    FORCE_INLINE Vector2& Vector2::operator /= (const f32& _scaler)
    {
        x /= _scaler;
        y /= _scaler;

        return *this;
    }

    FORCE_INLINE Vector2 operator / (const f32& _a, const Vector2& _b)
    {
        Vector2 out = _b;
        out.x = _a / out.x;
        out.y = _a / out.y;

        return out;
    }
}