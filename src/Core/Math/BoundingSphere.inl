#include "BoundingSphere.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE BoundingSphere::BoundingSphere() :
        radius(-Math::infinity)
    {
        //
    }

    FORCE_INLINE BoundingSphere::BoundingSphere(const BoundingSphere& _other) :
        position(_other.position),
        radius(_other.radius)
    {
        //
    }

    FORCE_INLINE BoundingSphere::BoundingSphere(const Vector3& _position, const f32& _radius) :
        position(_position),
        radius(_radius)
    {
        //
    }

    FORCE_INLINE BoundingSphere BoundingSphere::getMerged(const Vector3& _point) const
    {
        BoundingSphere self = *this;
        self.merge(_point);

        return self;
    }

    FORCE_INLINE BoundingSphere BoundingSphere::getMerged(const BoundingSphere& _other) const
    {
        BoundingSphere self = *this;
        self.merge(_other);

        return self;
    }

    FORCE_INLINE BoundingSphere BoundingSphere::getTransformed(const Matrix3& _matrix) const
    {
        BoundingSphere self = *this;
        self.transform(_matrix);

        return self;
    }

    FORCE_INLINE BoundingSphere BoundingSphere::getTransformed(const Matrix& _matrix) const
    {
        BoundingSphere self = *this;
        self.transform(_matrix);

        return self;
    }

    FORCE_INLINE bool BoundingSphere::isInside(const Vector3& _point) const
    {
        return position.getDistanceFrom(_point) <= radius;
    }

    FORCE_INLINE BoundingSphere& BoundingSphere::set(const Vector3& _position, const f32& _radius)
    {
        position = _position;
        radius = _radius;

        return *this;
    }

    FORCE_INLINE BoundingSphere& BoundingSphere::operator = (const BoundingSphere& _other)
    {
        position = _other.position;
        radius = _other.radius;

        return *this;
    }

    FORCE_INLINE bool BoundingSphere::operator == (const BoundingSphere& _other) const
    {
        return Math::equals(radius, _other.radius) && position == _other.position;
    }

    FORCE_INLINE bool BoundingSphere::operator != (const BoundingSphere& _other) const
    {
        return !(*this == _other);
    }
}
