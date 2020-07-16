#include "BoundingBox.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE BoundingBox::BoundingBox() :
        min(Vector3::infinity),
        max(-Vector3::infinity)
    {
        //
    }

    FORCE_INLINE BoundingBox::BoundingBox(const Vector3& _min, const Vector3& _max) :
        min(_min),
        max(_max)
    {
        //
    }

    FORCE_INLINE BoundingBox::BoundingBox(const f32& _min, const f32& _max) :
        min(_min, _min, _min),
        max(_max, _max, _max)
    {
        //
    }

    FORCE_INLINE BoundingBox::BoundingBox(const f32& _min_x, const f32& _min_y, const f32& _min_z, const f32& _max_x, const f32& _max_y, const f32& _max_z) :
        min(_min_x, _min_y, _min_z),
        max(_max_x, _max_y, _max_z)
    {
        //
    }

    FORCE_INLINE BoundingBox::BoundingBox(const BoundingBox& _other) :
        min(_other.min),
        max(_other.max)
    {
        //
    }

    FORCE_INLINE bool BoundingBox::check() const
    {
        return min.x <= max.x && min.y < max.y && min.z < max.z;
    }

    FORCE_INLINE Vector3 BoundingBox::getCenter() const
    {
        return (max + min) * 0.5f;
    }

    FORCE_INLINE BoundingBox BoundingBox::getMerged(const Vector3& _point) const
    {
        BoundingBox self = *this;
        self.merge(_point);

        return self;
    }

    FORCE_INLINE BoundingBox BoundingBox::getMerged(const BoundingBox& _other) const
    {
        BoundingBox self = *this;
        self.merge(_other);

        return self;
    }

    FORCE_INLINE Vector3 BoundingBox::getSizeVector() const
    {
        return max - min;
    }

    FORCE_INLINE BoundingBox BoundingBox::getTransformed(const Matrix3& _matrix) const
    {
        BoundingBox self = *this;
        self.transform(_matrix);

        return self;
    }

    FORCE_INLINE BoundingBox BoundingBox::getTransformed(const Matrix& _matrix) const
    {
        BoundingBox self = *this;
        self.transform(_matrix);

        return self;
    }

    FORCE_INLINE BoundingBox& BoundingBox::merge(const BoundingBox& _box)
    {
        merge(_box.min);
        return merge(_box.max);
    }

    FORCE_INLINE BoundingBox& BoundingBox::set(const Vector3& _min, const Vector3& _max)
    {
        min = _min;
        max = _max;

        return *this;
    }

    FORCE_INLINE BoundingBox& BoundingBox::operator = (const BoundingBox& _other)
    {
        min = _other.min;
        max = _other.max;

        return *this;
    }

    FORCE_INLINE bool BoundingBox::operator == (const BoundingBox& _other) const
    {
        return min == _other.min && max == _other.max;
    }

    FORCE_INLINE bool BoundingBox::operator != (const BoundingBox& _other) const
    {
        return !(*this == _other);
    }
}
