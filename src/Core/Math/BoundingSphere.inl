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
