#ifndef __BOUNDING_BOX_H__
#define __BOUNDING_BOX_H__

#include "Core/Defines.h"
#include "Vector3.h"

namespace Michka
{
    class MICHKA_API BoundingBox
    {
    public:
        enum Corner
        {
            leftDownBack,
            leftDownForward,
            leftUpBack,
            leftUpForward,
            rightDownBack,
            rightDownForward,
            rightUpBack,
            rightUpForward
        };
    public:
        FORCE_INLINE BoundingBox();
        FORCE_INLINE BoundingBox(const Vector3& _min, const Vector3& _max);
        FORCE_INLINE BoundingBox(const f32& _min, const f32& _max);
        FORCE_INLINE BoundingBox(const f32& _min_x, const f32& _min_y, const f32& _min_z, const f32& _max_x, const f32& _max_y, const f32& _max_z);
        FORCE_INLINE BoundingBox(const BoundingBox& _other);

        /**
         * @brief Check bounding box values are valid.
         */
        FORCE_INLINE bool check() const;

        /**
         * @brief Fix unvalid bounding box.
         *
         * @return Self
         */
        BoundingBox& fix();

        /**
         * @brief Get the center of the bounding box.
         *
         * @return Vector3
         */
        FORCE_INLINE Vector3 getCenter() const;

        /**
         * @brief Get position of specific corner of box.
         *
         * @param _corner
         */
        Vector3 getCorner(const Corner& _corner) const;

        /**
         * @brief Merge a point to bounding box.
         *
         * @param _point
         * @return Self
         */
        BoundingBox& merge(const Vector3& _point);

        /**
         * @brief Merge another bounding box to this bounding box.
         *
         * @param _box
         * @return Self
         */
        FORCE_INLINE BoundingBox& merge(const BoundingBox& _box);

        /**
         * @brief Set bounding box value.
         *
         * @param _min
         * @param _max
         * @return Self
         */
        FORCE_INLINE BoundingBox& set(const Vector3& _min, const Vector3& _max);

        FORCE_INLINE BoundingBox& operator = (const BoundingBox& _other);

        FORCE_INLINE bool operator == (const BoundingBox& _other) const;
        FORCE_INLINE bool operator != (const BoundingBox& _other) const;
    public:
        Vector3 min;
        Vector3 max;
    };
}

#include "BoundingBox.inl"

#endif // __BOUNDING_BOX_H__
