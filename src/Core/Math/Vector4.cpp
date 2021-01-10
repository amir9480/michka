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

#include "Vector4.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "Core/Container/String.h"

namespace Michka
{
    const Vector4 Vector4::up       = Vector4( 0.0f, +1.0f,  0.0f);
    const Vector4 Vector4::down     = Vector4( 0.0f, -1.0f,  0.0f);
    const Vector4 Vector4::left     = Vector4(-1.0f,  0.0f,  0.0f);
    const Vector4 Vector4::right    = Vector4(+1.0f,  0.0f,  0.0f);
    const Vector4 Vector4::forward  = Vector4( 0.0f,  0.0f, +1.0f);
    const Vector4 Vector4::back     = Vector4( 0.0f,  0.0f, -1.0f);
    const Vector4 Vector4::zero     = Vector4( 0.0f,  0.0f,  0.0f);
    const Vector4 Vector4::one      = Vector4(+1.0f, +1.0f, +1.0f);
    const Vector4 Vector4::infinity = Vector4(Math::infinity, Math::infinity, Math::infinity);
    const Vector4 Vector4::nan      = Vector4(Math::nan, Math::nan, Math::nan, Math::nan);

    String Vector4::toString() const
    {
        return String("Vector4(") + String::number(x) + ", " + String::number(y) + ", " + String::number(z) + ", " + String::number(w) + ")";
    }

    Vector4 Vector4::operator * (const Matrix& _other) const
    {
        return Vector4(
            x*_other.m11 + y*_other.m21 + z*_other.m31 + w*_other.m41,
            x*_other.m12 + y*_other.m22 + z*_other.m32 + w*_other.m42,
            x*_other.m13 + y*_other.m23 + z*_other.m33 + w*_other.m43,
            x*_other.m14 + y*_other.m24 + z*_other.m34 + w*_other.m44
        );
    }

    Vector4::operator Vector3 () const
    {
        f32 wInv = 1.0f / w;
        return Vector3(x * wInv, y * wInv, z * wInv);
    }
}
