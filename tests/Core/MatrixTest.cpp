#include <gtest/gtest.h>
#include "Core/Math/Matrix.h"

TEST(MatrixTest, isIdentity)
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

TEST(MatrixTest, determinant)
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

TEST(MatrixTest, inverse)
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

TEST(MatrixTest, transpose)
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

TEST(MatrixTest, operators)
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

