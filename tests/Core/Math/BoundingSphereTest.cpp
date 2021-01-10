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
#include "Core/Math/BoundingSphere.h"
#include "Core/Math/BoundingBox.h"
#include "Core/Math/Matrix3.h"
#include "Core/Math/Matrix.h"
#include "Core/Foundation/Types.h"

TEST(BoundingSphereTest, IsInside)
{
    Michka::BoundingSphere a(Michka::Vector3::zero, 1.0f);

    ASSERT_TRUE(a.isInside(Michka::Vector3(0.3f, 0.3f, 0.3f)));
    ASSERT_FALSE(a.isInside(Michka::Vector3(-2.0f, -1.0f, -1.0f)));

    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(Michka::Vector3::zero, 0.1f)));
    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(2.0f * Michka::Vector3::up, 2.0f)));
    ASSERT_FALSE(a.isInside(Michka::BoundingSphere(2.0f * Michka::Vector3::up, 0.5f)));

    ASSERT_TRUE(a.isInside(Michka::BoundingBox(Michka::Vector3::zero, Michka::Vector3::one)));
    ASSERT_TRUE(a.isInside(Michka::BoundingBox(-Michka::Vector3::one, Michka::Vector3(-0.4f, -0.4f, -0.4f))));
    ASSERT_FALSE(a.isInside(Michka::BoundingBox(-4.0f * Michka::Vector3::one, -3.0f * Michka::Vector3::one)));
}

TEST(BoundingSphereTest, Merge)
{
    Michka::BoundingSphere a(Michka::Vector3::zero, 1.0f);

    ASSERT_EQ(a.getMerged(2.0f * Michka::Vector3::up), Michka::BoundingSphere(0.5f * Michka::Vector3::up, 1.5f));

    ASSERT_EQ(a.getMerged(Michka::BoundingSphere(2.0f * Michka::Vector3::up, 1.0f)), Michka::BoundingSphere(1.0f * Michka::Vector3::up, 2.0f));
    ASSERT_EQ(a.getMerged(Michka::BoundingSphere(4.0f * Michka::Vector3::up, 10.0f)), Michka::BoundingSphere(4.0f * Michka::Vector3::up, 10.0f));
    ASSERT_EQ(a.getMerged(Michka::BoundingSphere(0.2f * Michka::Vector3::up, 0.5f)), a);

    ASSERT_EQ(a.getMerged(Michka::BoundingBox(Michka::Vector3::zero, 0.6f * Michka::Vector3::one)), a.getMerged(0.6f * Michka::Vector3::one));

    a = Michka::BoundingSphere();
    ASSERT_EQ(a.getMerged(2.0f * Michka::Vector3::up), Michka::BoundingSphere(2.0f * Michka::Vector3::up, 0.0f));
    ASSERT_EQ(a.getMerged(Michka::BoundingSphere(2.0f * Michka::Vector3::up, 1.0f)), Michka::BoundingSphere(2.0f * Michka::Vector3::up, 1.0f));

    a.set(Michka::Vector3::zero, 1.0f);
    ASSERT_EQ(a, Michka::BoundingSphere(Michka::Vector3::zero, 1.0f));
}

TEST(BoundingSphereTest, Transform)
{
    Michka::BoundingSphere a(Michka::Vector3::zero, 1.0f);

    ASSERT_EQ(
        a.getTransformed(Michka::Matrix3::createScaleMatrix(2.0f * Michka::Vector3::one)),
        Michka::BoundingSphere(Michka::Vector3::zero, 2.0f)
    );
    ASSERT_EQ(
        a.getTransformed(Michka::Matrix::createTranslationMatrix(Michka::Vector3(1.0f, 2.0f, 3.0f))),
        Michka::BoundingSphere(Michka::Vector3(1.0f, 2.0f, 3.0f), 1.0f)
    );
    ASSERT_NE(
        a.getTransformed(Michka::Matrix::createScaleMatrix(2.0f * Michka::Vector3::one) * Michka::Matrix::createTranslationMatrix(Michka::Vector3(1.0f, 2.0f, 3.0f))),
        Michka::BoundingSphere(Michka::Vector3(1.0f, 2.0f, 3.0f), 1.0f)
    );
    ASSERT_EQ(
        a.getTransformed(Michka::Matrix::createScaleMatrix(2.0f * Michka::Vector3::one) * Michka::Matrix::createTranslationMatrix(Michka::Vector3(1.0f, 2.0f, 3.0f))),
        Michka::BoundingSphere(Michka::Vector3(1.0f, 2.0f, 3.0f), 2.0f)
    );
}
