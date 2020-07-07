#include <gtest/gtest.h>
#include "Core/Math/Vector4.h"

TEST(Vector4Test, compare)
{
	const Michka::Vector4 a(0.0f, 1.0f, 0.0f);
	Michka::Vector4 b (0.0f, 0.0f, 1.0f);

	ASSERT_NE(a, b);

	b.setY(1.0f);
	ASSERT_NE(a, b);

	b.setZ(0.0f);
	ASSERT_EQ(a, b);
	ASSERT_EQ(a, Michka::Vector4::up);

	Michka::Vector4 c = a;
	ASSERT_EQ(b, c);
}


TEST(Vector4Test, dotProduct)
{
	Michka::Vector4 a(1.0f, 2.0f, 3.0f);
	const Michka::Vector4 b(1.0f, 5.0f, 7.0f);

	ASSERT_FLOAT_EQ(b.getDotProduct(a), 33.0f);
}

TEST(Vector4Test, operators)
{
	Michka::Vector4 a(5.0f, -10.0f, 15.0f, 1.0f);
	const Michka::Vector4 b(-5.0f, 10.0f, -15.0f, -1.0f);

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

	ASSERT_EQ(a * b, Michka::Vector4(-25.0f, -100.0f, -225.0f, -1.0f));
	ASSERT_EQ(a / Michka::Vector4(1.0, 2.0f, 3.0f), Michka::Vector4(5.0f, -5.0f, 5.0f));
	ASSERT_EQ(a * 2.0f, Michka::Vector4(10, -20.0f, 30.0f, 2.0f));
	ASSERT_EQ(2.0f * a, Michka::Vector4(10, -20.0f, 30.0f, 2.0f));
	ASSERT_EQ(a / 2.0f, Michka::Vector4(2.5f, -5.0f, 7.5f, 0.5f));
	ASSERT_EQ(1.0f / a, Michka::Vector4(1.0f/5.0f, -1.0f/10.0f, 1.0f/15.0f, 1.0f));

	ASSERT_EQ(a + 2.0f, Michka::Vector4(7.0f, -8.0f, 17.0f, 3.0f));
	ASSERT_EQ(a - 2.0f, Michka::Vector4(3.0f, -12.0f, 13.0f, -1.0f));
	ASSERT_EQ(2.0f + a, Michka::Vector4(7.0f, -8.0f, 17.0f, 3.0f));
	ASSERT_EQ(2.0f - a, Michka::Vector4(-3.0f, 12.0f, -13.0f, 1.0f));

	ASSERT_EQ(a + Michka::Vector4(2.0f, 3.0f, 4.0f), Michka::Vector4(7.0f, -7.0f, 19.0f, 2.0f));
	ASSERT_EQ(a - Michka::Vector4(2.0f, 3.0f, 4.0f), Michka::Vector4(3.0f, -13.0f, 11.0f, 0.0f));
}

TEST(Vector4Test, length)
{
	Michka::Vector4 a;
	a.setX(7.0f).setY(4.0f).setZ(3.0f);

	ASSERT_FLOAT_EQ(a.getLength(), 8.6023254f);
}
