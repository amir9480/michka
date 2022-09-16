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

#ifndef __RAY_H__
#define __RAY_H__

#include "Core/Helpers.h"
#include "Vector3.h"

namespace Michka
{
    class BoundingBox;
    class BoundingSphere;
    class Plane;

    class MICHKA_API Ray
    {
        MICHKA_CLASS();
    public:
        FORCE_INLINE Ray();
        FORCE_INLINE Ray(const Vector3& _position, const Vector3& _direction);

        /**
         * @brief Get the normalized copy of this ray.
         */
        FORCE_INLINE Ray getNormalized() const;

        /**
         * @brief Get the point along ray with specific distance.
         *
         * @param _distance
         */
        FORCE_INLINE Vector3 getPoint(const f32& _distance) const;

        /**
         * @brief Check ray intersects plane.
         *
         * @param _plane
         * @return distance to hit position. infinity if has no intersection.
         */
        f32 isIntersects(const Plane& _plane) const;

        /**
         * @brief Check ray intersects bounding box.
         *
         * @param _box
         * @return distance to hit position. infinity if has no intersection.
         */
        f32 isIntersects(const BoundingBox& _box) const;

        /**
         * @brief Check ray intersects bounding plane.
         *
         * @param _sphere
         * @return distance to hit position. infinity if has no intersection.
         */
        f32 isIntersects(const BoundingSphere& _sphere) const;

        /**
         * @brief Normalize ray direction vector.
         *
         * @return Self
         */
        FORCE_INLINE Ray& normalize();

        /**
         * @brief Set the position of ray.
         *
         * @param _position
         * @return Self
         */
        FORCE_INLINE Ray& setPosition(const Vector3& _position);

        /**
         * @brief Set the direction of ray.
         *
         * @param _position
         * @return Self
         */
        FORCE_INLINE Ray& setDirection(const Vector3& _direction);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Ray& operator = (const Ray& _other);

        FORCE_INLINE bool operator == (const Ray& _other) const;
        FORCE_INLINE bool operator != (const Ray& _other) const;

    public:
        Vector3 position;
        Vector3 direction;
    };
}

#include "Ray.inl"

#endif // __RAY_H__
