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

#include <gtest/gtest.h>
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"
#include "Core/Types.h"

TEST(Vector3Test, Angle)
{
    Michka::Vector3 a(0.0f, 1.0f, 0.0f);

    ASSERT_FLOAT_EQ(a.getAngleFrom(Michka::Vector3::right), 90.0f);
}

TEST(Vector3Test, Cast)
{
    Michka::Vector3 a(1.0f, 2.0f, 3.0f);
    Michka::Vector4 b = a;

    ASSERT_EQ(b, Michka::Vector4(1.0f, 2.0f, 3.0f, 1.0f));
}

TEST(Vector3Test, Compare)
{
    const Michka::Vector3 a(0.0f, 1.0f, 0.0f);
    Michka::Vector3 b (0.0f, 0.0f, 1.0f);

    ASSERT_NE(a, b);

    b.setY(1.0f);
    ASSERT_NE(a, b);

    b.setZ(0.0f);
    ASSERT_EQ(a, b);
    ASSERT_EQ(a, Michka::Vector3::up);

    Michka::Vector3 c = a;
    ASSERT_EQ(b, c);
}

TEST(Vector3Test, CrossProduct)
{
    ASSERT_EQ(Michka::Vector3::crossProduct(Michka::Vector3::right, Michka::Vector3::up), Michka::Vector3::forward);
    ASSERT_EQ(Michka::Vector3::crossProduct(Michka::Vector3::right, Michka::Vector3::forward), Michka::Vector3::down);
    ASSERT_EQ(Michka::Vector3::crossProduct(Michka::Vector3::back, Michka::Vector3::up), Michka::Vector3::right);
    ASSERT_EQ(Michka::Vector3::crossProduct(Michka::Vector3::left, Michka::Vector3::back), Michka::Vector3::down);
    ASSERT_EQ(Michka::Vector3::crossProduct(Michka::Vector3::right, Michka::Vector3::back), Michka::Vector3::up);

    Michka::Vector3 a(1.0f, 2.0f, 3.0f);
    Michka::Vector3 b(1.0f, 5.0f, 7.0f);
    ASSERT_EQ(a.getCrossProduct(b), Michka::Vector3(-1.0f, -4.0f, 3.0f));
}

TEST(Vector3Test, Distance)
{
    Michka::Vector3 a(7.0f, 4.0f, 3.0f);
    const Michka::Vector3 b(17.0f, 6.0f, 2.0f);

    ASSERT_FLOAT_EQ(b.getDistanceFrom(a), 10.246951f);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3(8.0f, 5.0f, -8.0f)), 11.090537f);
    ASSERT_FLOAT_EQ(b.getDistanceFrom(b), 0.0f);
}

TEST(Vector3Test, DotProduct)
{
    Michka::Vector3 a(1.0f, 2.0f, 3.0f);
    const Michka::Vector3 b(1.0f, 5.0f, 7.0f);

    ASSERT_FLOAT_EQ(b.getDotProduct(a), 32.0f);
}

TEST(Vector3Test, Lerp)
{
    Michka::Vector3 a(0.0f, 0.0f, 0.0f);
    const Michka::Vector3 b(10.0f, 0.0f, 0.0f);

    ASSERT_EQ(Michka::Vector3::lerp(a, b, 0.0f), a);
    ASSERT_EQ(Michka::Vector3::lerp(a, b, 1.0f), b);
    ASSERT_EQ(Michka::Vector3::lerp(a, b, 0.5f), Michka::Vector3(5.0f, 0.0f, 0.0f));
}

TEST(Vector3Test, Normalize)
{
    Michka::Vector3 a;
    ASSERT_EQ(a, Michka::Vector3::zero);
    a.set(5.0f, 10.0f, 5.0f);

    ASSERT_EQ(a.getNormalized(), Michka::Vector3(0.40825f, 0.8165f, 0.40825f));
    a.normalize();
    ASSERT_TRUE(a.isNormalized());
    ASSERT_FLOAT_EQ(a.getLength(), 1.0f);

    a.setX(0.0f).setY(0.0f).setZ(0.0f);
    ASSERT_FALSE(a.isNormalizable());
    ASSERT_EQ(a.getNormalized(), Michka::Vector3::zero);
}

TEST(Vector3Test, Operators)
{
    Michka::Vector3 a(5.0f, -10.0f, 15.0f);
    const Michka::Vector3 b(-5.0f, 10.0f, -15.0f);

    ASSERT_EQ(+a, a);
    ASSERT_EQ(-a, b);
    ASSERT_FLOAT_EQ(a[0], 5.0f);
    ASSERT_FLOAT_EQ(a[1], -10.0f);
    ASSERT_FLOAT_EQ(a[2], 15.0f);
    ASSERT_FLOAT_EQ(b[0], -5.0f);
    ASSERT_FLOAT_EQ(b[1], 10.0f);
    ASSERT_FLOAT_EQ(b[2], -15.0f);

    a[0] = -a[0];
    ASSERT_FLOAT_EQ(a[0], -5.0f);
    a[0] = -a[0];

    ASSERT_EQ(a * b, Michka::Vector3(-25.0f, -100.0f, -225.0f));
    ASSERT_EQ(a / Michka::Vector3(1.0, 2.0f, 3.0f), Michka::Vector3(5.0f, -5.0f, 5.0f));
    ASSERT_EQ(a * 2.0f, Michka::Vector3(10, -20.0f, 30.0f));
    ASSERT_EQ(2.0f * a, Michka::Vector3(10, -20.0f, 30.0f));
    ASSERT_EQ(a / 2.0f, Michka::Vector3(2.5f, -5.0f, 7.5f));
    ASSERT_EQ(1.0f / a, Michka::Vector3(1.0f/5.0f, -1.0f/10.0f, 1.0f/15.0f));

    ASSERT_EQ(a + 2.0f, Michka::Vector3(7.0f, -8.0f, 17.0f));
    ASSERT_EQ(a - 2.0f, Michka::Vector3(3.0f, -12.0f, 13.0f));
    ASSERT_EQ(2.0f + a, Michka::Vector3(7.0f, -8.0f, 17.0f));
    ASSERT_EQ(2.0f - a, Michka::Vector3(-3.0f, 12.0f, -13.0f));

    ASSERT_EQ(a + Michka::Vector3(2.0f, 3.0f, 4.0f), Michka::Vector3(7.0f, -7.0f, 19.0f));
    ASSERT_EQ(a - Michka::Vector3(2.0f, 3.0f, 4.0f), Michka::Vector3(3.0f, -13.0f, 11.0f));
}

TEST(Vector3Test, Reflect)
{
    Michka::Vector3 a(1.0f, 1.0f, 0.0f);
    a.reflect(Michka::Vector3::up);

    ASSERT_EQ(a, Michka::Vector3(1.0f, -1.0f, 0.0f));
}
