#include <gtest/gtest.h>
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"

TEST(Vector2Test, Compare)
{
    const Michka::Vector2 a(0.0f, 1.0f);
    Michka::Vector2 b (0.0f, 0.0f);

    ASSERT_NE(a, b);

    b.setY(1.0f);

    ASSERT_EQ(a, b);
    ASSERT_EQ(a, Michka::Vector2::up);

    Michka::Vector2 c = a;
    ASSERT_EQ(b, c);
}

TEST(Vector2Test, Normalize)
{
    Michka::Vector2 a;
    ASSERT_EQ(a, Michka::Vector2::zero);
    a.set(5.0f, 10.0f);

    ASSERT_EQ(a.getNormalized(), Michka::Vector2(0.44721f, 0.89442f));
    a.normalize();
    ASSERT_TRUE(a.isNormalized());
    ASSERT_FLOAT_EQ(a.getLength(), 1.0f);

    a.setX(0.0f).setY(0.0f);
    ASSERT_FALSE(a.isNormalizable());
    ASSERT_EQ(a.getNormalized(), Michka::Vector2::zero);
}

TEST(Vector2Test, Distance)
{
    Michka::Vector2 a(7.0f, 4.0f);
    const Michka::Vector2 b(17.0f, 6.0f);

    ASSERT_FLOAT_EQ(b.getDistanceFrom(a), 10.198039f);
    ASSERT_FLOAT_EQ(a.getDistanceFrom(Michka::Vector2(8.0f, 5.0f)), 1.414214f);
    ASSERT_FLOAT_EQ(b.getDistanceFrom(b), 0.0f);
}

TEST(Vector2Test, DotProduct)
{
    Michka::Vector2 a(1.0f, 2.0f);
    const Michka::Vector2 b(1.0f, 5.0f);

    ASSERT_FLOAT_EQ(b.getDotProduct(a), 11.0f);
}

TEST(Vector2Test, Reflect)
{
    Michka::Vector2 a(1.0f, 1.0f);
    a.reflect(Michka::Vector2::up);

    ASSERT_EQ(a, Michka::Vector2(1.0f, -1.0f));
}

TEST(Vector2Test, Angle)
{
    Michka::Vector2 a(0.0f, 1.0f);

    ASSERT_FLOAT_EQ(a.getAngleFrom(Michka::Vector2::right), 90.0f);
}

TEST(Vector2Test, Cast)
{
    Michka::Vector2 a(1.0f, 2.0f);
    Michka::Vector3 b = a;
    Michka::Vector4 c = a;

    ASSERT_EQ(b, Michka::Vector3(1.0f, 2.0f, 0.0f));
    ASSERT_EQ(c, Michka::Vector4(1.0f, 2.0f, 0.0f, 1.0f));
}

TEST(Vector2Test, Operators)
{
    Michka::Vector2 a(5.0f, -10.0f);
    const Michka::Vector2 b(-5.0f, 10.0f);

    ASSERT_EQ(+a, a);
    ASSERT_EQ(-a, b);
    ASSERT_FLOAT_EQ(a[0], 5.0f);
    ASSERT_FLOAT_EQ(a[1], -10.0f);
    ASSERT_FLOAT_EQ(b[0], -5.0f);
    ASSERT_FLOAT_EQ(b[1], 10.0f);

    a[0] = -a[0];
    ASSERT_FLOAT_EQ(a[0], -5.0f);
    a[0] = -a[0];

    ASSERT_EQ(a * b, Michka::Vector2(-25.0f, -100.0f));
    ASSERT_EQ(a / Michka::Vector2(1.0, 2.0f), Michka::Vector2(5.0f, -5.0f));
    ASSERT_EQ(a * 2.0f, Michka::Vector2(10, -20.0f));
    ASSERT_EQ(2.0f * a, Michka::Vector2(10, -20.0f));
    ASSERT_EQ(a / 2.0f, Michka::Vector2(2.5f, -5.0f));
    ASSERT_EQ(1.0f / a, Michka::Vector2(1.0f/5.0f, -1.0f/10.0f));

    ASSERT_EQ(a + 2.0f, Michka::Vector2(7.0f, -8.0f));
    ASSERT_EQ(a - 2.0f, Michka::Vector2(3.0f, -12.0f));
    ASSERT_EQ(2.0f + a, Michka::Vector2(7.0f, -8.0f));
    ASSERT_EQ(2.0f - a, Michka::Vector2(-3.0f, 12.0f));

    ASSERT_EQ(a + Michka::Vector2(2.0f, 3.0f), Michka::Vector2(7.0f, -7.0f));
    ASSERT_EQ(a - Michka::Vector2(2.0f, 3.0f), Michka::Vector2(3.0f, -13.0f));
}
