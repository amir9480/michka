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

#include "Matrix3.h"
#include "Core/Container/String.h"
#include "Core/Helpers.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"

namespace Michka
{
    const Matrix3 Matrix3::identity = Matrix3();
    const Matrix3 Matrix3::zero = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    const Matrix3 Matrix3::one = Matrix3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    Matrix3::Matrix3() :
        m11(1.0f), m12(0.0f), m13(0.0f),
        m21(0.0f), m22(1.0f), m23(0.0f),
        m31(0.0f), m32(0.0f), m33(1.0f)
    {
        //
    }

    Matrix3::Matrix3(const f32 _array[9]) :
        m11(_array[0]),  m12(_array[1]),  m13(_array[2]),
        m21(_array[3]),  m22(_array[4]),  m23(_array[5]),
        m31(_array[6]),  m32(_array[7]),  m33(_array[8])
    {
        //
    }

    Matrix3::Matrix3(const f32 _array[3][3]) :
        m11(_array[0][0]), m12(_array[0][1]), m13(_array[0][2]),
        m21(_array[1][0]), m22(_array[1][1]), m23(_array[1][2]),
        m31(_array[2][0]), m32(_array[2][1]), m33(_array[2][2])
    {
        //
    }

    Matrix3::Matrix3(
        const f32& _11, const f32& _12, const f32& _13,
        const f32& _21, const f32& _22, const f32& _23,
        const f32& _31, const f32& _32, const f32& _33
    ) :
        m11(_11), m12(_12), m13(_13),
        m21(_21), m22(_22), m23(_23),
        m31(_31), m32(_32), m33(_33)
    {
        //
    }

    Matrix3 Matrix3::createRotationMatrixAxis(const Vector3& _axis, const f32& _angle)
    {
        // Adapted from : https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
        f32 cosAngle= Math::cos(-_angle);
        f32 sinAngle= Math::sin(-_angle);
        f32 oneMinusCosAngle = 1.0f - cosAngle;

        return Matrix3(
            cosAngle + ((_axis.x * _axis.x) * oneMinusCosAngle),
            (_axis.x * _axis.y * (oneMinusCosAngle)) - (_axis.z * sinAngle),
            (_axis.x * _axis.z * (oneMinusCosAngle)) + (_axis.y * sinAngle),

            (_axis.y *_axis.z * oneMinusCosAngle) + (_axis.z * sinAngle),
            cosAngle + ((_axis.y * _axis.y) * oneMinusCosAngle),
            (_axis.y *_axis.z * oneMinusCosAngle) - (_axis.x * sinAngle),

            (_axis.z * _axis.x * oneMinusCosAngle) - (_axis.y * sinAngle),
            (_axis.z * _axis.y * oneMinusCosAngle) + (_axis.x * sinAngle),
            cosAngle + ((_axis.z * _axis.z) * oneMinusCosAngle)
        );
    }

    Matrix3 Matrix3::createRotationMatrix(const f32& _pitch,const f32& _yaw, const f32& _roll)
    {
        Matrix3 out;
        out *= createRotationMatrixZ(_roll);
        out *= createRotationMatrixX(_pitch);
        out *= createRotationMatrixY(_yaw);

        return out;
    }

    Matrix3 Matrix3::createRotationMatrixX(const f32& _angle)
    {
        f32 cosAngle= Math::cos(_angle);
        f32 sinAngle= Math::sin(_angle);
        return Matrix3(
            1.0f, 0.0f, 0.0f,
            0.0f, cosAngle, sinAngle,
            0.0f, -sinAngle, cosAngle
        );
    }

    Matrix3 Matrix3::createRotationMatrixY(const f32& _angle)
    {
        f32 cosAngle= Math::cos(_angle);
        f32 sinAngle= Math::sin(_angle);
        return Matrix3(
            cosAngle, 0.0f, -sinAngle,
            0.0f, 1.0f, 0.0f,
            sinAngle, 0.0f, cosAngle
        );
    }

    Matrix3 Matrix3::createRotationMatrixZ(const f32& _angle)
    {
        f32 cosAngle= Math::cos(_angle);
        f32 sinAngle= Math::sin(_angle);
        return Matrix3(
            cosAngle, sinAngle, 0.0f,
            -sinAngle, cosAngle, 0.0f,
            0.0f, 0.0f, 1.0f
        );
    }

    Matrix3 Matrix3::createScaleMatrix(const Vector3& _scale)
    {
        return Matrix3(
            _scale.x, 0.0f, 0.0f,
            0.0f, _scale.y, 0.0f,
            0.0f, 0.0f, _scale.z
        );
    }

    f32 Matrix3::getDeterminant() const
    {
        return m11 * (m22*m33 - m23*m32) - m12 * (m21*m33 - m23*m31) + m13 * (m21*m32 - m22*m31);
    }

    bool Matrix3::inverse()
    {
        f32 determinant = getDeterminant();
        if (determinant == 0.0f)
        {
            return false;
        }

        f32 determinantInv = 1.0f / determinant;
        Matrix3 inversed(
            determinantInv * (m22*m33 - m32*m23),
            determinantInv * (m13*m32 - m12*m33),
            determinantInv * (m12*m23 - m13*m22),

            determinantInv * (m23*m31 - m21*m33),
            determinantInv * (m11*m33 - m13*m31),
            determinantInv * (m21*m13 - m11*m23),

            determinantInv * (m21*m32 - m31*m22),
            determinantInv * (m31*m12 - m11*m32),
            determinantInv * (m11*m22 - m21*m12)
        );

        *this = inversed;

        return true;
    }

    String Matrix3::toString() const
    {
        return String("Matrix3(\n") +
            String::number(m11) + ", " + String::number(m12) + ", " + String::number(m13) + ",\n" +
            String::number(m21) + ", " + String::number(m22) + ", " + String::number(m23) + ",\n" +
            String::number(m31) + ", " + String::number(m32) + ", " + String::number(m33) + "\n)";
    }

    Matrix3& Matrix3::transpose()
    {
        swap(m12, m21);
        swap(m13, m31);
        swap(m23, m32);

        return *this;
    }


    bool Matrix3::operator == (const Matrix3& _other) const
    {
        return
        Math::equals(m11, _other.m11) && Math::equals(m12, _other.m12) && Math::equals(m13, _other.m13) &&
        Math::equals(m21, _other.m21) && Math::equals(m22, _other.m22) && Math::equals(m23, _other.m23) &&
        Math::equals(m31, _other.m31) && Math::equals(m32, _other.m32) && Math::equals(m33, _other.m33);
    }

    Matrix3 Matrix3::operator + (const Matrix3& _other) const
    {
        return Matrix3(
            m11 + _other.m11, m12 + _other.m12, m13 + _other.m13,
            m21 + _other.m21, m22 + _other.m22, m23 + _other.m23,
            m31 + _other.m31, m32 + _other.m32, m33 + _other.m33
        );
    }

    Matrix3 Matrix3::operator - (const Matrix3& _other) const
    {
        return Matrix3(
            m11 - _other.m11, m12 - _other.m12, m13 - _other.m13,
            m21 - _other.m21, m22 - _other.m22, m23 - _other.m23,
            m31 - _other.m31, m32 - _other.m32, m33 - _other.m33
        );
    }

    Matrix3 Matrix3::operator - () const
    {
        return Matrix3(
            -m11, -m12, -m13,
            -m21, -m22, -m23,
            -m31, -m32, -m33
        );
    }


    Matrix3 Matrix3::operator * (const f32& _scaler) const
    {
        return Matrix3(
            m11 * _scaler, m12 * _scaler, m13 * _scaler,
            m21 * _scaler, m22 * _scaler, m23 * _scaler,
            m31 * _scaler, m32 * _scaler, m33 * _scaler
        );
    }

    Matrix3 Matrix3::operator * (const Matrix3& _other) const
    {
        return Matrix3(
            m11*_other.m11 + m12*_other.m21 + m13*_other.m31,
            m11*_other.m12 + m12*_other.m22 + m13*_other.m32,
            m11*_other.m13 + m12*_other.m23 + m13*_other.m33,

            m21*_other.m11 + m22*_other.m21 + m23*_other.m31,
            m21*_other.m12 + m22*_other.m22 + m23*_other.m32,
            m21*_other.m13 + m22*_other.m23 + m23*_other.m33,

            m31*_other.m11 + m32*_other.m21 + m33*_other.m31,
            m31*_other.m12 + m32*_other.m22 + m33*_other.m32,
            m31*_other.m13 + m32*_other.m23 + m33*_other.m33
        );
    }

    Matrix3::operator Matrix () const
    {
        return Matrix(
            m11, m12, m13, 0.0f,
            m21, m22, m23, 0.0f,
            m31, m32, m33, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
}
