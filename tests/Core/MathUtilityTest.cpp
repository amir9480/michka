#include <gtest/gtest.h>
#include "Core/Math/Utility.h"

TEST(MathUtilityTest, Abs)
{
    ASSERT_EQ(Michka::Math::abs(10), 10);
    ASSERT_EQ(Michka::Math::abs(-10), 10);
    ASSERT_EQ(Michka::Math::abs(3.14f), 3.14f);
    ASSERT_EQ(Michka::Math::abs(-3.14f), 3.14f);
}

TEST(MathUtilityTest, FloatEqual)
{
    ASSERT_TRUE(Michka::Math::equals(5, 5));
    ASSERT_FALSE(Michka::Math::equals(5, 6));
    ASSERT_TRUE(Michka::Math::equals(31.4f/10.0f, 3.14f));
    ASSERT_TRUE(Michka::Math::equals(31.4/10.0, 3.14));
    ASSERT_TRUE(Michka::Math::equals(31.4L/10.0L, 3.14L));
    ASSERT_FALSE(Michka::Math::equals(31.4L/10.0L, 3.0L));
}

TEST(MathUtilityTest, Mod)
{
    ASSERT_EQ(Michka::Math::mod(4, 2), 0);
    ASSERT_EQ(Michka::Math::mod(5, 2), 1);
    ASSERT_FLOAT_EQ(Michka::Math::mod(4.0f, 2.5f), 1.5f);
    ASSERT_FLOAT_EQ(Michka::Math::mod(5.0f, 2.5f), 0.0f);
    ASSERT_DOUBLE_EQ(Michka::Math::mod(4.0, 2.5), 1.5);
    ASSERT_DOUBLE_EQ(Michka::Math::mod(5.0, 2.5), 0.0);
    ASSERT_DOUBLE_EQ(Michka::Math::mod(4.0L, 2.5L), 1.5L);
    ASSERT_DOUBLE_EQ(Michka::Math::mod(5.0L, 2.5L), 0.0L);
}

TEST(MathUtilityTest, FloorAndCeil)
{
    ASSERT_FLOAT_EQ(Michka::Math::floor(0.0f), 0.0f);
    ASSERT_FLOAT_EQ(Michka::Math::ceil(0.0f), 0.0f);

    ASSERT_FLOAT_EQ(Michka::Math::floor(1.0f), 1.0f);
    ASSERT_FLOAT_EQ(Michka::Math::ceil(1.0f), 1.0f);

    ASSERT_FLOAT_EQ(Michka::Math::floor(-1.0f), -1.0f);
    ASSERT_FLOAT_EQ(Michka::Math::ceil(-1.0f), -1.0f);

    ASSERT_FLOAT_EQ(Michka::Math::floor(1.5f), 1.0f);
    ASSERT_FLOAT_EQ(Michka::Math::ceil(1.5f), 2.0f);

    ASSERT_FLOAT_EQ(Michka::Math::floor(-1.5f), -2.0f);
    ASSERT_FLOAT_EQ(Michka::Math::ceil(-1.5f), -1.0f);
}

TEST(MathUtilityTest, Round)
{
    ASSERT_FLOAT_EQ(Michka::Math::round(0.0f, 0.01f), 0.0f);
    ASSERT_FLOAT_EQ(Michka::Math::round(0.1f, 0.01f), 0.1f);
    ASSERT_FLOAT_EQ(Michka::Math::round(1.0f, 0.01f), 1.0f);
    ASSERT_FLOAT_EQ(Michka::Math::round(0.01f, 0.01f), 0.01f);
    ASSERT_FLOAT_EQ(Michka::Math::round(0.001f, 0.01f), 0.0f);
    ASSERT_FLOAT_EQ(Michka::Math::round(0.005f, 0.01f), 0.01f);
    ASSERT_FLOAT_EQ(Michka::Math::round(0.007f, 0.01f), 0.01f);
}

TEST(MathUtilityTest, Sqrt)
{
    ASSERT_FLOAT_EQ(Michka::Math::sqrt(1.0f), 1.0f);
    ASSERT_FLOAT_EQ(Michka::Math::sqrt(2.0f), 1.41421356f);
    ASSERT_FLOAT_EQ(Michka::Math::sqrt(4.0f), 2.0f);
    ASSERT_FLOAT_EQ(Michka::Math::sqrt(9.0f), 3.0f);
    ASSERT_FLOAT_EQ(Michka::Math::sqrt(16.0f), 4.0f);
    ASSERT_FLOAT_EQ(Michka::Math::sqrt(25.0f), 5.0f);
}

TEST(MathUtilityTest, Clamp)
{
    ASSERT_EQ(Michka::Math::clamp(1), 1);
    ASSERT_EQ(Michka::Math::clamp(2), 1);
    ASSERT_EQ(Michka::Math::clamp(-1), 0);

    ASSERT_EQ(Michka::Math::clamp(70, 50, 100), 70);
    ASSERT_EQ(Michka::Math::clamp(200, 50, 100), 100);
    ASSERT_EQ(Michka::Math::clamp(0, 50, 100), 50);
}

TEST(MathUtilityTest, Lerp)
{
    ASSERT_FLOAT_EQ(Michka::Math::lerp(1, 3, 0), 1);
    ASSERT_FLOAT_EQ(Michka::Math::lerp(1, 3, 0.25f), 1.5f);
    ASSERT_FLOAT_EQ(Michka::Math::lerp(1, 3, 0.5f), 2);
    ASSERT_FLOAT_EQ(Michka::Math::lerp(1, 3, 0.75f), 2.5f);
    ASSERT_FLOAT_EQ(Michka::Math::lerp(1, 3, 1), 3);
}

TEST(MathUtilityTest, Sign)
{
    ASSERT_EQ(Michka::Math::sign(-5), -1);
    ASSERT_EQ(Michka::Math::sign(0), 0);
    ASSERT_EQ(Michka::Math::sign(5), 1);
}

TEST(MathUtilityTest, DegreesAndRadiansConversion)
{
    ASSERT_NEAR(Michka::Math::degreesToRadians(0.0f), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::degreesToRadians(30.0f), 0.5235987755f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::degreesToRadians(60.0f), 1.0471975511f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::degreesToRadians(90.0f), 0.5f * Michka::Math::pi, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::degreesToRadians(180.0f), Michka::Math::pi, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::degreesToRadians(360.0f), 2 * Michka::Math::pi, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::degreesToRadians(-30.0f), -0.5235987755f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::radiansToDegrees(0.0f), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::radiansToDegrees(0.5235987755f), 30.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::radiansToDegrees(1.0471975511f), 60.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::radiansToDegrees(0.5f * Michka::Math::pi), 90.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::radiansToDegrees(Michka::Math::pi), 180.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::radiansToDegrees(2 * Michka::Math::pi), 360.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::radiansToDegrees(-0.5235987755f), -30.0f, Michka::Math::epsilon);
}

TEST(MathUtilityTest, Other)
{
    ASSERT_NEAR(Michka::Math::sin(0), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::sin(30), 0.5f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::sin(60), 0.8660254f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::sin(90), 1.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::sin(180), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::sin(270), -1.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::sin(-90.0f), -1.0f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::cos(0), 1.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cos(30), 0.8660254f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cos(60), 0.5f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cos(90), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cos(180), -1.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cos(270), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cos(-90.0f), 0.0f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::tan(0), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::tan(30), 0.57735027f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::tan(45), 1.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::tan(60), 1.73205081f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::cotan(30), 1.73205081f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cotan(45), 1.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cotan(60), 0.57735027f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::cotan(90), 0.0f, Michka::Math::epsilon);

    /* -------------------------------------------------------------------------- */

    ASSERT_NEAR(Michka::Math::asin(0.0f), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::asin(0.5f), 30.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::asin(0.8660254f), 60.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::asin(1.0f), 90.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::asin(-1.0f), -90.0f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::acos(1.0f), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acos(0.8660254f), 30.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acos(0.5f), 60.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acos(0.0f), 90.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acos(-1.0f), 180.0f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::atan(0.0f), 0.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::atan(0.57735027f), 30.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::atan(1.0f), 45.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::atan(1.73205081f), 60.0f, Michka::Math::epsilon);

    ASSERT_NEAR(Michka::Math::acotan(1.73205081f), 30.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acotan(1.0f), 45.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acotan(0.57735027f), 60.0f, Michka::Math::epsilon);
    ASSERT_NEAR(Michka::Math::acotan(0.0f), 90.0f, Michka::Math::epsilon);
}
