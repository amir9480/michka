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
#include "Core/Math/BoundingBox.h"
#include "Core/Math/BoundingSphere.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Plane.h"
#include "Core/Foundation/Types.h"

TEST(PlaneTest, GetDistance)
{
    Michka::Plane a(Michka::Vector3::down * 3.0f, Michka::Vector3::up);

    ASSERT_NE(a, Michka::Plane());

    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3::down * 3.0f), 0.0f);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3::down * 1.0f), 2.0f);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3::up * 1.0f), 4.0f);

    a.set(Michka::Vector3::zero, Michka::Vector3::left);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3::down * 3.0f), 0.0f);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3::right), -1.0f);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector3::left), 1.0f);
}

TEST(PlaneTest, GetProjected)
{
    Michka::Plane a(Michka::Vector3::down * 3.0f, Michka::Vector3::up);

    ASSERT_EQ(a.getProjected(Michka::Vector3::zero), Michka::Vector3(Michka::Vector3::down * 3.0f));
    Michka::Vector3 test = a.getProjected(Michka::Vector3(5.0f, 5.0f, 5.0f));
    ASSERT_EQ(a.getProjected(Michka::Vector3(5.0f, 5.0f, 5.0f)), Michka::Vector3(5.0f, -3.0f, 5.0f));
}

TEST(PlaneTest, GetReflected)
{
    Michka::Plane a(Michka::Vector3::down * 3.0f, Michka::Vector3::up);

    ASSERT_EQ(a.getReflected(Michka::Vector3::zero), Michka::Vector3(Michka::Vector3::down * 6.0f));
    ASSERT_EQ(a.getReflected(Michka::Vector3(5.0f, 5.0f, 5.0f)), Michka::Vector3(5.0f, -11.0f, 5.0f));
}

TEST(PlaneTest, GetReflectionMatrix)
{
    Michka::Plane a(Michka::Vector3::down * 3.0f, Michka::Vector3::up);

    Michka::Vector3 test = Michka::Vector3::zero * a.getReflectionMatrix();
    ASSERT_EQ(Michka::Vector3::zero * a.getReflectionMatrix(), Michka::Vector3(Michka::Vector3::down * 6.0f));
    ASSERT_EQ(Michka::Vector3(5.0f, 5.0f, 5.0f) * a.getReflectionMatrix(), Michka::Vector3(5.0f, -11.0f, 5.0f));
}

TEST(PlaneTest, GetSide)
{
    Michka::Plane a(Michka::Vector3::up * 3.0f, Michka::Vector3::up);

    ASSERT_EQ(a.getSide(Michka::Vector3::one * 1.0f), Michka::Side::back);
    ASSERT_EQ(a.getSide(Michka::Vector3::one * 3.0f), Michka::Side::on);
    ASSERT_EQ(a.getSide(Michka::Vector3::one * 4.0f), Michka::Side::front);
}

TEST(PlaneTest, IsIntersects)
{
    Michka::Plane a(Michka::Vector3::up * 3.0f, Michka::Vector3::up);

    ASSERT_FALSE(a.isIntersects(Michka::BoundingBox(Michka::Vector3::zero, Michka::Vector3::one)));
    ASSERT_FALSE(a.isIntersects(Michka::BoundingBox(3.5f * Michka::Vector3::up, 5.0f * Michka::Vector3::one)));
    ASSERT_TRUE(a.isIntersects(Michka::BoundingBox(2.0f * Michka::Vector3::up, 4.0f * Michka::Vector3::one)));
    ASSERT_TRUE(a.isIntersects(Michka::BoundingBox(3.0f * Michka::Vector3::up, 4.0f * Michka::Vector3::one)));

    ASSERT_FALSE(a.isIntersects(Michka::BoundingSphere(Michka::Vector3::zero, 2.0f)));
    ASSERT_FALSE(a.isIntersects(Michka::BoundingSphere(6.0f * Michka::Vector3::up, 2.0f)));
    ASSERT_TRUE(a.isIntersects(Michka::BoundingSphere(2.0f * Michka::Vector3::up, 2.0f)));
    ASSERT_TRUE(a.isIntersects(Michka::BoundingSphere(3.0f * Michka::Vector3::up, 2.0f)));
    ASSERT_TRUE(a.isIntersects(Michka::BoundingSphere(4.0f * Michka::Vector3::up, 2.0f)));
}

TEST(PlaneTest, IsSide)
{
    Michka::Plane a(Michka::Vector3::up * 3.0f, Michka::Vector3::up);

    ASSERT_TRUE(a.isSameSide(Michka::Vector3::one * 1.0f, Michka::Vector3::one * 2.0f));
    ASSERT_TRUE(a.isSameSide(Michka::Vector3::one * 4.0f, Michka::Vector3::one * 5.0f));
    ASSERT_FALSE(a.isSameSide(Michka::Vector3::one * 1.0f, Michka::Vector3::one * 5.0f));
}

TEST(PlaneTest, Normalize)
{
    Michka::Plane a(0.0f, 2.0f, 0.0f, 2.0f);

    ASSERT_EQ(a.getNormalized(), Michka::Plane(Michka::Vector3::up, Michka::Vector3::up));
}

TEST(PlaneTest, Set)
{
    Michka::Plane a(Michka::Vector3::up * 3.0f, Michka::Vector3::up);

    ASSERT_EQ(a.getPosition(), Michka::Vector3::up * 3.0f);
    ASSERT_EQ(a.getNormal(), Michka::Vector3::up);

    a = Michka::Plane(Michka::Vector3::up, Michka::Vector3::zero, Michka::Vector3::right);

    ASSERT_EQ(a.getPosition(), Michka::Vector3::zero);
    ASSERT_EQ(a.getNormal(), Michka::Vector3::back);

    a = Michka::Plane(0.0f, 0.0f, 1.0f, 0.0f);
    ASSERT_EQ(a.getPosition(), Michka::Vector3::zero);
    ASSERT_EQ(a.getNormal(), Michka::Vector3::forward);
}
