#include <gtest/gtest.h>
#include "Core/Math/Vector3.h"

TEST(Vector3Test, compare)
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

TEST(Vector3Test, normalize)
{
	Michka::Vector3 a(5.0f, 10.0f, 5.0f);

	ASSERT_EQ(a.getNormalized(), Michka::Vector3(0.40825f, 0.8165f, 0.40825f));
	a.normalize();
	ASSERT_TRUE(a.isNormalized());
	ASSERT_FLOAT_EQ(a.getLength(), 1.0f);

	a.setX(0.0f).setY(0.0f).setZ(0.0f);
	ASSERT_EQ(a.getNormalized(), Michka::Vector3::zero);
}

TEST(Vector3Test, operators)
{
	Michka::Vector3 a(5.0f, -10.0f, 15.0f);
	Michka::Vector3 b(-5.0f, 10.0f, -15.0f);

	ASSERT_EQ(+a, a);
	ASSERT_EQ(-a, b);
	ASSERT_FLOAT_EQ(a[0], 5.0f);
	ASSERT_FLOAT_EQ(a[1], -10.0f);
	ASSERT_FLOAT_EQ(a[2], 15.0f);

	a[0] = -a[0];
	ASSERT_FLOAT_EQ(a[0], -5.0f);
	a[0] = -a[0];

	ASSERT_EQ(a * b, Michka::Vector3(-25.0f, -100.0f, -225.0f));
	ASSERT_EQ(a / Michka::Vector3(1.0, 2.0f, 3.0f), Michka::Vector3(5.0f, -5.0f, 5.0f));
	ASSERT_EQ(a * 2, Michka::Vector3(10, -20.0f, 30.0f));
	ASSERT_EQ(a / 2.0f, Michka::Vector3(2.5f, -5.0f, 7.5f));
}
