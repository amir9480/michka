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
#include "Michka/Core/Container/Rect.h"

TEST(RectTest, Create)
{
    {
        Michka::Rect r;

        ASSERT_EQ(r.x, 0);
        ASSERT_EQ(r.y, 0);
        ASSERT_EQ(r.width, 0);
        ASSERT_EQ(r.height, 0);
    }
    {
        Michka::Rect r(Michka::Position(2, 3), Michka::Size(4, 5));

        ASSERT_EQ(r.x, 2);
        ASSERT_EQ(r.y, 3);
        ASSERT_EQ(r.width, 4);
        ASSERT_EQ(r.height, 5);
    }
    {
        Michka::Rect r(10, 20, 15, 25);

        ASSERT_EQ(r.x, 10);
        ASSERT_EQ(r.y, 20);
        ASSERT_EQ(r.width, 15);
        ASSERT_EQ(r.height, 25);

        Michka::Rect r2(r);
        ASSERT_EQ(r2.x, 10);
        ASSERT_EQ(r2.y, 20);
        ASSERT_EQ(r2.width, 15);
        ASSERT_EQ(r2.height, 25);

        r2 = Michka::Rect();
        ASSERT_EQ(r2.x, 0);
        ASSERT_EQ(r2.y, 0);
        ASSERT_EQ(r2.width, 0);
        ASSERT_EQ(r2.height, 0);
    }
}

TEST(RectTest, Operators)
{
    Michka::Rect r1(10, 20, 30, 40);
    Michka::Rect r2(10, 20, 30, 40);

    ASSERT_TRUE(r1 == r2);
    ASSERT_FALSE(r1 != r2);

    r2.x = 0;
    ASSERT_FALSE(r1 == r2);
    ASSERT_TRUE(r1 != r2);
}

TEST(RectTest, Set)
{
    Michka::Rect r(10, 20, 15, 25);

    ASSERT_EQ(r.x, 10);
    ASSERT_EQ(r.y, 20);
    ASSERT_EQ(r.width, 15);
    ASSERT_EQ(r.height, 25);

    r.setX(100);
    ASSERT_EQ(r.x, 100);
    ASSERT_EQ(r.y, 20);
    ASSERT_EQ(r.width, 15);
    ASSERT_EQ(r.height, 25);

    r.setY(200);
    ASSERT_EQ(r.x, 100);
    ASSERT_EQ(r.y, 200);
    ASSERT_EQ(r.width, 15);
    ASSERT_EQ(r.height, 25);

    r.setWidth(150);
    ASSERT_EQ(r.x, 100);
    ASSERT_EQ(r.y, 200);
    ASSERT_EQ(r.width, 150);
    ASSERT_EQ(r.height, 25);

    r.setHeight(250);
    ASSERT_EQ(r.x, 100);
    ASSERT_EQ(r.y, 200);
    ASSERT_EQ(r.width, 150);
    ASSERT_EQ(r.height, 250);

    r.set(10, 20, 15, 25);
    ASSERT_EQ(r.x, 10);
    ASSERT_EQ(r.y, 20);
    ASSERT_EQ(r.width, 15);
    ASSERT_EQ(r.height, 25);

    r.setPosition(Michka::Position(100, 200));
    ASSERT_EQ(r.x, 100);
    ASSERT_EQ(r.y, 200);
    ASSERT_EQ(r.width, 15);
    ASSERT_EQ(r.height, 25);

    r.setSize(Michka::Size(150, 250));
    ASSERT_EQ(r.x, 100);
    ASSERT_EQ(r.y, 200);
    ASSERT_EQ(r.width, 150);
    ASSERT_EQ(r.height, 250);
}
