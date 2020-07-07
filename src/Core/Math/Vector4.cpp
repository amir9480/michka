#include "Vector4.h"

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
}
