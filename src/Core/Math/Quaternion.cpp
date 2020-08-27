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

#include "Quaternion.h"
#include "Matrix3.h"
#include "Vector3.h"
#include "Core/Container/String.h"

namespace Michka
{
    const Quaternion Quaternion::identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    const Quaternion Quaternion::zero     = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

    Quaternion::Quaternion(const f32& _x, const f32& _y, const f32& _z)
    {
        set(_x, _y, _z);
    }

    Quaternion::Quaternion(const Matrix3& _matrix)
    {
        set(_matrix);
    }

    Quaternion::Quaternion(const Vector3& _euler):
        Quaternion(_euler.x, _euler.y, _euler.z)
    {
        //
    }

    Quaternion::Quaternion(const Vector3& _axis, const f32& _angle)
    {
        set(_axis, _angle);
    }

    Quaternion::Quaternion(const Vector3& _from, const Vector3& _to)
    {
        set(_from, _to);
    }

    Quaternion::Quaternion(const Vector3& _right, const Vector3& _up, const Vector3& _forward)
    {
        set(_right, _up, _forward);
    }

    Quaternion Quaternion::getExponent() const
    {
        f32 m;
        f32 l = Math::sqrt(x*x + y*y + z*z);
        if(Math::equals(l, 0.0f, QUATERNION_EPSILON))
        {
            m = 1.0f;
        }
        else
        {
            m = Math::sin(l) / l;
        }
        return Quaternion(
            x * m,
            y * m,
            z * m,
            Math::cos(l)
        );
    }

    Vector3 Quaternion::getForward() const
    {
        return Vector3(
            2.0f * (x*z - w*y),
            2.0f * (y*z + w*x),
            1.0f - 2.0f * (x*x + y*y)
        );
    }

    Quaternion Quaternion::getLog() const
    {
        float l = Math::atan2(x*x + y*y + z*z, w);
        return Quaternion(
            x * l,
            y * l,
            z * l,
            0.0f
        );
    }

    Vector3 Quaternion::getRight() const
    {
        return Vector3(
            1.0f - 2.0f * (y*y + z*z),
            2.0f * (x*y - w*z),
            2.0f * (x*z + w*y)
        );
    }

    Vector3 Quaternion::getUp() const
    {
        return Vector3(
            2.0f * (x*y + w*z),
            1.0f - 2.0f*(x*x + z*z),
            2.0f * (y*z - w*x)
        );
    }

    bool Quaternion::inverse()
    {
        f32 length = getLength();

        if(length > 0.0)
        {
            length = 1.0f/length;
            x *= -length;
            y *= -length;
            z *= -length;
            w *= +length;

            return true;
        }

        return false;
    }

    Quaternion& Quaternion::set(const f32& _x, const f32& _y, const f32& _z)
    {
        f32 sinX = Math::sin(_x * 0.5f);
        f32 sinY = Math::sin(_y * 0.5f);
        f32 sinZ = Math::sin(_z * 0.5f);
        f32 cosX = Math::cos(_x * 0.5f);
        f32 cosY = Math::cos(_y * 0.5f);
        f32 cosZ = Math::cos(_z * 0.5f);

        x = -(cosX * sinY * sinZ) + (sinX * cosY * cosZ);
        y =  (cosX * sinY * cosZ) + (sinX * cosY * sinZ);
        z = -(sinX * sinY * cosZ) + (cosX * cosY * sinZ);
        w =  (cosX * cosY * cosZ) + (sinX * sinY * sinZ);

        x = (Math::abs(x) < QUATERNION_EPSILON ? 1 : Math::sign(x)) * Math::clamp(Math::abs(x), 0.0f, 1.0f, QUATERNION_EPSILON);
        y = (Math::abs(y) < QUATERNION_EPSILON ? 1 : Math::sign(y)) * Math::clamp(Math::abs(y), 0.0f, 1.0f, QUATERNION_EPSILON);
        z = (Math::abs(z) < QUATERNION_EPSILON ? 1 : Math::sign(z)) * Math::clamp(Math::abs(z), 0.0f, 1.0f, QUATERNION_EPSILON);
        w = (Math::abs(w) < QUATERNION_EPSILON ? 1 : Math::sign(w)) * Math::clamp(Math::abs(w), 0.0f, 1.0f, QUATERNION_EPSILON);

        return *this;
    }

    Quaternion& Quaternion::set(const Vector3& _euler)
    {
        set(_euler.x, _euler.y, _euler.z);

        return *this;
    }

    Quaternion& Quaternion::set(const Vector3& _axis, const f32& _angle)
    {
        f32 sinAng = Math::sin(_angle * 0.5f);
        w = Math::cos(_angle * 0.5f);
        x = _axis.x * sinAng;
        y = _axis.y * sinAng;
        z = _axis.z * sinAng;

        return *this;
    }

    Quaternion& Quaternion::set(const Vector3& _from, const Vector3& _to)
    {
        Vector3 cross = _from.getCrossProduct(_to).getNormalized();
        f32 ang = _from.getAngleFrom(_to);
        *this = Quaternion(cross, ang);

        return *this;
    }

    Quaternion& Quaternion::set(const Matrix3& _matrix)
    {
        // Adapted from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
        f32 t = _matrix.m11 + _matrix.m22 + _matrix.m33;
        if(t > 0.0f)
        {
            f32 s = Math::sqrt(t + 1.0f) * 2.0f;
            w = 0.25f * s;
            s = 1.0f / s;
            x = (_matrix.m32 - _matrix.m23) * s;
            y = (_matrix.m13 - _matrix.m31) * s;
            z = (_matrix.m12 - _matrix.m21) * s;
        }
        else if((_matrix.m11 > _matrix.m22) && (_matrix.m11 > _matrix.m33))
        {
            f32 s = Math::sqrt(1.0f + _matrix.m11 - _matrix.m22 - _matrix.m33) * 2.0f;
            x = 0.25f * s;
            s = 1.0f / s;
            w = (_matrix.m32 - _matrix.m23) * s;
            y = (_matrix.m12 + _matrix.m21) * s;
            z = (_matrix.m13 + _matrix.m31) * s;
        }
        else if(_matrix.m22 > _matrix.m33)
        {
            f32 s = Math::sqrt(1.0f + _matrix.m22 - _matrix.m11 - _matrix.m33) * 2.0f;
            y = 0.25f * s;
            s = 1.0f / s;
            w = (_matrix.m13 - _matrix.m31) * s;
            x = (_matrix.m12 + _matrix.m21) * s;
            z = (_matrix.m23 + _matrix.m32) * s;
        }
        else
        {
            f32 s= Math::sqrt(1.0f + _matrix.m33 - _matrix.m11 - _matrix.m22) * 2.0f;
            z = 0.25f * s;
            s = 1.0f / s;
            w = (_matrix.m21 - _matrix.m12) * s;
            x = (_matrix.m13 + _matrix.m31) * s;
            y = (_matrix.m23 + _matrix.m32) * s;
        }

        return *this;
    }

    void Quaternion::set(const Vector3& _right, const Vector3& _up, const Vector3& _forward)
    {
        set(Matrix3(
            _right.x  , _right.y  , _right.z  ,
            _up.x     , _up.y     , _up.z     ,
            _forward.x, _forward.y, _forward.z
        ));
    }

    Quaternion Quaternion::slerp(Quaternion _a, Quaternion _b, const f32& _position)
    {
        // Adapted from : https://en.wikipedia.org/wiki/Slerp#Source_code
        _a.normalize();
        _b.normalize();

        float dot = dotProduct(_a, _b);

        if (dot < 0.0f)
        {
            _b = -_b;
            dot = -dot;
        }

        if (1.0f - dot < QUATERNION_EPSILON)
        {
            return (_a + _position*(_b - _a)).getNormalized();
        }

        float theta0 = Math::acos(dot);
        float theta = theta0 * _position;
        float sinTheta = Math::sin(theta);
        float sinTheta0 = Math::sin(theta0);

        float s0 = Math::cos(theta) - dot * sinTheta / sinTheta0;
        float s1 = sinTheta / sinTheta0;

        return (s0*_a) + (s1*_b);
    }

    void Quaternion::toAxes(Vector3 &_right, Vector3 &_up, Vector3 &_forward) const
    {
        _right = getRight();
        _up = getUp();
        _forward = getForward();

    }

    void Quaternion::toAxisAngle(Vector3& _axis, f32& _angle) const
    {
        Quaternion t = *this;
        t.normalize();
        _angle = 2.0f * Math::acos(t.w);
        _axis.x = t.x;
        _axis.y = t.y;
        _axis.z = t.z;
        if (Math::sqrt(1.0f - t.w*t.w) > QUATERNION_EPSILON)
        {
            _axis /= Math::sqrt(1.0f - t.w*t.w);
        }
    }

    Vector3 Quaternion::toEulerAngels() const
    {
        f32 y2 = y * y;
        f32 t = 2.0f * (w*y - z*x);
        if (Math::abs(t) > 0.9999f)
        {
            t = Math::sign(t) * 1.0f;
        }
        return Vector3(
            Math::atan2(2.0f * (w*x + y*z), 1.0f - 2.0f * (x*x + y2)),
            Math::asin(t),
            Math::atan2(2.0f * (w*z + x*y), 1.0f - 2.0f * (y2 + z*z))
        );
    }

    Matrix3 Quaternion::toMatrix() const
    {
        f32 x2 = 2.0f * x * x;
        f32 y2 = 2.0f * y * y;
        f32 z2 = 2.0f * z * z;
        f32 xy = 2.0f * x * y;
        f32 xz = 2.0f * x * z;
        f32 xw = 2.0f * -w * x;
        f32 yw = 2.0f * -w * y;
        f32 yz = 2.0f * y * z;
        f32 zw = 2.0f * -w * z;

        return Matrix3(
            1.0f - y2 - z2, xy - zw, xz + yw,
            xy + zw, 1.0f - x2 - z2, yz - xw,
            xz - yw, yz + xw, 1.0f - x2 - y2
        );
    }

    String Quaternion::toString() const
    {
        return String("Quaternion(") + String::number(x) + ", " + String::number(y) + ", " + String::number(z) + ", " + String::number(w) + ")";
    }
}
