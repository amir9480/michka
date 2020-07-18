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

#include "Plane.h"
#include "Core/Container/String.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/BoundingBox.h"
#include "Core/Math/BoundingSphere.h"

namespace Michka
{
    Matrix Plane::getReflectionMatrix() const
    {
        Plane p = getNormalized();

        return Matrix(
            -2.0f * p.a * p.a +1.0f, -2.0f * p.a * p.b,       -2.0f * p.a * p.c,      0.0f,
            -2.0f * p.a * p.b,       -2.0f * p.b * p.b +1.0f, -2.0f * p.b * p.c,      0.0f,
            -2.0f * p.a * p.c,       -2.0f * p.b * p.c,       -2.0f * p.c * p.c+1.0f, 0.0f,
             2.0f * p.a * p.d,        2.0f * p.b * p.d,        2.0f * p.c * p.d,      1.0f
        );
    }

    bool Plane::isIntersects(const BoundingBox& _box) const
    {
        return _box.isIntersects(*this);
    }

    bool Plane::isIntersects(const BoundingSphere& _sphere) const
    {
        return _sphere.isIntersects(*this);
    }

    String Plane::toString() const
    {
        return "Plane(" + String::number(a) + ", " + String::number(b) + ", " + String::number(c) + ", " + String::number(d) + ")";
    }
}
