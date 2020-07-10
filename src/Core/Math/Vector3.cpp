#include "Vector3.h"
#include "Matrix.h"

namespace Michka
{
    const Vector3 Vector3::up      = Vector3( 0.0f, +1.0f,  0.0f);
    const Vector3 Vector3::down    = Vector3( 0.0f, -1.0f,  0.0f);
    const Vector3 Vector3::left    = Vector3(-1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::right   = Vector3(+1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::forward = Vector3( 0.0f,  0.0f, +1.0f);
    const Vector3 Vector3::back    = Vector3( 0.0f,  0.0f, -1.0f);
    const Vector3 Vector3::zero    = Vector3( 0.0f,  0.0f,  0.0f);
    const Vector3 Vector3::one     = Vector3(+1.0f, +1.0f, +1.0f);

    Vector3& Vector3::operator *= (const Matrix& _other)
    {
        *this = *this * _other;

        return *this;
    }

    Vector3 Vector3::operator * (const Matrix& _other) const
    {
        return Vector3(
            x*_other.m11 + y*_other.m21 + z*_other.m31 + _other.m41,
            x*_other.m12 + y*_other.m22 + z*_other.m32 + _other.m42,
            x*_other.m13 + y*_other.m23 + z*_other.m33 + _other.m43
        );
    }
}
