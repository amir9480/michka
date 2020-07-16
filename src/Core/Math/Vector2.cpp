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

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Michka
{
    const Vector2 Vector2::up       = Vector2( 0.0f, +1.0f);
    const Vector2 Vector2::down     = Vector2( 0.0f, -1.0f);
    const Vector2 Vector2::left     = Vector2(-1.0f,  0.0f);
    const Vector2 Vector2::right    = Vector2(+1.0f,  0.0f);
    const Vector2 Vector2::zero     = Vector2( 0.0f,  0.0f);
    const Vector2 Vector2::one      = Vector2(+1.0f, +1.0f);
    const Vector2 Vector2::infinity = Vector2(Math::infinity, Math::infinity);

    Vector2::operator Vector3 () const
    {
        return Vector3(x, y, 0.0f);
    }

    Vector2::operator Vector4 () const
    {
        return Vector4(x, y, 0.0f);
    }
}
