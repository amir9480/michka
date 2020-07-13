#include "Matrix.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Matrix3::Matrix3(const Matrix3& _other)
    {
        *this = _other;
    }

    FORCE_INLINE Matrix3 Matrix3::getInversed() const
    {
        Matrix3 temp = *this;
        temp.inverse();

        return temp;
    }

    FORCE_INLINE Matrix3 Matrix3::getInverseTransposed() const
    {
        Matrix3 temp = *this;
        temp.inverse();
        temp.transpose();

        return temp;
    }

    FORCE_INLINE Matrix3 Matrix3::getTransposed() const
    {
        Matrix3 temp = *this;
        temp.transpose();

        return temp;
    }

    FORCE_INLINE bool Matrix3::isIdentity() const
    {
        return *this == identity;
    }

    FORCE_INLINE bool Matrix3::isInversable() const
    {
        return getDeterminant() != 0.0f;
    }

    FORCE_INLINE Matrix3& Matrix3::operator = (const Matrix3& _other)
    {
        memcpy(m, _other.m, sizeof(f32) * 9);
        return *this;
    }

    FORCE_INLINE f32 Matrix3::operator () (const u32& _i, const u32& _j) const
    {
        return m2D[_i][_j];
    }

    FORCE_INLINE f32& Matrix3::operator () (const u32& _i, const u32& _j)
    {
        return m2D[_i][_j];
    }

    FORCE_INLINE f32 Matrix3::operator () (const u32& _i) const
    {
        return m[_i];
    }

    FORCE_INLINE f32& Matrix3::operator () (const u32& _i)
    {
        return m[_i];
    }

    FORCE_INLINE const f32* Matrix3::operator [] (const u32& _i) const
    {
        return m2D[_i];
    }

    FORCE_INLINE f32* Matrix3::operator [] (const u32& _i)
    {
        return m2D[_i];
    }

    FORCE_INLINE bool Matrix3::operator != (const Matrix3& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE Matrix3 Matrix3::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Matrix3& Matrix3::operator += (const Matrix3& _other)
    {
        *this = *this + _other;

        return *this;
    }

    FORCE_INLINE Matrix3& Matrix3::operator -= (const Matrix3& _other)
    {
        *this = *this - _other;

        return *this;
    }

    FORCE_INLINE Matrix3& Matrix3::operator *= (const f32& _scaler)
    {
        *this = *this * _scaler;

        return *this;
    }

    FORCE_INLINE Matrix3& Matrix3::operator *= (const Matrix3& _other)
    {
        *this = *this * _other;

        return *this;
    }
}
