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
#include "Michka/Core/Container/Position.h"

TEST(PositionTest, Create)
{
    {
        Michka::Position p;
        ASSERT_EQ(p.x, 0);
        ASSERT_EQ(p.y, 0);
    }
    {
        Michka::Position p(1920, 1080);
        ASSERT_EQ(p.x, 1920);
        ASSERT_EQ(p.y, 1080);

        Michka::Position p2(p);
        ASSERT_EQ(p2.x, 1920);
        ASSERT_EQ(p2.y, 1080);
    }
}

TEST(PositionTest, Operators)
{
    Michka::Position p1(640, 480);
    Michka::Position p2(640, 480);

    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 != p2);

    p2 = Michka::Position(1920, 1080);
    ASSERT_FALSE(p1 == p2);
    ASSERT_TRUE(p1 != p2);
}

TEST(PositionTest, Set)
{
    Michka::Position p(640, 480);

    p.setX(1024);
    ASSERT_EQ(p.x, 1024);
    ASSERT_EQ(p.y, 480);

    p.setY(768);
    ASSERT_EQ(p.x, 1024);
    ASSERT_EQ(p.y, 768);

    p.set(1920, 1080);
    ASSERT_EQ(p.x, 1920);
    ASSERT_EQ(p.y, 1080);
}
