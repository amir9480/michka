#include "Matrix.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Matrix::Matrix(const Matrix& _other)
    {
        *this = _other;
    }

    FORCE_INLINE Matrix Matrix::getInversed() const
    {
        Matrix temp = *this;
        temp.inverse();

        return temp;
    }

    FORCE_INLINE Matrix Matrix::getInverseTransposed() const
    {
        Matrix temp = *this;
        temp.inverse();
        temp.transpose();

        return temp;
    }

    FORCE_INLINE Matrix Matrix::getTransposed() const
    {
        Matrix temp = *this;
        temp.transpose();

        return temp;
    }

    FORCE_INLINE bool Matrix::isIdentity() const
    {
        return *this == identity;
    }

    FORCE_INLINE bool Matrix::isInversable() const
    {
        return getDeterminant() != 0.0f;
    }

    FORCE_INLINE Matrix& Matrix::operator = (const Matrix& _other)
    {
        memcpy(m, _other.m, sizeof(f32) * 16);
        return *this;
    }

    FORCE_INLINE f32 Matrix::operator () (const u32& _i, const u32& _j) const
    {
        return m2D[_i][_j];
    }

    FORCE_INLINE f32& Matrix::operator () (const u32& _i, const u32& _j)
    {
        return m2D[_i][_j];
    }

    FORCE_INLINE f32 Matrix::operator () (const u32& _i) const
    {
        return m[_i];
    }

    FORCE_INLINE f32& Matrix::operator () (const u32& _i)
    {
        return m[_i];
    }

    FORCE_INLINE const f32* Matrix::operator [] (const u32& _i) const
    {
        return m2D[_i];
    }

    FORCE_INLINE f32* Matrix::operator [] (const u32& _i)
    {
        return m2D[_i];
    }

    FORCE_INLINE bool Matrix::operator != (const Matrix& _other) const
    {
        return !(*this == _other);
    }

    FORCE_INLINE Matrix Matrix::operator + () const
    {
        return *this;
    }

    FORCE_INLINE Matrix& Matrix::operator += (const Matrix& _other)
    {
        *this = *this + _other;

        return *this;
    }

    FORCE_INLINE Matrix& Matrix::operator -= (const Matrix& _other)
    {
        *this = *this - _other;

        return *this;
    }

    FORCE_INLINE Matrix& Matrix::operator *= (const f32& _scaler)
    {
        *this = *this * _scaler;

        return *this;
    }

    FORCE_INLINE Matrix& Matrix::operator *= (const Matrix& _other)
    {
        *this = *this * _other;

        return *this;
    }
}
