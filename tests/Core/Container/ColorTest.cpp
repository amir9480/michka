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

#include <gtest/gtest.h>
#include "Core/Container/Color.h"
#include "Core/Math/Vector4.h"
#include "Core/Math/Vector3.h"
#include "Core/Foundation/Types.h"

TEST(ColorTest, Operators)
{
    Michka::Color a(5, 10, 15, 255);
    const Michka::Color b(50, 100, 150, 255);

    ASSERT_EQ(a[0], 5);
    ASSERT_EQ(a[1], 10);
    ASSERT_EQ(a[2], 15);
    ASSERT_EQ(b[0], 50);
    ASSERT_EQ(b[1], 100);
    ASSERT_EQ(b[2], 150);

    a[0] *= 2;
    ASSERT_EQ(a[0], 10);
    a[0] /= 2;
    ASSERT_EQ(a[0], 5);

    ASSERT_EQ((Michka::Vector3)a, Michka::Vector3(5.0f, 10.0f, 15.0f));
    ASSERT_EQ((Michka::Vector4)a, Michka::Vector4(5.0f, 10.0f, 15.0f, 255.0f));
}

TEST(ColorTest, Set)
{
    {
        Michka::Color color;
        ASSERT_EQ(color, Michka::Color::black);
    }
    {
        Michka::Color color(Michka::Color::red);
        ASSERT_EQ(color, Michka::Color::red);
        color = Michka::Color::green;
        ASSERT_NE(color, Michka::Color::red);
        ASSERT_EQ(color, Michka::Color::green);

        color.set(255, 255, 0, 255);
        ASSERT_EQ(color, Michka::Color::yellow);

        color.set(0x00ffffff);
        ASSERT_EQ(color, Michka::Color::cyan);

        color = 0xff00ffff;
        ASSERT_EQ(color, Michka::Color::magenta);
    }
    {
        Michka::Color color = 0x0000ffff;
        ASSERT_EQ(color, Michka::Color::blue);
    }
}
