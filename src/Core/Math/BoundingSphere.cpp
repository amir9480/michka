// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
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

#include "BoundingSphere.h"
#include "Core/Container/String.h"
#include "Core/Math/BoundingBox.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Matrix3.h"

namespace Michka
{
    BoundingSphere BoundingSphere::getMerged(const BoundingBox& _box) const
    {
        BoundingSphere self = *this;
        self.merge(_box);

        return self;
    }

    bool BoundingSphere::isInside(const BoundingBox& _box) const
    {
        return
            isInside(_box.min) ||
            isInside(Vector3(_box.min.x, _box.min.y, _box.max.z)) ||
            isInside(Vector3(_box.min.x, _box.max.y, _box.min.z)) ||
            isInside(Vector3(_box.min.x, _box.max.y, _box.max.z)) ||
            isInside(Vector3(_box.max.x, _box.min.y, _box.min.z)) ||
            isInside(Vector3(_box.max.x, _box.min.y, _box.max.z)) ||
            isInside(Vector3(_box.max.x, _box.max.y, _box.min.z)) ||
            isInside(_box.max);
    }

    bool BoundingSphere::isInside(const BoundingSphere& _other) const
    {
        return position.getDistanceFrom(_other.position) <= radius + _other.radius;
    }

    BoundingSphere& BoundingSphere::merge(const Vector3& _point)
    {
        if (radius < 0.0f)
        {
            position = _point;
            radius = 0.0f;
            return *this;
        }
        Vector3 toPoint = _point - position;
        f32 distance = toPoint.getLength();
        if (distance > radius)
        {
            f32 halfRealDistance = (distance - radius) * 0.5f;
            position += toPoint * (halfRealDistance / distance);
            radius += halfRealDistance;
        }

        return *this;
    }

    BoundingSphere& BoundingSphere::merge(const BoundingSphere& _sphere)
    {
        if (radius < 0.0f)
        {
            position = _sphere.position;
            radius = _sphere.radius;
            return *this;
        }
        Vector3 toCenter = _sphere.position - position;
        f32 distance = toCenter.getLength();

        if (distance + _sphere.radius > radius)
        {
            if (distance + radius < _sphere.radius)
            {
                position = _sphere.position;
                radius = _sphere.radius;
            }
            else
            {
                f32 newRadius = (radius + _sphere.radius + distance) * 0.5f;
                position = position + ((toCenter * (newRadius - radius)) / distance);
                radius = newRadius;
            }
        }

        return *this;
    }

    BoundingSphere& BoundingSphere::merge(const BoundingBox& _box)
    {
        merge(_box.min);
        merge(Vector3(_box.min.x, _box.min.y, _box.max.z));
        merge(Vector3(_box.min.x, _box.max.y, _box.min.z));
        merge(Vector3(_box.min.x, _box.max.y, _box.max.z));
        merge(Vector3(_box.max.x, _box.min.y, _box.min.z));
        merge(Vector3(_box.max.x, _box.min.y, _box.max.z));
        merge(Vector3(_box.max.x, _box.max.y, _box.min.z));
        merge(_box.max);

        return *this;
    }

    String BoundingSphere::toString() const
    {
        return "BoundingSphere(position=" + position.toString() + ", radius=" + String::number(radius) + ")";
    }

    BoundingSphere& BoundingSphere::transform(const Matrix3& _matrix)
    {
        position *= _matrix;
        radius *= max(_matrix.m11, _matrix.m22, _matrix.m33);

        return *this;
    }

    BoundingSphere& BoundingSphere::transform(const Matrix& _matrix)
    {
        position *= _matrix;
        radius *= max(_matrix.m11, _matrix.m22, _matrix.m33);

        return *this;
    }
}
