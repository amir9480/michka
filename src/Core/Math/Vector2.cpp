#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Michka
{
    const Vector2 Vector2::up       = Vector2( 0.0f, +1.0f);
    const Vector2 Vector2::down     = Vector2( 0.0f, -1.0f);
    const Vector2 Vector2::left     = Vector2(-1.0f,  0.0f);
    const Vector2 Vector2::right    = Vector2(+1.0f,  0.0f);
    const Vector2 Vector2::zero     = Vector2( 0.0f,  0.0f);
    const Vector2 Vector2::one      = Vector2(+1.0f, +1.0f);
    const Vector2 Vector2::infinity = Vector2(Math::infinity, Math::infinity);

    Vector2::operator Vector3 () const
    {
        return Vector3(x, y, 0.0f);
    }

    Vector2::operator Vector4 () const
    {
        return Vector4(x, y, 0.0f);
    }
}
