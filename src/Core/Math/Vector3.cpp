#include "Vector3.h"

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
}
