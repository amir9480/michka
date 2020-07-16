#include <gtest/gtest.h>
#include "Core/Math/BoundingBox.h"
#include "Core/Math/BoundingSphere.h"
#include "Core/Math/Matrix3.h"
#include "Core/Math/Matrix.h"

TEST(BoundingBoxTest, Check)
{
    Michka::BoundingBox a(-Michka::Vector3::one, Michka::Vector3::one);

    ASSERT_TRUE(a.check());
    a.min.x = 1.5f;
    ASSERT_FALSE(a.check());
}

TEST(BoundingBoxTest, Fix)
{
    Michka::BoundingBox a;

    a.set(Michka::Vector3::one, -Michka::Vector3::one);
    a.fix();

    ASSERT_EQ(a, Michka::BoundingBox(-Michka::Vector3::one, Michka::Vector3::one));
}

TEST(BoundingBoxTest, GetCenter)
{
    Michka::BoundingBox a;

    a.set(Michka::Vector3::one * 2, Michka::Vector3::one * 4);

    ASSERT_EQ(a.getCenter(), Michka::Vector3::one * 3.0f);
}

TEST(BoundingBoxTest, GetCorner)
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

TEST(BoundingBoxTest, GetIntersection)
{
    Michka::BoundingBox a(Michka::Vector3::one, Michka::Vector3::one * 2.0f);

    ASSERT_EQ(a.getIntersection(Michka::BoundingBox(Michka::Vector3(0.5f, 0.5f, 0.5f), Michka::Vector3(1.5f, 1.5f, 1.5f))), Michka::Intersection::Intersect);
    ASSERT_EQ(a.getIntersection(Michka::BoundingBox(-2.0 * Michka::Vector3::one, Michka::Vector3::zero)), Michka::Intersection::Outside);
    ASSERT_EQ(a.getIntersection(Michka::BoundingBox(Michka::Vector3::one, Michka::Vector3(1.5f, 1.5f, 1.5f))), Michka::Intersection::Inside);
}

TEST(BoundingBoxTest, GetSizeVector)
{
    Michka::BoundingBox a(-Michka::Vector3::one * 2.0f, Michka::Vector3::one * 2.0f);

    ASSERT_EQ(a.getSizeVector(), 4.0f * Michka::Vector3::one);
}

TEST(BoundingBoxTest, IsInside)
{
    Michka::BoundingBox a(Michka::Vector3::one, Michka::Vector3::one * 2.0f);

    ASSERT_TRUE(a.isInside(Michka::BoundingBox(Michka::Vector3(0.5f, 0.5f, 0.5f), Michka::Vector3(1.5f, 1.5f, 1.5f))));
    ASSERT_TRUE(a.isInside(Michka::BoundingBox(Michka::Vector3(1.1f, 1.1f, 1.1f), Michka::Vector3(1.5f, 1.5f, 1.5f))));
    ASSERT_TRUE(a.isInside(Michka::BoundingBox(-20.0f * Michka::Vector3::one, 20.0f * Michka::Vector3::one)));
    ASSERT_FALSE(a.isInside(Michka::BoundingBox(-2.0 * Michka::Vector3::one, Michka::Vector3::zero)));

    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(Michka::Vector3::one, 1.0f)));
    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(-Michka::Vector3::one, 4.0f)));
    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(2.5f * Michka::Vector3::one, 1.0f)));
    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(Michka::Vector3(1.5f, 1.5f, 1.5f), 0.2f)));
    ASSERT_TRUE(a.isInside(Michka::BoundingSphere(Michka::Vector3::zero, 100.0f)));
    ASSERT_FALSE(a.isInside(Michka::BoundingSphere(Michka::Vector3::down, 1.0f)));

    ASSERT_TRUE(a.isInside(Michka::Vector3(1.5f, 1.2f, 1.8f)));
    ASSERT_FALSE(a.isInside(Michka::Vector3(1.5f, 1.2f, 2.1f)));
}

TEST(BoundingBoxTest, Merge)
{
    Michka::BoundingBox a(-1.0f, 1.0f);

    a.merge(Michka::Vector3::up * 2);
    ASSERT_NE(a, Michka::BoundingBox(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f));
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

    a = Michka::BoundingBox(-Michka::Vector3::one, Michka::Vector3::one);
    a.merge(Michka::BoundingBox(-Michka::Vector3::one * 2, Michka::Vector3::one * 2));
    ASSERT_EQ(a, Michka::BoundingBox(-2.0f, -2.0f, -2.0f, 2.0f, 2.0f, 2.0f));

    ASSERT_EQ(a.getMerged(3.0f * Michka::Vector3::one), Michka::BoundingBox(-2.0f * Michka::Vector3::one, 3.0f * Michka::Vector3::one));
    ASSERT_EQ(a.getMerged(Michka::BoundingBox(-3.0f * Michka::Vector3::one, 3.0f * Michka::Vector3::one)), Michka::BoundingBox(-3.0f * Michka::Vector3::one, 3.0f * Michka::Vector3::one));
}

TEST(BoundingBoxTest, Transform)
{
    Michka::BoundingBox a(Michka::Vector3::one, Michka::Vector3::one * 2.0f);

    ASSERT_EQ(
        a.getTransformed(Michka::Matrix3::createRotationMatrixY(90.0f)),
        Michka::BoundingBox(1.0f, 1.0f, -2.0f, 2.0f, 2.0f, -1.0f)
    );

    ASSERT_EQ(
        a.getTransformed(Michka::Matrix::createRotationMatrixY(90.0f) * Michka::Matrix::createTranslationMatrix(Michka::Vector3(0.0f, 1.0f, 0.0f))),
        Michka::BoundingBox(1.0f, 2.0f, -2.0f, 2.0f, 3.0f, -1.0f)
    );
}
