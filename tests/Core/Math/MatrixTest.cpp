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
#include "Core/Math/Matrix.h"
#include "Core/Math/Matrix3.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"
#include "Core/Types.h"

TEST(MatrixTest, Cast)
{
    Michka::Matrix a = Michka::Matrix::createRotationMatrix(45.0f, 90.0f, 60.0f);
    Michka::Matrix3 b = a;

    ASSERT_EQ(b, Michka::Matrix3::createRotationMatrix(45.0f, 90.0f, 60.0f));
}

TEST(MatrixTest, CreateOrthgraphicProjection)
{
    {
        // By left / right / top / bottom
        Michka::Matrix mat = Michka::Matrix::createOrthgraphicProjection(0.0f, 100.0f, 0.0f, 100.0f, 1.0f, 100.0f);
        Michka::Vector4 pos;
        pos = Michka::Vector4(0.0f, 0.0f, 1.0f) * mat;
        pos /= pos.w;

        ASSERT_EQ(pos, Michka::Vector4(-1.0f, 1.0f, 0.0f));

        pos = Michka::Vector4(50.0f, 50.0f, 100.0f) * mat;
        pos /= pos.w;

        ASSERT_EQ(pos, Michka::Vector4(0.0f, 0.0f, 0.999999f));
    }
    {
        // By width and height
        Michka::Matrix mat = Michka::Matrix::createOrthgraphicProjection(640.0f, 480.0f, 1.0f, 100.0f);
        Michka::Vector4 pos;
        pos = Michka::Vector4(0.0f, 0.0f, 1.0f) * mat;
        pos /= pos.w;

        ASSERT_EQ(pos, Michka::Vector4(0.0f, 0.0f, 0.0f));

        pos = Michka::Vector4(0.0f, 0.0f, 100.0f) * mat;
        pos /= pos.w;

        ASSERT_EQ(pos, Michka::Vector4(0.0f, 0.0f, 0.999999f));

        pos = Michka::Vector4(-320.0f, -240.0f, 1.0f) * mat;
        pos /= pos.w;

        ASSERT_EQ(pos, Michka::Vector4(-1.0f, -1.0f, 0.0f));
    }
}

TEST(MatrixTest, CreatePerspectiveProjection)
{
    Michka::Matrix mat = Michka::Matrix::createPerspectiveProjection(45.0f, 4.0f/3.0f, 1.0f, 100.0f);
    Michka::Vector4 pos;
    pos = Michka::Vector4(0.0f, 0.0f, 1.0f) * mat;
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(0.0f, 0.0f, 0.0f));

    pos = Michka::Vector4(0.0f, 0.0f, 100.0f) * mat;
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(0.0f, 0.0f, 0.999999f));
}

TEST(MatrixTest, CreateRotationMatrix)
{
    Michka::Vector4 pos;
    pos = Michka::Vector4(0.0f, 1.0f, 0.0f) * Michka::Matrix::createRotationMatrixX(90.0f);
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(0.0f, 0.0f, 1.0f));

    pos = Michka::Vector4(0.0f, 0.0f, 1.0f) * Michka::Matrix::createRotationMatrixY(90.0f);
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(1.0f, 0.0f, 0.0f));

    pos = Michka::Vector4(0.0f, 1.0f, 0.0f) * Michka::Matrix::createRotationMatrixZ(90.0f);
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(-1.0f, 0.0f, 0.0f));

    pos = Michka::Vector4(0.0f, 1.0f, 0.0f) * Michka::Matrix::createRotationMatrixZ(-90.0f);
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(1.0f, 0.0f, 0.0f));

    pos = Michka::Vector4(0.0f, 1.0f, 0.0f) * Michka::Matrix::createRotationMatrix(90.0f, 90.0f, 0.0f);
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(1.0f, 0.0f, 0.0f));

    pos = Michka::Vector4(0.0f, 1.0f, 0.0f) * Michka::Matrix::createRotationMatrixAxis(Michka::Vector3::forward, -90.0f);
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(1.0f, 0.0f, 0.0f));
}

TEST(MatrixTest, CreateScaleMatrix)
{
    Michka::Matrix mat = Michka::Matrix::createScaleMatrix(Michka::Vector3(1.0f, 2.0f, 3.0f));
    Michka::Vector4 pos(1.0f, 2.0f, 3.0f);
    pos *= mat;
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(1.0f, 4.0f, 9.0f));
}

TEST(MatrixTest, CreateTranslationMatrix)
{
    Michka::Matrix mat = Michka::Matrix::createTranslationMatrix(Michka::Vector3(1.0f, 2.0f, 3.0f));
    Michka::Vector4 pos;
    pos *= mat;
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(1.0f, 2.0f, 3.0f));
}

TEST(MatrixTest, CreateViewMatrix)
{
    Michka::Matrix mat = Michka::Matrix::createViewMatrix(Michka::Vector3(0.0f, 1.0f, 1.0f), Michka::Vector3::forward, Michka::Vector3::up);
    Michka::Vector4 pos;
    pos *= mat;
    pos /= pos.w;

    ASSERT_EQ(pos, Michka::Vector4(0.0f, 1.0f, 1.0f));
}

TEST(MatrixTest, Determinant)
{
    const Michka::Matrix a(
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );
    const Michka::Matrix b(
        5.0f, 1.0f, 6.0f, 3.0f,
        8.0f, 4.0f, 2.0f, 2.0f,
        7.0f, 6.0f, 5.0f, 4.0f,
        1.0f, 9.0f, 6.0f, 5.0f
    );

    ASSERT_FLOAT_EQ(a.getDeterminant(), 0.0f);
    ASSERT_FLOAT_EQ(b.getDeterminant(), -60.0f);
}

TEST(MatrixTest, Inverse)
{
    const Michka::Matrix a(
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );
    const Michka::Matrix b(
        5.0f, 1.0f, 6.0f, 3.0f,
        8.0f, 4.0f, 2.0f, 2.0f,
        7.0f, 6.0f, 5.0f, 4.0f,
        1.0f, 9.0f, 6.0f, 5.0f
    );
    const Michka::Matrix bInv(
          1.0f/30.0f,   1.0f/6.0f,  -1.0f/15.0f,  -1.0f/30.0f,
          1.0f/3.0f,    7.0f/6.0f,  -5.0f/3.0f,    2.0f/3.0f,
         29.0f/30.0f,  11.0f/6.0f, -44.0f/15.0f,  31.0f/30.0f,
        -53.0f/30.0f, -13.0f/3.0f,  98.0f/15.0f, -67.0f/30.0f
    );

    ASSERT_FALSE(a.isInversable());
    ASSERT_TRUE(b.isInversable());
    ASSERT_EQ(a.getInversed(), a);
    ASSERT_EQ(b.getInversed(), bInv);
    ASSERT_EQ(b.getInverseTransposed(), bInv.getTransposed());
}

TEST(MatrixTest, IsIdentity)
{
    const Michka::Matrix a;
    const Michka::Matrix b(
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );

    ASSERT_TRUE(a.isIdentity());
    ASSERT_FALSE(b.isIdentity());
}

TEST(MatrixTest, Operators)
{
    Michka::Matrix a;
    const Michka::Matrix b(
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );
    f32 cValues[16] = {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    Michka::Matrix c(cValues);
    f32 dValues[4][4] = {
        {1.0f,  2.0f,  3.0f,  4.0f},
        {5.0f,  6.0f,  7.0f,  8.0f},
        {9.0f,  10.0f, 11.0f, 12.0f},
        {13.0f, 14.0f, 15.0f, 16.0f}
    };
    const Michka::Matrix d(dValues);
    const Michka::Matrix e(b);
    Michka::Matrix aPlusB(
        2.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  7.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 12.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 17.0f
    );
    Michka::Matrix bMinusA(
        0.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  5.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 10.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 15.0f
    );
    Michka::Matrix bMulC(
        90.0f, 100.0f, 110.0f, 120.0f,
        202.0f, 228.0f, 254.0f, 280.0f,
        314.0f, 356.0f, 398.0f, 440.0f,
        426.0f, 484.0f, 542.0f, 600.0f
    );
    Michka::Matrix bNeg(
        -1.0f,  -2.0f,  -3.0f,  -4.0f,
        -5.0f,  -6.0f,  -7.0f,  -8.0f,
        -9.0f,  -10.0f, -11.0f, -12.0f,
        -13.0f, -14.0f, -15.0f, -16.0f
    );
    Michka::Matrix bMulTwo(
        2.0f,  4.0f,  6.0f,  8.0f,
        10.0f, 12.0f, 14.0f, 16.0f,
        18.0f, 20.0f, 22.0f, 24.0f,
        26.0f, 28.0f, 30.0f, 32.0f
    );

    ASSERT_EQ(a(0, 0), 1.0f);
    ASSERT_EQ(a(0, 1), 0.0f);
    ASSERT_EQ(a(1, 0), 0.0f);
    ASSERT_EQ(a(0), 1.0f);
    ASSERT_EQ(a(1), 0.0f);
    ASSERT_EQ(a(4), 0.0f);

    ASSERT_EQ(b(0, 0), 1.0f);
    ASSERT_EQ(b(0, 1), 2.0f);
    ASSERT_EQ(b(1, 0), 5.0f);
    ASSERT_EQ(b(0), 1.0f);
    ASSERT_EQ(b(1), 2.0f);
    ASSERT_EQ(b(4), 5.0f);

    ASSERT_EQ(c[0][0], 1.0f);
    ASSERT_EQ(c[0][1], 2.0f);
    ASSERT_EQ(c[1][0], 5.0f);

    ASSERT_EQ(d[0][0], 1.0f);
    ASSERT_EQ(d[0][1], 2.0f);
    ASSERT_EQ(d[1][0], 5.0f);

    ASSERT_TRUE(b == c);
    ASSERT_TRUE(b == e);
    ASSERT_TRUE(a != b);

    ASSERT_EQ(+b, b);
    ASSERT_EQ(-b, bNeg);
    ASSERT_EQ(a + b, aPlusB);
    ASSERT_EQ(b - a, bMinusA);
    ASSERT_EQ(b * 2, bMulTwo);
    ASSERT_EQ(b * Michka::Matrix::identity, b);
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

TEST(MatrixTest, Transpose)
{
    const Michka::Matrix a(
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );
    const Michka::Matrix aTransposed(
        1.0f,  5.0f,  9.0f,  13.0f,
        2.0f,  6.0f,  10.0f, 14.0f,
        3.0f,  7.0f,  11.0f, 15.0f,
        4.0f,  8.0f,  12.0f, 16.0f
    );

    ASSERT_EQ(a.getTransposed(), aTransposed);
}

