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

#include "Michka/Core/Container/Color.h"
#include "Michka/Core/Math/Vector3.h"
#include "Michka/Core/Math/Vector4.h"
#include "Michka/Core/Container/String.h"

namespace Michka
{
    const Color Color::transparent  = Color(  0,   0,   0,   0);
    const Color Color::black        = Color(  0,   0,   0, 255);
    const Color Color::white        = Color(255, 255, 255, 255);
    const Color Color::red          = Color(255,   0,   0, 255);
    const Color Color::green        = Color(  0, 255,   0, 255);
    const Color Color::blue         = Color(  0,   0, 255, 255);
    const Color Color::yellow       = Color(255, 255,   0, 255);
    const Color Color::cyan         = Color(  0, 255, 255, 255);
    const Color Color::magenta      = Color(255,   0, 255, 255);

    String Color::toString() const
    {
        return String("Color(") + String::number(r) + ", " + String::number(g) + ", " + String::number(b) + ", " + String::number(a) + ")";
    }

    Color::operator Vector3 () const
    {
        return Vector3(r, g, b);
    }

    Color::operator Vector4 () const
    {
        return Vector4(r, g, b, a);
    }
}
