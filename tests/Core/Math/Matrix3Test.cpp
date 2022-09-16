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
#include "Michka/Core/Math/Matrix3.h"
#include "Michka/Core/Math/Matrix.h"
#include "Michka/Core/Math/Vector3.h"
#include "Michka/Core/Foundation/Types.h"

TEST(Matrix3Test, Cast)
{
    Michka::Matrix3 a = Michka::Matrix3::createRotationMatrix(45.0f, 90.0f, 60.0f);
    Michka::Matrix b = a;

    ASSERT_EQ(b, Michka::Matrix::createRotationMatrix(45.0f, 90.0f, 60.0f));
}

TEST(Matrix3Test, CreateRotationMatrix)
{
    Michka::Vector3 pos;
    pos = Michka::Vector3(0.0f, 1.0f, 0.0f) * Michka::Matrix3::createRotationMatrixX(90.0f);

    ASSERT_EQ(pos, Michka::Vector3(0.0f, 0.0f, 1.0f));

    pos = Michka::Vector3(0.0f, 0.0f, 1.0f) * Michka::Matrix3::createRotationMatrixY(90.0f);

    ASSERT_EQ(pos, Michka::Vector3(1.0f, 0.0f, 0.0f));

    pos = Michka::Vector3(0.0f, 1.0f, 0.0f) * Michka::Matrix3::createRotationMatrixZ(90.0f);

    ASSERT_EQ(pos, Michka::Vector3(-1.0f, 0.0f, 0.0f));

    pos = Michka::Vector3(0.0f, 1.0f, 0.0f) * Michka::Matrix3::createRotationMatrixZ(-90.0f);

    ASSERT_EQ(pos, Michka::Vector3(1.0f, 0.0f, 0.0f));

    pos = Michka::Vector3(0.0f, 1.0f, 0.0f) * Michka::Matrix3::createRotationMatrix(90.0f, 90.0f, 0.0f);

    ASSERT_EQ(pos, Michka::Vector3(1.0f, 0.0f, 0.0f));

    pos = Michka::Vector3(0.0f, 1.0f, 0.0f) * Michka::Matrix3::createRotationMatrixAxis(Michka::Vector3::forward, -90.0f);

    ASSERT_EQ(pos, Michka::Vector3(1.0f, 0.0f, 0.0f));
}

TEST(Matrix3Test, CreateScaleMatrix3)
{
    Michka::Matrix3 mat = Michka::Matrix3::createScaleMatrix(Michka::Vector3(1.0f, 2.0f, 3.0f));
    Michka::Vector3 pos(1.0f, 2.0f, 3.0f);
    pos *= mat;

    ASSERT_EQ(pos, Michka::Vector3(1.0f, 4.0f, 9.0f));
}

TEST(Matrix3Test, Determinant)
{
    const Michka::Matrix3 a(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );
    const Michka::Matrix3 b(
        5.0f, 1.0f, 6.0f,
        8.0f, 4.0f, 2.0f,
        7.0f, 6.0f, 5.0f
    );

    ASSERT_FLOAT_EQ(a.getDeterminant(), 0.0f);
    ASSERT_FLOAT_EQ(b.getDeterminant(), 134.0f);
}

TEST(Matrix3Test, Inverse)
{
    const Michka::Matrix3 a(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );
    const Michka::Matrix3 b(
        5.0f, 1.0f, 6.0f,
        8.0f, 4.0f, 2.0f,
        7.0f, 6.0f, 5.0f
    );
    const Michka::Matrix3 bInv(
        4.0f/67.0f,    31.0f/134.0f, -11.0f/67.0f,
        -13.0f/67.0f, -17.0f/134.0f,  19.0f/67.0f,
        10.0f/67.0f,  -23.0f/134.0f,  6.0f/67.0f
    );

    ASSERT_FALSE(a.isInversable());
    ASSERT_TRUE(b.isInversable());
    ASSERT_EQ(a.getInversed(), a);
    ASSERT_EQ(b.getInversed(), bInv);
    ASSERT_EQ(b.getInverseTransposed(), bInv.getTransposed());
}

TEST(Matrix3Test, IsIdentity)
{
    const Michka::Matrix3 a;
    const Michka::Matrix3 b(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );

    ASSERT_TRUE(a.isIdentity());
    ASSERT_FALSE(b.isIdentity());
}

TEST(Matrix3Test, Operators)
{
    Michka::Matrix3 a;
    const Michka::Matrix3 b(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );
    f32 cValues[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    Michka::Matrix3 c(cValues);
    f32 dValues[3][3] = {
        {1.0f,  2.0f,  3.0f},
        {4.0f,  5.0f,  6.0f},
        {7.0f,  8.0f,  9.0f}
    };
    const Michka::Matrix3 d(dValues);
    const Michka::Matrix3 e(b);
    Michka::Matrix3 aPlusB(
        2.0f, 2.0f, 3.0f,
        4.0f, 6.0f, 6.0f,
        7.0f, 8.0f, 10.0f
    );
    Michka::Matrix3 bMinusA(
        0.0f,  2.0f,  3.0f,
        4.0f,  4.0f,  6.0f,
        7.0f,  8.0f, 8.0f
    );
    Michka::Matrix3 bMulC(
        30.0f,  36.0f,  42.0f,
        66.0f,  81.0f,  96.0f,
        102.0f, 126.0f, 150.0f
    );
    Michka::Matrix3 bNeg(
        -1.0f, -2.0f, -3.0f,
        -4.0f, -5.0f, -6.0f,
        -7.0f, -8.0f, -9.0f
    );
    Michka::Matrix3 bMulTwo(
        2.0f,  4.0f,  6.0f,
        8.0f,  10.0f, 12.0f,
        14.0f, 16.0f, 18.0f
    );

    ASSERT_EQ(a(0, 0), 1.0f);
    ASSERT_EQ(a(0, 1), 0.0f);
    ASSERT_EQ(a(1, 0), 0.0f);
    ASSERT_EQ(a(0), 1.0f);
    ASSERT_EQ(a(1), 0.0f);

    ASSERT_EQ(b(0, 0), 1.0f);
    ASSERT_EQ(b(0, 1), 2.0f);
    ASSERT_EQ(b(1, 0), 4.0f);
    ASSERT_EQ(b(0), 1.0f);
    ASSERT_EQ(b(1), 2.0f);

    ASSERT_EQ(c[0][0], 1.0f);
    ASSERT_EQ(c[0][1], 2.0f);
    ASSERT_EQ(c[1][0], 4.0f);

    ASSERT_EQ(d[0][0], 1.0f);
    ASSERT_EQ(d[0][1], 2.0f);
    ASSERT_EQ(d[1][0], 4.0f);

    ASSERT_TRUE(b == c);
    ASSERT_TRUE(b == e);
    ASSERT_TRUE(a != b);

    ASSERT_EQ(+b, b);
    ASSERT_EQ(-b, bNeg);
    ASSERT_EQ(a + b, aPlusB);
    ASSERT_EQ(b - a, bMinusA);
    ASSERT_EQ(b * 2, bMulTwo);
    ASSERT_EQ(b * Michka::Matrix3::identity, b);
    ASSERT_EQ(b * c, bMulC);

    c += a;
    ASSERT_EQ(c, aPlusB);
    c = b;
    c -= a;
    ASSERT_EQ(c, bMinusA);
    c = b;
    c *= 2;
    ASSERT_EQ(c, bMulTwo);
    c = b;
    c *= c;
    ASSERT_EQ(c, bMulC);
}

TEST(Matrix3Test, Transpose)
{
    const Michka::Matrix3 a(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );
    const Michka::Matrix3 aTransposed(
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f
    );

    ASSERT_EQ(a.getTransposed(), aTransposed);
}
