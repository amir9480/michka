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
#include "Core/Math/Plane.h"
#include "Core/Math/Ray.h"
#include "Core/Math/Utility.h"
#include "Core/Foundation/Types.h"

TEST(RayTest, GetPoint)
{
    Michka::Ray r;

    ASSERT_EQ(r.getPoint(1.0f), Michka::Vector3::forward * 1.0f);
    ASSERT_EQ(r.getPoint(2.0f), Michka::Vector3::forward * 2.0f);

    r = Michka::Ray(Michka::Vector3::forward, Michka::Vector3::forward);
    ASSERT_EQ(r.getPoint(1.0f), Michka::Vector3::forward * 2.0f);
    ASSERT_EQ(r.getPoint(2.0f), Michka::Vector3::forward * 3.0f);
}

TEST(RayTest, IsIntersects)
{
    Michka::Ray r(Michka::Vector3::zero, Michka::Vector3::forward);

    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingSphere(Michka::Vector3::forward * 3.0f, 1.0f)), 2.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingSphere(Michka::Vector3::zero, 2.0f)), 2.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingSphere(Michka::Vector3::forward, 2.0f)), 3.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingSphere(Michka::Vector3::back * 2.1f, 2.0f)), Michka::Math::infinity);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingSphere(Michka::Vector3::right * 4.0f, 2.0f)), Michka::Math::infinity);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingSphere(Michka::Vector3::down * 5.0f, 4.0f)), Michka::Math::infinity);

    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingBox(Michka::Vector3(0.0f, -1.0f, 1.0f), Michka::Vector3(0.0f, 1.0f, 2.0f))), 1.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingBox(Michka::Vector3(0.0f, -1.0f, 2.0f), Michka::Vector3(0.0f, 1.0f, 3.0f))), 2.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingBox(Michka::Vector3(0.0f, -1.0f, -2.0f), Michka::Vector3(0.0f, 1.0f, -1.0f))), Michka::Math::infinity);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::BoundingBox(Michka::Vector3(0.0f, +1.0f, 2.0f), Michka::Vector3(0.0f, 2.0f, 3.0f))), Michka::Math::infinity);

    ASSERT_FLOAT_EQ(r.isIntersects(Michka::Plane(Michka::Vector3::forward, Michka::Vector3::back)), 1.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::Plane(Michka::Vector3::forward, Michka::Vector3::forward)), 1.0f);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::Plane(Michka::Vector3::right, Michka::Vector3::left)), Michka::Math::infinity);
    ASSERT_FLOAT_EQ(r.isIntersects(Michka::Plane(Michka::Vector3::forward, Michka::Vector3::up)), Michka::Math::infinity);
}

TEST(RayTest, Normalize)
{
    Michka::Ray r;
    r.direction = Michka::Vector3::one;
    ASSERT_NE(r.getNormalized(), r);
    ASSERT_EQ(r.getNormalized(), Michka::Ray(Michka::Vector3::zero, Michka::Vector3::one.getNormalized()));
}

TEST(RayTest, Set)
{
    Michka::Ray r;

    ASSERT_EQ(r, Michka::Ray(Michka::Vector3::zero, Michka::Vector3::forward));

    r.setPosition(Michka::Vector3(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(r, Michka::Ray(Michka::Vector3(1.0f, 2.0f, 3.0f), Michka::Vector3::forward));

    r.setDirection(Michka::Vector3::one);
    ASSERT_EQ(r, Michka::Ray(Michka::Vector3(1.0f, 2.0f, 3.0f), Michka::Vector3::one.getNormalized()));
}
