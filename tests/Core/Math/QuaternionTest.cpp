#include <gtest/gtest.h>
#include "Core/Math/Quaternion.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"

TEST(QuaternionTest, Conjugate)
{
    Michka::Quaternion a(1.0f, 2.0f, 3.0f, 1.0f);
    ASSERT_EQ(a.getConjugated(), Michka::Quaternion(-1.0f, -2.0f, -3.0f, 1.0f));
}

TEST(QuaternionTest, Create)
{
    {
        Michka::Quaternion q;
        ASSERT_EQ(q, Michka::Quaternion::identity);
        ASSERT_TRUE(q.isIdentity());
    }
    {
        Michka::Quaternion q(0.0f, 0.0f, 0.0f, 0.0f);
        ASSERT_EQ(q, Michka::Quaternion::zero);
    }
    {
        Michka::Quaternion q(0.0f, 90.0f, 0.0f);
        ASSERT_EQ(q, Michka::Quaternion(0.0f, 0.707106f, 0.0f, 0.707106f));
    }
    {
        Michka::Quaternion q(45.0f, -60.0f, 0.0f);
        ASSERT_EQ(q, Michka::Quaternion(0.331413f, -0.461939f, -0.191341f, 0.800103f));
    }
    {
        Michka::Quaternion q(Michka::Vector3(45.0f, -60.0f, 0.0f));
        ASSERT_EQ(q, Michka::Quaternion(0.331413f, -0.461939f, -0.191341f, 0.800103f));
    }
    {
        Michka::Quaternion q(Michka::Matrix::createRotationMatrixY(90.0f));
        ASSERT_EQ(q, Michka::Quaternion(0.0f, 90.0f, 0.0f));

        q = Michka::Matrix::createRotationMatrixX(180.0f);
        ASSERT_EQ(q, Michka::Quaternion(180.0f, 0.0f, 0.0f));
        q = Michka::Matrix::createRotationMatrixY(180.0f);
        ASSERT_EQ(q, Michka::Quaternion(0.0f, 180.0f, 0.0f));
        q = Michka::Matrix::createRotationMatrixZ(180.0f);
        ASSERT_EQ(q, Michka::Quaternion(0.0f, 0.0f, 180.0f));

        Michka::Quaternion q2(q);
        ASSERT_EQ(q2, Michka::Quaternion(0.0f, 0.0f, 180.0f));
    }
    {
        Michka::Quaternion q(Michka::Vector3::up, 90.0f);
        ASSERT_EQ(q, Michka::Quaternion(0.0f, 90.0f, 0.0f));
    }
    {
        Michka::Quaternion q2(Michka::Vector3::forward, Michka::Vector3::right);
        ASSERT_EQ(q2, Michka::Quaternion(0.0f, 90.0f, 0.0f));
    }
}

TEST(QuaternionTest, CrossProduct)
{
    Michka::Quaternion a(0.0f, 90.0f, 0.0f);
    ASSERT_EQ(a.getCrossProduct(Michka::Quaternion(0.0f, 0.0f, 0.0f)), Michka::Quaternion(-90.0f, 0.0f, 0.0f));
}

TEST(QuaternionTest, DotProduct)
{
    Michka::Quaternion a(1.0f, 2.0f, 3.0f, 1.0f);
    const Michka::Quaternion b(1.0f, 5.0f, 7.0f, 1.0f);

    ASSERT_FLOAT_EQ(b.getDotProduct(a), 33.0f);
}

TEST(QuaternionTest, GetExponent)
{
    Michka::Quaternion a (0.0f, 90.0f, 0.0f);
    Michka::Quaternion b = a.getExponent();
    ASSERT_EQ(b, Michka::Quaternion(0.0f, 0.0123f, 0.0f, 0.9999f));

    a = Michka::Quaternion(0.0f, 0.0f, 0.0f);
    b = a.getExponent();
    ASSERT_EQ(b, Michka::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
}

TEST(QuaternionTest, GetLog)
{
    Michka::Quaternion a (0.0f, 90.0f, 0.0f);
    Michka::Quaternion b = a.getLog();
    ASSERT_EQ(b, Michka::Quaternion(0.0f, 24.9356f, 0.0f, 0.0f));

    a = Michka::Quaternion(0.0f, 0.0f, 0.0f);
    b = a.getExponent();
    ASSERT_EQ(b, Michka::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
}

TEST(QuaternionTest, Inverse)
{
    {
        Michka::Quaternion a(0.0f, 0.0f, 0.0f, 0.0f);
        ASSERT_FALSE(a.isInversable());
        ASSERT_EQ(a.getInversed(), Michka::Quaternion::zero);
    }
    {
        Michka::Quaternion a(2.0f, 1.0f, 2.0f, 1.0f);
        ASSERT_EQ(a.getInversed(), Michka::Quaternion(-0.632455f, -0.316227f, -0.632455f, 0.316227f));
    }
    {
        Michka::Quaternion q(Michka::Vector3::left, 90.0f);
        Michka::Vector3 axis = Michka::Vector3::forward;
        axis *= q.toMatrix();
        ASSERT_EQ(axis, Michka::Vector3::up);
        axis *= q.getInversed().toMatrix();
        ASSERT_EQ(axis, Michka::Vector3::forward);
    }
    {
        Michka::Quaternion q(Michka::Vector3::up, 90.0f);
        Michka::Vector3 axis = Michka::Vector3::forward;
        axis *= q.toMatrix();
        ASSERT_EQ(axis, Michka::Vector3::right);
        axis *= q.getInversed().toMatrix();
        ASSERT_EQ(axis, Michka::Vector3::forward);
    }
    {
        Michka::Quaternion q(Michka::Vector3::forward, 90.0f);
        Michka::Vector3 axis = Michka::Vector3::up;
        axis *= q.toMatrix();
        ASSERT_EQ(axis, Michka::Vector3::left);
        axis *= q.getInversed().toMatrix();
        ASSERT_EQ(axis, Michka::Vector3::up);
    }
}

TEST(QuaternionTest, Lerp)
{
    Michka::Quaternion a(0.0f, 0.0f, 0.0f);
    Michka::Quaternion b(0.0f, 90.0f, 0.0f);
    ASSERT_EQ(Michka::Quaternion::lerp(a, b, 0.0f), a);
    ASSERT_EQ(Michka::Quaternion::lerp(a, b, 1.0f), b);
    ASSERT_EQ(Michka::Quaternion::lerp(a, b, 0.5f), Michka::Quaternion(0.0f, 45.0f, 0.0f));

    b.set(0.0f, 270.0f, 0.0f);
    ASSERT_EQ(Michka::Quaternion::lerp(a, b, 0.5f), Michka::Quaternion(0.0f, 135.0f, 0.0f));
    ASSERT_EQ(Michka::Quaternion::lerp(a, b, 0.5f, true), Michka::Quaternion(0.0f, -45.0f, 0.0f));
}

TEST(QuaternionTest, Normalize)
{
    Michka::Quaternion a;
    ASSERT_EQ(a, Michka::Quaternion::identity);
    a.set(2.0f, -5.0f, 4.0f, 1.0f);

    ASSERT_EQ(a.getNormalized(), Michka::Quaternion(0.294883f, -0.737209f, 0.589767f, 0.147441f));
    a.normalize();
    ASSERT_TRUE(a.isNormalized());
    ASSERT_FLOAT_EQ(a.getLength(), 1.0f);

    a = Michka::Quaternion::zero;
    ASSERT_FALSE(a.isNormalizable());
    ASSERT_EQ(a.getNormalized(), Michka::Quaternion::zero);
}

TEST(QuaternionTest, Operators)
{
    Michka::Quaternion a(5.0f, -10.0f, 15.0f, 1.0f);
    const Michka::Quaternion b(-5.0f, 10.0f, -15.0f, -1.0f);

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

    ASSERT_EQ(a + Michka::Quaternion(2.0f, 3.0f, 4.0f, 1.0f), Michka::Quaternion(7.0f, -7.0f, 19.0f, 2.0f));
    ASSERT_EQ(a - Michka::Quaternion(2.0f, 3.0f, 4.0f, 1.0f), Michka::Quaternion(3.0f, -13.0f, 11.0f, 0.0f));

    ASSERT_EQ(a * 2.0f, Michka::Quaternion(10, -20.0f, 30.0f, 2.0f));
    ASSERT_EQ(2.0f * a, Michka::Quaternion(10, -20.0f, 30.0f, 2.0f));
    ASSERT_EQ(a / 2.0f, Michka::Quaternion(2.5f, -5.0f, 7.5f, 0.5f));
    ASSERT_EQ(1.0f / a, Michka::Quaternion(1.0f/5.0f, -1.0f/10.0f, 1.0f/15.0f, 1.0f));

    a = Michka::Quaternion(0.0f, 90.0f, 0.0f);
    ASSERT_EQ(a * Michka::Quaternion(0.0f, 0.0f, 0.0f), Michka::Quaternion(-90.0f, 0.0f, 0.0f));
    ASSERT_EQ(Michka::Quaternion(-90.0f, 0.0f, 0.0f) / Michka::Quaternion(0.0f, 0.0f, 0.0f).getInversed(), a);

    ASSERT_EQ(Michka::Quaternion::identity, Michka::Quaternion::identity);
    ASSERT_NE(Michka::Quaternion::identity, Michka::Quaternion::zero);
}

TEST(QuaternionTest, Slerp)
{
    Michka::Quaternion a(0.0f, 0.0f, 0.0f);
    Michka::Quaternion b(0.0f, 60.0f, 0.0f);
    Michka::Vector3 test = Michka::Quaternion::slerp(a, b, 1.0f).toEulerAngels();
    ASSERT_EQ(Michka::Quaternion::slerp(a, b, 0.0f), a);
    ASSERT_EQ(Michka::Quaternion::slerp(a, b, 1.0f), b);
    ASSERT_EQ(Michka::Quaternion::slerp(a, b, 0.5f), Michka::Quaternion(0.0f, 30.0f, 0.0f));
    ASSERT_EQ(Michka::Quaternion::slerp(a, a, 0.0f), a);
    ASSERT_EQ(Michka::Quaternion::slerp(a, a, 1.0f), a);

    b.set(0.0f, 270.0f, 0.0f);
    ASSERT_EQ(Michka::Quaternion::slerp(a, b, 0.5f), Michka::Quaternion(0.0f, -45.0f, 0.0f));

    b.set(0.0f, -30.0f, 0.0f);
    ASSERT_EQ(Michka::Quaternion::slerp(a, b, 0.5f), Michka::Quaternion(0.0f, -15.0f, 0.0f));
}

TEST(QuaternionTest, ToAxes)
{
    Michka::Vector3 forward, up, right;
    {
        Michka::Quaternion q(Michka::Vector3::right, Michka::Vector3::up, Michka::Vector3::forward);
        q.toAxes(right, up, forward);
        ASSERT_EQ(forward, Michka::Vector3::forward);
        ASSERT_EQ(right, Michka::Vector3::right);
        ASSERT_EQ(up, Michka::Vector3::up);
    }
    {
        Michka::Quaternion q(Michka::Vector3::left, Michka::Vector3::up, Michka::Vector3::back);
        q.toAxes(right, up, forward);
        ASSERT_EQ(forward, Michka::Vector3::back);
        ASSERT_EQ(right, Michka::Vector3::left);
        ASSERT_EQ(up, Michka::Vector3::up);
    }
}

TEST(QuaternionTest, ToAxisAngle)
{
    f32 angle;
    Michka::Vector3 axis;
    {
        Michka::Quaternion q(Michka::Vector3::up, 90.0f);
        q.toAxisAngle(axis, angle);
        ASSERT_EQ(axis, Michka::Vector3::up);
        ASSERT_FLOAT_EQ(angle, 90.0f);
    }
    {
        Michka::Quaternion q(Michka::Vector3::right, 45.0f);
        q.toAxisAngle(axis, angle);
        ASSERT_EQ(axis, Michka::Vector3::right);
        ASSERT_FLOAT_EQ(angle, 45.0f);
    }
    {
        Michka::Quaternion q(Michka::Vector3::back, 60.0f);
        q.toAxisAngle(axis, angle);
        ASSERT_EQ(axis, Michka::Vector3::back);
        ASSERT_FLOAT_EQ(angle, 60.0f);
    }
}

TEST(QuaternionTest, ToEulerAngels)
{
    Michka::Quaternion a(0.0f, 45.0f, 0.0f);
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(0.0f, 45.0f, 0.0f));
    a.set(Michka::Vector3(60.0f, 45.0f, 0.0f));
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(60.0f, 45.0f, 0.0f));
    a.set(Michka::Vector3(135.0f, 0.0f, 90.0f));
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(135.0f, 0.0f, 90.0f));
    a.set(Michka::Vector3(0.0f, 0.0f, 180.0f));
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(0.0f, 0.0f, 180.0f));
    a.set(Michka::Vector3(0.0f, -180.0f, 0.0f));
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(180.0f, 0.0f, 180.0f));
    a.set(Michka::Vector3(180.0f, 0.0f, 0.0f));
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(180.0f, 0.0f, 0.0f));
    a.set(Michka::Vector3(0.0f, 90.0f, 0.0f));
    ASSERT_EQ(a.toEulerAngels(), Michka::Vector3(0.0f, 90.0f, 0.0f));
}
