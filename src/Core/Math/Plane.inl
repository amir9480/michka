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

#include "Plane.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Plane::Plane() :
        normal(Vector3::zero),
        d(0.0f)
    {
        //
    }

    FORCE_INLINE Plane::Plane(const Vector3& _position, const Vector3& _normal)
    {
        set(_position, _normal);
    }

    FORCE_INLINE Plane::Plane(const Vector3& _point1, const Vector3& _point2, const Vector3& _point3)
    {
        set(_point1, _point2, _point3);
    }

    FORCE_INLINE Plane::Plane(const f32& _a, const f32& _b, const f32& _c, const f32& _d)
    {
        set(_a, _b, _c, _d);
    }

    FORCE_INLINE Plane::Plane(const Plane& _other) :
        normal(_other.normal),
        d(_other.d)
    {
        //
    }

    FORCE_INLINE Plane& Plane::setPosition(const Vector3& _position)
    {
        d = normal.getDotProduct(_position);

        return *this;
    }

    FORCE_INLINE Vector3 Plane::getNormal() const
    {
        return normal;
    }

    FORCE_INLINE Plane Plane::getNormalized() const
    {
        Plane self = *this;
        self.normalize();

        return self;
    }

    FORCE_INLINE f32 Plane::getDistanceFrom(const Vector3& _position) const
    {
        return normal.getDotProduct(_position) - d;
    }

    FORCE_INLINE Vector3 Plane::getPosition() const
    {
        return normal * d;
    }

    FORCE_INLINE Vector3 Plane::getProjected(const Vector3& _position) const
    {
        return _position - (normal * getDistanceFrom(_position));
    }

    FORCE_INLINE Vector3 Plane::getReflected(const Vector3& _position) const
    {
        return _position - (normal * getDistanceFrom(_position) * 2.0f);
    }

    FORCE_INLINE Side Plane::getSide(const Vector3& _position) const
    {
        f32 distance = getDistanceFrom(_position);

        if (distance >= Math::epsilon)
        {
            return Side::front;
        }
        else if (distance <= -Math::epsilon)
        {
            return Side::back;
        }

        return Side::on;
    }

    FORCE_INLINE bool Plane::isSameSide(const Vector3& _a, const Vector3& _b)
    {
        return Math::sign(getDistanceFrom(_a)) == Math::sign(getDistanceFrom(_b));
    }

    FORCE_INLINE Plane& Plane::normalize()
    {
        d /= normal.getLength();
        normal.normalize();

        return *this;
    }

    FORCE_INLINE Plane& Plane::set(const Vector3& _position, const Vector3& _normal)
    {
        normal = _normal;
        setPosition(_position);

        return *this;
    }

    FORCE_INLINE Plane& Plane::set(const Vector3& _point1, const Vector3& _point2, const Vector3& _point3)
    {
        Vector3 j = _point2 - _point1;
        Vector3 k = _point2 - _point3;
        normal = j.getCrossProduct(k);
        setPosition(_point2);

        return *this;
    }

    FORCE_INLINE Plane& Plane::set(const f32& _a, const f32& _b, const f32& _c, const f32& _d)
    {
        a = _a;
        b = _b;
        c = _c;
        d = _d;

        return *this;
    }

    FORCE_INLINE Plane& Plane::operator = (const Plane& _other)
    {
        normal = _other.normal;
        d = _other.d;

        return *this;
    }

    FORCE_INLINE bool Plane::operator == (const Plane& _other) const
    {
        return Math::equals(d, _other.d) && normal == _other.normal;
    }

    FORCE_INLINE bool Plane::operator != (const Plane& _other) const
    {
        return !(*this == _other);
    }
}
