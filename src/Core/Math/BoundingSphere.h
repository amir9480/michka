#ifndef __BOUNDING_SPHERE_H__
#define __BOUNDING_SPHERE_H__

#include "Core/Defines.h"
#include "Core/Math/Vector3.h"

namespace Michka
{
    class BoundingBox;
    class Matrix3;
    class Matrix;

    class MICHKA_API BoundingSphere
    {
    public:
        FORCE_INLINE BoundingSphere();
        FORCE_INLINE BoundingSphere(const Vector3& _position, const f32& _radius);
        FORCE_INLINE BoundingSphere(const BoundingSphere& _other);

        /**
         * @brief Get the copy of this merged with \a _point.
         *
         * @param _point
         */
        FORCE_INLINE BoundingSphere getMerged(const Vector3& _point) const;

        /**
         * @brief Get the copy of this merged with \a _other sphere.
         *
         * @param _other
         */
        FORCE_INLINE BoundingSphere getMerged(const BoundingSphere& _other) const;

        /**
         * @brief Get the copy of this merged with \a _box .
         *
         * @param _box
         */
        BoundingSphere getMerged(const BoundingBox& _box) const;

        /**
         * @brief Get transformed copy of this bounding box.
         *
         * @param _matrix
         */
        FORCE_INLINE BoundingSphere getTransformed(const Matrix3& _matrix) const;
        FORCE_INLINE BoundingSphere getTransformed(const Matrix& _matrix) const;

        /**
         * @brief Is a point inside this sphere.
         *
         * @param _point
         */
        FORCE_INLINE bool isInside(const Vector3& _point) const;

        /**
         * @brief Is a box inside this sphere partially/completely.
         *
         * @param _box
         */
        bool isInside(const BoundingBox& _box) const;

        /**
         * @brief Is a sphere inside this sphere partially/completely.
         *
         * @param _other
         */
        bool isInside(const BoundingSphere& _other) const;

        /**
         * @brief Merge a point to bounding sphere.
         *
         * @param _point
         * @return Self
         */
        BoundingSphere& merge(const Vector3& _point);

        /**
         * @brief Merge another bounding sphere to this bounding sphere.
         *
         * @param _sphere
         * @return Self
         */
        BoundingSphere& merge(const BoundingSphere& _sphere);

        /**
         * @brief Merge a bounding box to this bounding sphere.
         *
         * @param _box
         * @return Self
         */
        BoundingSphere& merge(const BoundingBox& _box);

        /**
         * @brief Set bounding sphere value.
         *
         * @param _position
         * @param _radius
         * @return Self
         */
        FORCE_INLINE BoundingSphere& set(const Vector3& _position = Michka::Vector3::zero, const f32& _radius = -Math::infinity);

        /**
         * @brief Transform bounding box using a matrix.
         *
         * @param _matrix
         * @return Self
         */
        BoundingSphere& transform(const Matrix3& _matrix);
        BoundingSphere& transform(const Matrix& _matrix);

        FORCE_INLINE BoundingSphere& operator = (const BoundingSphere& _other);

        FORCE_INLINE bool operator == (const BoundingSphere& _other) const;
        FORCE_INLINE bool operator != (const BoundingSphere& _other) const;
    public:
        Vector3 position;
        f32 radius = 1.0f;
    };
}

#include "BoundingSphere.inl"

#endif // __BOUNDING_SPHERE_H__
