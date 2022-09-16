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

#include "Michka/Core/Math/Ray.h"
#include "Michka/Core/Math/Utility.h"

namespace Michka
{
    FORCE_INLINE Ray::Ray() :
        direction(Vector3::forward)
    {
        //
    }

    FORCE_INLINE Ray::Ray(const Vector3& _position, const Vector3& _direction) :
        position(_position)
    {
        direction = _direction.getNormalized();
    }

    FORCE_INLINE Ray Ray::getNormalized() const
    {
        Ray self = *this;
        self.normalize();

        return self;
    }

    FORCE_INLINE Vector3 Ray::getPoint(const f32& _distance) const
    {
        return position + _distance*direction;
    }

    FORCE_INLINE Ray& Ray::normalize()
    {
        direction.normalize();

        return *this;
    }

    FORCE_INLINE Ray& Ray::setPosition(const Vector3& _position)
    {
        position = _position;
        return *this;
    }

    FORCE_INLINE Ray& Ray::setDirection(const Vector3& _direction)
    {
        direction = _direction.getNormalized();
        return *this;
    }

    FORCE_INLINE Ray& Ray::operator = (const Ray& _other)
    {
        position = _other.position;
        direction = _other.direction;

        return *this;
    }

    FORCE_INLINE bool Ray::operator == (const Ray& _other) const
    {
        return position == _other.position && direction == _other.direction;
    }

    FORCE_INLINE bool Ray::operator != (const Ray& _other) const
    {
        return !(*this == _other);
    }
}
