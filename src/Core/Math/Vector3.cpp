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

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Matrix3.h"

namespace Michka
{
    const Vector3 Vector3::up       = Vector3( 0.0f, +1.0f,  0.0f);
    const Vector3 Vector3::down     = Vector3( 0.0f, -1.0f,  0.0f);
    const Vector3 Vector3::left     = Vector3(-1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::right    = Vector3(+1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::forward  = Vector3( 0.0f,  0.0f, +1.0f);
    const Vector3 Vector3::back     = Vector3( 0.0f,  0.0f, -1.0f);
    const Vector3 Vector3::zero     = Vector3( 0.0f,  0.0f,  0.0f);
    const Vector3 Vector3::one      = Vector3(+1.0f, +1.0f, +1.0f);
    const Vector3 Vector3::infinity = Vector3(Math::infinity, Math::infinity, Math::infinity);

    Vector3& Vector3::operator *= (const Matrix& _other)
    {
        *this = *this * _other;

        return *this;
    }

    Vector3 Vector3::operator * (const Matrix& _other) const
    {
        return Vector3(
            x*_other.m11 + y*_other.m21 + z*_other.m31 + _other.m41,
            x*_other.m12 + y*_other.m22 + z*_other.m32 + _other.m42,
            x*_other.m13 + y*_other.m23 + z*_other.m33 + _other.m43
        );
    }

    Vector3& Vector3::operator *= (const Matrix3& _other)
    {
        *this = *this * _other;

        return *this;
    }

    Vector3 Vector3::operator * (const Matrix3& _other) const
    {
        return Vector3(
            x*_other.m11 + y*_other.m21 + z*_other.m31,
            x*_other.m12 + y*_other.m22 + z*_other.m32,
            x*_other.m13 + y*_other.m23 + z*_other.m33
        );
    }

    Vector3::operator Vector4 () const
    {
        return Vector4(x, y, z);
    }
}
