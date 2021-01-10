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

#ifndef __BOUNDING_BOX_H__
#define __BOUNDING_BOX_H__

#include "Core/Defines.h"
#include "Utility.h"
#include "Vector3.h"

namespace Michka
{
    class BoundingSphere;
    class Matrix3;
    class Matrix;
    class Plane;

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
        FORCE_INLINE Vector3 getCorner(const Corner& _corner) const;

        /**
         * @brief Get intersection status to another bounding box.
         *
         * @param _other
         */
        Intersection getIntersection(const BoundingBox& _other) const;

        /**
         * @brief Get the copy of this merged with \a _point.
         *
         * @param _point
         */
        FORCE_INLINE BoundingBox getMerged(const Vector3& _point) const;

        /**
         * @brief Get the copy of this merged with \a _other box.
         *
         * @param _other
         */
        FORCE_INLINE BoundingBox getMerged(const BoundingBox& _other) const;

        /**
         * @brief Get size vector. a vector from min to max.
         */
        FORCE_INLINE Vector3 getSizeVector() const;

        /**
         * @brief Get transformed copy of this bounding box.
         *
         * @param _matrix
         */
        FORCE_INLINE BoundingBox getTransformed(const Matrix3& _matrix) const;
        FORCE_INLINE BoundingBox getTransformed(const Matrix& _matrix) const;

        /**
         * @brief Is a point inside this box.
         *
         * @param _point
         */
        bool isInside(const Vector3& _point) const;

        /**
         * @brief Is another box inside this box partially/completely.
         *
         * @param _other
         */
        bool isInside(const BoundingBox& _other) const;

        /**
         * @brief Is a sphere inside this box partially/completely.
         *
         * @param _sphere
         */
        bool isInside(const BoundingSphere& _sphere) const;

        /**
         * @brief Check bounding box intersects plane.
         *
         * @param _plane
         */
        bool isIntersects(const Plane& _plane) const;

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
        FORCE_INLINE BoundingBox& set(const Vector3& _min = Vector3::infinity, const Vector3& _max = -Vector3::infinity);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        /**
         * @brief Transform bounding box using a matrix.
         *
         * @param _matrix
         * @return Self
         */
        BoundingBox& transform(const Matrix3& _matrix);
        BoundingBox& transform(const Matrix& _matrix);

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
