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

#include "Ray.h"
#include "Core/Container/String.h"
#include "Core/Math/BoundingBox.h"
#include "Core/Math/BoundingSphere.h"
#include "Core/Math/Plane.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    f32 Ray::isIntersects(const Plane& _plane) const
    {
        f32 directionDotPlaneNormal = direction.getDotProduct(_plane.normal);
        if(directionDotPlaneNormal == 0.0f)
        {
            return Math::infinity;
        }
        return (_plane.d - position.getDotProduct(_plane.normal)) / directionDotPlaneNormal;
    }

    f32 Ray::isIntersects(const BoundingBox& _box) const
    {
        Vector3 directionInv = 1.0f / direction;
        f32 t1 = (_box.min.x - direction.x) * directionInv.x;
        f32 t2 = (_box.max.x - direction.x) * directionInv.x;
        f32 t3 = (_box.min.y - direction.y) * directionInv.y;
        f32 t4 = (_box.max.y - direction.y) * directionInv.y;
        f32 t5 = (_box.min.z - direction.z) * directionInv.z;
        f32 t6 = (_box.max.z - direction.z) * directionInv.z;

        f32 tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
        f32 tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

        if (tmax < 0)
        {
            return Math::infinity;
        }
        if (tmin > tmax)
        {
            return Math::infinity;
        }

        return tmax;
    }

    f32 Ray::isIntersects(const BoundingSphere& _sphere) const
    {
        // Adapted from: http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
        Vector3 diff = position - _sphere.position;
        Vector3 _direction = direction;
        if (position.getDistanceFrom(_sphere.position) < _sphere.radius)
        {
            diff = -diff;
        }
        f32 a = direction.getDotProduct(direction);
        f32 b = 2.0f * diff.getDotProduct(direction);
        f32 c = diff.getDotProduct(diff) - _sphere.radius*_sphere.radius;
        f32 d = b*b - 4.0f*a*c;
        if (d < 0.0f)
        {
            return Math::infinity;
        }

        f32 distance = (-b - Math::sqrt(d)) / 2.0f*a;
        if (distance < 0.0f)
        {
            if (position.getDistanceFrom(_sphere.position) < _sphere.radius)
            {
                return -distance;
            }
            return INFINITY;
        }

        return distance;
    }

    String Ray::toString() const
    {
        return "Ray(position=" + position.toString() + ", direction=" + direction.toString() + ")";
    }
}
