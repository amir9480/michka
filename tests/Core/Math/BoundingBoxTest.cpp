#include <gtest/gtest.h>
#include "Core/Math/BoundingBox.h"

TEST(BoundingBoxTest, merge)
{
    Michka::BoundingBox a(-1.0f, 1.0f);

    a.merge(Michka::Vector3::up * 2);
    ASSERT_EQ(a, Michka::BoundingBox(-1.0f, -1.0f, -1.0f, 1.0f, 2.0f, 1.0f));

    a.merge(Michka::Vector3::left * 2);
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -1.0f, -1.0f, 1.0f, 2.0f, 1.0f));

    a.merge(Michka::Vector3::right * 2);
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -1.0f, -1.0f, 2.0f, 2.0f, 1.0f));

    a.merge(Michka::Vector3::down * 2);
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -2.0f, -1.0f, 2.0f, 2.0f, 1.0f));

    a.merge(Michka::Vector3::forward * 2);
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -2.0f, -1.0f, 2.0f, 2.0f, 2.0f));

    a.merge(Michka::Vector3::back * 2);
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -2.0f, -2.0f, 2.0f, 2.0f, 2.0f));

    a.set(-Michka::Vector3::one, Michka::Vector3::one);
    a.merge(Michka::BoundingBox(-Michka::Vector3::one * 2, Michka::Vector3::one * 2));
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -2.0f, -2.0f, 2.0f, 2.0f, 2.0f));
}

TEST(BoundingBoxTest, check)
{
    Michka::BoundingBox a(-Michka::Vector3::one, Michka::Vector3::one);

    ASSERT_TRUE(a.check());
    a.min.x = 1.5f;
    ASSERT_FALSE(a.check());
}

TEST(BoundingBoxTest, fix)
{
    Michka::BoundingBox a;

    a.set(Michka::Vector3::one, -Michka::Vector3::one);
    a.fix();

    ASSERT_EQ(a, Michka::BoundingBox(-Michka::Vector3::one, Michka::Vector3::one));
}

TEST(BoundingBoxTest, getCenter)
{
    Michka::BoundingBox a;

    a.set(Michka::Vector3::one * 2, Michka::Vector3::one * 4);

    ASSERT_EQ(a.getCenter(), Michka::Vector3::one * 3.0f);
}

TEST(BoundingBoxTest, getCorner)
{
    Michka::BoundingBox a(-Michka::Vector3::one * 2.0f, Michka::Vector3::one * 2.0f);

    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::leftDownBack), Michka::Vector3(-2.0f, -2.0f, -2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::leftDownForward), Michka::Vector3(-2.0f, -2.0f, 2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::leftUpBack), Michka::Vector3(-2.0f, 2.0f, -2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::leftUpForward), Michka::Vector3(-2.0f, 2.0f, 2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::rightDownBack), Michka::Vector3(2.0f, -2.0f, -2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::rightDownForward), Michka::Vector3(2.0f, -2.0f, 2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::rightUpBack), Michka::Vector3(2.0f, 2.0f, -2.0f));
    ASSERT_EQ(a.getCorner(Michka::BoundingBox::Corner::rightUpForward), Michka::Vector3(2.0f, 2.0f, 2.0f));
}
