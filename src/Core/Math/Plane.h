// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2021 amir alizadeh.                                          //
//                                                                                 //
// Permission is hereby granted, free of charge, to any person obtaining a copy    //
// of this software and associated documentation files (the "Software"), to deal   //
// in the Software without restriction, including without limitation the rights    //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       //
// copies of the Software, and to permit persons to whom the Software is           //
// furnished to do so, subject to the following conditions:                        //
//                                                                                 //
// The above copyright notice and this permission notice shall be included in all  //
// copies or substantial portions of the Software.                                 //
//                                                                                 //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
// SOFTWARE.                                                                       //
// ------------------------------------------------------------------------------- //

#ifndef __PLANE_H__
#define __PLANE_H__

#include "Core/Helpers.h"
#include "Vector3.h"
#include "Utility.h"
#include "MichkaGenerated/Core/Math/Plane.generated.h"

namespace Michka
{
    class BoundingBox;
    class BoundingSphere;
    class Matrix;

    class MICHKA_API Plane
    {
        MICHKA_CLASS(Plane);
    public:
        FORCE_INLINE Plane();
        FORCE_INLINE Plane(const Vector3& _position, const Vector3& _normal);
        FORCE_INLINE Plane(const Vector3& _point1, const Vector3& _point2, const Vector3& _point3);
        FORCE_INLINE Plane(const f32& _a, const f32& _b, const f32& _c, const f32& _d);
        FORCE_INLINE Plane(const Plane& _other);

        /**
         * @brief Get the normal direction of plane.
         */
        FORCE_INLINE Vector3 getNormal() const;

        /**
         * @brief Get the normaled copy of this plane.
         */
        FORCE_INLINE Plane getNormalized() const;

        /**
         * @brief Get the distance from \a _position .
         *
         * @param _position
         */
        FORCE_INLINE f32 getDistanceFrom(const Vector3& _position) const;

        /**
         * @brief Get the position of plane.
         */
        FORCE_INLINE Vector3 getPosition() const;

        /**
         * @brief Get the Projected point on plane.
         *
         * @param _position
         */
        FORCE_INLINE Vector3 getProjected(const Vector3& _position) const;

        /**
         * @brief Get the Reflected point based on plane.
         *
         * @param _position
         */
        FORCE_INLINE Vector3 getReflected(const Vector3& _position) const;

        /**
         * @brief Get the reflection as matrix.
         */
        Matrix getReflectionMatrix() const;

        /**
         * @brief Get a position is in which side of plane.
         *
         * @param _position
         */
        FORCE_INLINE Side getSide(const Vector3& _position) const;

        /**
         * @brief Check plane intersects bounding box.
         *
         * @param _box
         */
        bool isIntersects(const BoundingBox& _box) const;

        /**
         * @brief Check plane intersects bounding sphere.
         *
         * @param _sphere
         */
        bool isIntersects(const BoundingSphere& _sphere) const;

        /**
         * @brief Check two diffrent points are in same side of plane.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE bool isSameSide(const Vector3& _a, const Vector3& _b);

        /**
         * @brief Normalize plane.
         *
         * @return Self
         */
        FORCE_INLINE Plane& normalize();

        /**
         * @brief Set from a position and a normal vector.
         *
         * @param _position
         * @param _normal
         * @return Self
         */
        FORCE_INLINE Plane& set(const Vector3& _position, const Vector3& _normal);

        /**
         * @brief Set from three points which creating plane.
         *
         * @param _point1
         * @param _point2
         * @param _point3
         * @return Self
         */
        FORCE_INLINE Plane& set(const Vector3& _point1, const Vector3& _point2, const Vector3& _point3);

        /**
         * @brief Set directly.
         *
         * @param _a
         * @param _b
         * @param _c
         * @param _d
         * @return Self
         */
        FORCE_INLINE Plane& set(const f32& _a, const f32& _b, const f32& _c, const f32& _d);

        /**
         * @brief Calculate d from _position.
         *
         * @param _position
         * @return Self
         */
        FORCE_INLINE Plane& setPosition(const Vector3& _position);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Plane& operator = (const Plane& _other);

        FORCE_INLINE bool operator == (const Plane& _other) const;
        FORCE_INLINE bool operator != (const Plane& _other) const;

    public:
        union
        {
            struct
            {
                f32 a, b, c;
            };
            Vector3 normal;
        };
        f32 d;
    };
}

#include "Plane.inl"

#endif // __PLANE_H__
