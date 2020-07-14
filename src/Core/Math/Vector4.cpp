#include "Vector4.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"

namespace Michka
{
    const Vector4 Vector4::up      = Vector4( 0.0f, +1.0f,  0.0f);
    const Vector4 Vector4::down    = Vector4( 0.0f, -1.0f,  0.0f);
    const Vector4 Vector4::left    = Vector4(-1.0f,  0.0f,  0.0f);
    const Vector4 Vector4::right   = Vector4(+1.0f,  0.0f,  0.0f);
    const Vector4 Vector4::forward = Vector4( 0.0f,  0.0f, +1.0f);
    const Vector4 Vector4::back    = Vector4( 0.0f,  0.0f, -1.0f);
    const Vector4 Vector4::zero    = Vector4( 0.0f,  0.0f,  0.0f);
    const Vector4 Vector4::one     = Vector4(+1.0f, +1.0f, +1.0f);

    Vector4 Vector4::operator * (const Matrix& _other) const
    {
        return Vector4(
            x*_other.m11 + y*_other.m21 + z*_other.m31 + w*_other.m41,
            x*_other.m12 + y*_other.m22 + z*_other.m32 + w*_other.m42,
            x*_other.m13 + y*_other.m23 + z*_other.m33 + w*_other.m43,
            x*_other.m14 + y*_other.m24 + z*_other.m34 + w*_other.m44
        );
    }

    Vector4::operator Vector3 () const
    {
        f32 wInv = 1.0f / w;
        return Vector3(x * wInv, y * wInv, z * wInv);
    }
}
