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
#include "Michka/Core/Container/Size.h"

TEST(SizeTest, Create)
{
    {
        Michka::Size s;
        ASSERT_EQ(s.width, 0);
        ASSERT_EQ(s.height, 0);
    }
    {
        Michka::Size s(1920, 1080);
        ASSERT_EQ(s.width, 1920);
        ASSERT_EQ(s.height, 1080);

        Michka::Size s2(s);
        ASSERT_EQ(s2.width, 1920);
        ASSERT_EQ(s2.height, 1080);
    }
}

TEST(SizeTest, Operators)
{
    Michka::Size s1(640, 480);
    Michka::Size s2(640, 480);

    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);

    s2 = Michka::Size(1920, 1080);
    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);
}

TEST(SizeTest, Set)
{
    Michka::Size s(640, 480);

    s.setWidth(1024);
    ASSERT_EQ(s.width, 1024);
    ASSERT_EQ(s.height, 480);

    s.setHeight(768);
    ASSERT_EQ(s.width, 1024);
    ASSERT_EQ(s.height, 768);

    s.set(1920, 1080);
    ASSERT_EQ(s.width, 1920);
    ASSERT_EQ(s.height, 1080);
}
