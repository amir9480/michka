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

#include "Michka/Core/Math/Matrix.h"
#include "Michka/Core/Container/String.h"
#include "Michka/Core/Helpers.h"
#include "Michka/Core/Math/Vector3.h"
#include "Michka/Core/Math/Matrix3.h"

namespace Michka
{
    const Matrix Matrix::identity = Matrix();
    const Matrix Matrix::zero = Matrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    const Matrix Matrix::one = Matrix(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    Matrix::Matrix() :
        m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f),
        m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
        m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
        m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
    {
        //
    }

    Matrix::Matrix(const f32 _array[16]) :
        m11(_array[0]),  m12(_array[1]),  m13(_array[2]),  m14(_array[3]),
        m21(_array[4]),  m22(_array[5]),  m23(_array[6]),  m24(_array[7]),
        m31(_array[8]),  m32(_array[9]),  m33(_array[10]), m34(_array[11]),
        m41(_array[12]), m42(_array[13]), m43(_array[14]), m44(_array[15])
    {
        //
    }

    Matrix::Matrix(const f32 _array[4][4]) :
        m11(_array[0][0]), m12(_array[0][1]), m13(_array[0][2]), m14(_array[0][3]),
        m21(_array[1][0]), m22(_array[1][1]), m23(_array[1][2]), m24(_array[1][3]),
        m31(_array[2][0]), m32(_array[2][1]), m33(_array[2][2]), m34(_array[2][3]),
        m41(_array[3][0]), m42(_array[3][1]), m43(_array[3][2]), m44(_array[3][3])
    {
        //
    }

    Matrix::Matrix(
        const f32& _11, const f32& _12, const f32& _13, const f32& _14,
        const f32& _21, const f32& _22, const f32& _23, const f32& _24,
        const f32& _31, const f32& _32, const f32& _33, const f32& _34,
        const f32& _41, const f32& _42, const f32& _43, const f32& _44
    ):
        m11(_11), m12(_12), m13(_13), m14(_14),
        m21(_21), m22(_22), m23(_23), m24(_24),
        m31(_31), m32(_32), m33(_33), m34(_34),
        m41(_41), m42(_42), m43(_43), m44(_44)
    {
        //
    }

    Matrix Matrix::createOrthgraphicProjection(const f32& _left, const f32& _right, const f32& _top, const f32& _bottom, const f32& _zNear, const f32& _zFar)
    {
        f32 oneByFarMinusNear = 1.0f / (_zFar - _zNear);
        return Matrix(
            2.0f/(_right -_left), 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f/(_top - _bottom), 0.0f, 0.0f,
            0.0f, 0.0f, oneByFarMinusNear, 0.0f,
            -(_right + _left) / (_right - _left), -(_top + _bottom) / (_top - _bottom), -_zNear * oneByFarMinusNear, 1.0f
        );
    }

    Matrix Matrix::createOrthgraphicProjection(const f32& _width, const f32& _height, const f32& _zNear, const f32& _zFar)
    {
        f32 oneByFarMinusNear = 1.0f / (_zFar - _zNear);
        return Matrix(
            2.0f/_width, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f/_height, 0.0f, 0.0f,
            0.0f, 0.0f, oneByFarMinusNear, 0.0f,
            0.0f, 0.0f, -_zNear * oneByFarMinusNear, 1.0f
        );
    }

    Matrix Matrix::createPerspectiveProjection(const f32& _fov, const f32& _aspectRatio, const f32& _zNear, const f32& _zFar)
    {
        f32 oneByTanFov = 1.0f / Math::tan(_fov * 0.5f);
        f32 oneByFarMinusNear = 1.0f / (_zFar - _zNear);
        return Matrix(
            oneByTanFov / _aspectRatio, 0.0f, 0.0f, 0.0f,
            0.0f, oneByTanFov, 0.0f, 0.0f,
            0.0f, 0.0f, _zFar * oneByFarMinusNear, 1.0f,
            0.0f, 0.0f, -(_zFar * _zNear) * oneByFarMinusNear, 0.0f
        );
    }

    Matrix Matrix::createRotationMatrixAxis(const Vector3& _axis, const f32& _angle)
    {
        // Adapted from : https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
        f32 cosAngle= Math::cos(-_angle);
        f32 sinAngle= Math::sin(-_angle);
        f32 oneMinusCosAngle = 1.0f - cosAngle;

        return Matrix(
            cosAngle + ((_axis.x * _axis.x) * oneMinusCosAngle),
            (_axis.x * _axis.y * (oneMinusCosAngle)) - (_axis.z * sinAngle),
            (_axis.x * _axis.z * (oneMinusCosAngle)) + (_axis.y * sinAngle),
            0.0f,

            (_axis.y *_axis.z * oneMinusCosAngle) + (_axis.z * sinAngle),
            cosAngle + ((_axis.y * _axis.y) * oneMinusCosAngle),
            (_axis.y *_axis.z * oneMinusCosAngle) - (_axis.x * sinAngle),
            0.0f,

            (_axis.z * _axis.x * oneMinusCosAngle) - (_axis.y * sinAngle),
            (_axis.z * _axis.y * oneMinusCosAngle) + (_axis.x * sinAngle),
            cosAngle + ((_axis.z * _axis.z) * oneMinusCosAngle),
            0.0f,

            0.0f,
            0.0f,
            0.0f,
            1.0f
        );
    }

    Matrix Matrix::createRotationMatrix(const f32& _pitch,const f32& _yaw, const f32& _roll)
    {
        Matrix out;
        out *= createRotationMatrixZ(_roll);
        out *= createRotationMatrixX(_pitch);
        out *= createRotationMatrixY(_yaw);

        return out;
    }

    Matrix Matrix::createRotationMatrixX(const f32& _angle)
    {
        f32 cosAngle= Math::cos(_angle);
        f32 sinAngle= Math::sin(_angle);
        return Matrix(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cosAngle, sinAngle, 0.0f,
            0.0f, -sinAngle, cosAngle, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix Matrix::createRotationMatrixY(const f32& _angle)
    {
        f32 cosAngle= Math::cos(_angle);
        f32 sinAngle= Math::sin(_angle);
        return Matrix(
            cosAngle, 0.0f, -sinAngle, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            sinAngle, 0.0f, cosAngle, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix Matrix::createRotationMatrixZ(const f32& _angle)
    {
        f32 cosAngle= Math::cos(_angle);
        f32 sinAngle= Math::sin(_angle);
        return Matrix(
            cosAngle, sinAngle, 0.0f, 0.0f,
            -sinAngle, cosAngle, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix Matrix::createScaleMatrix(const Vector3& _scale)
    {
        return Matrix(
            _scale.x, 0.0f, 0.0f, 0.0f,
            0.0f, _scale.y, 0.0f, 0.0f,
            0.0f, 0.0f, _scale.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix Matrix::createTranslationMatrix(const Vector3& _position)
    {
        return Matrix(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _position.x, _position.y, _position.z, 1.0f
        );
    }

    Matrix Matrix::createViewMatrix(const Vector3& _position, const Vector3& _forward, const Vector3& _up)
    {
        Vector3 axisZ = _forward.getNormalized();
        Vector3 axisX = Vector3::crossProduct(_up, axisZ).getNormalized();
        Vector3 axisY = Vector3::crossProduct(axisZ, axisX).getNormalized();

        return Matrix(
            axisX.x, axisY.x, axisZ.x, 0.0f,
            axisX.y, axisY.y, axisZ.y, 0.0f,
            axisX.z, axisY.z, axisZ.z, 0.0f,
            -Vector3::dotProduct(axisX,_position), -Vector3::dotProduct(axisY,_position), -Vector3::dotProduct(axisZ,_position), 1.0f
        );
    }

    f32 Matrix::getDeterminant() const
    {
        return m11 * (m22 * (m33*m44 - m34*m43) - m23 * (m32*m44 - m34*m42) + m24 * (m32*m43 - m33*m42)) -
               m12 * (m21 * (m33*m44 - m34*m43) - m23 * (m31*m44 - m34*m41) + m24 * (m31*m43 - m33*m41)) +
               m13 * (m21 * (m32*m44 - m34*m42) - m22 * (m31*m44 - m34*m41) + m24 * (m31*m42 - m32*m41)) -
               m14 * (m21 * (m32*m43 - m33*m42) - m22 * (m31*m43 - m33*m41) + m23 * (m31*m42 - m32*m41));
    }

    bool Matrix::inverse()
    {
        f32 determinant = getDeterminant();
        if (determinant == 0.0f)
        {
            return false;
        }

        f32 determinantInv = 1.0f / determinant;
        Matrix inversed(
            determinantInv * (m22*m33*m44 + m23*m34*m42 + m24*m32*m43 - m22*m34*m43 - m23*m32*m44 - m24*m33*m42),
            determinantInv * (m12*m34*m43 + m13*m32*m44 + m14*m33*m42 - m12*m33*m44 - m13*m34*m42 - m14*m32*m43),
            determinantInv * (m12*m23*m44 + m13*m24*m42 + m14*m22*m43 - m12*m24*m43 - m13*m22*m44 - m14*m23*m42),
            determinantInv * (m12*m24*m33 + m13*m22*m34 + m14*m23*m32 - m12*m23*m34 - m13*m24*m32 - m14*m22*m33),

            determinantInv * (m21*m34*m43 + m23*m31*m44 + m24*m33*m41 - m21*m33*m44 - m23*m34*m41 - m24*m31*m43),
            determinantInv * (m11*m33*m44 + m13*m34*m41 + m14*m31*m43 - m11*m34*m43 - m13*m31*m44 - m14*m33*m41),
            determinantInv * (m11*m24*m43 + m13*m21*m44 + m14*m23*m41 - m11*m23*m44 - m13*m24*m41 - m14*m21*m43),
            determinantInv * (m11*m23*m34 + m13*m24*m31 + m14*m21*m33 - m11*m24*m33 - m13*m21*m34 - m14*m23*m31),

            determinantInv * (m21*m32*m44 + m22*m34*m41 + m24*m31*m42 - m21*m34*m42 - m22*m31*m44 - m24*m32*m41),
            determinantInv * (m11*m34*m42 + m12*m31*m44 + m14*m32*m41 - m11*m32*m44 - m12*m34*m41 - m14*m31*m42),
            determinantInv * (m11*m22*m44 + m12*m24*m41 + m14*m21*m42 - m11*m24*m42 - m12*m21*m44 - m14*m22*m41),
            determinantInv * (m11*m24*m32 + m12*m21*m34 + m14*m22*m31 - m11*m22*m34 - m12*m24*m31 - m14*m21*m32),

            determinantInv * (m21*m33*m42 + m22*m31*m43 + m23*m32*m41 - m21*m32*m43 - m22*m33*m41 - m23*m31*m42),
            determinantInv * (m11*m32*m43 + m12*m33*m41 + m13*m31*m42 - m11*m33*m42 - m12*m31*m43 - m13*m32*m41),
            determinantInv * (m11*m23*m42 + m12*m21*m43 + m13*m22*m41 - m11*m22*m43 - m12*m23*m41 - m13*m21*m42),
            determinantInv * (m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31)
        );
        *this = inversed;

        return true;
    }

    String Matrix::toString() const
    {
        return String("Matrix(\n") +
            String::number(m11) + ", " + String::number(m12) + ", " + String::number(m13) + ", " + String::number(m14) + ",\n" +
            String::number(m21) + ", " + String::number(m22) + ", " + String::number(m23) + ", " + String::number(m24) + ",\n" +
            String::number(m31) + ", " + String::number(m32) + ", " + String::number(m33) + ", " + String::number(m34) + ",\n" +
            String::number(m41) + ", " + String::number(m42) + ", " + String::number(m43) + ", " + String::number(m44) + "\n)";
    }

    Matrix& Matrix::transpose()
    {
        swap(m12, m21);
        swap(m13, m31);
        swap(m14, m41);
        swap(m23, m32);
        swap(m24, m42);
        swap(m43, m34);

        return *this;
    }


    bool Matrix::operator == (const Matrix& _other) const
    {
        return
        Math::equals(m11, _other.m11) && Math::equals(m12, _other.m12) && Math::equals(m13, _other.m13) && Math::equals(m14, _other.m14) &&
        Math::equals(m21, _other.m21) && Math::equals(m22, _other.m22) && Math::equals(m23, _other.m23) && Math::equals(m24, _other.m24) &&
        Math::equals(m31, _other.m31) && Math::equals(m32, _other.m32) && Math::equals(m33, _other.m33) && Math::equals(m34, _other.m34) &&
        Math::equals(m41, _other.m41) && Math::equals(m42, _other.m42) && Math::equals(m43, _other.m43) && Math::equals(m44, _other.m44);
    }

    Matrix Matrix::operator + (const Matrix& _other) const
    {
        return Matrix(
            m11 + _other.m11, m12 + _other.m12, m13 + _other.m13, m14 + _other.m14,
            m21 + _other.m21, m22 + _other.m22, m23 + _other.m23, m24 + _other.m24,
            m31 + _other.m31, m32 + _other.m32, m33 + _other.m33, m34 + _other.m34,
            m41 + _other.m41, m42 + _other.m42, m43 + _other.m43, m44 + _other.m44
        );
    }

    Matrix Matrix::operator - (const Matrix& _other) const
    {
        return Matrix(
            m11 - _other.m11, m12 - _other.m12, m13 - _other.m13, m14 - _other.m14,
            m21 - _other.m21, m22 - _other.m22, m23 - _other.m23, m24 - _other.m24,
            m31 - _other.m31, m32 - _other.m32, m33 - _other.m33, m34 - _other.m34,
            m41 - _other.m41, m42 - _other.m42, m43 - _other.m43, m44 - _other.m44
        );
    }

    Matrix Matrix::operator - () const
    {
        return Matrix(
            -m11, -m12, -m13, -m14,
            -m21, -m22, -m23, -m24,
            -m31, -m32, -m33, -m34,
            -m41, -m42, -m43, -m44
        );
    }


    Matrix Matrix::operator * (const f32& _scaler) const
    {
        return Matrix(
            m11 * _scaler, m12 * _scaler, m13 * _scaler, m14 * _scaler,
            m21 * _scaler, m22 * _scaler, m23 * _scaler, m24 * _scaler,
            m31 * _scaler, m32 * _scaler, m33 * _scaler, m34 * _scaler,
            m41 * _scaler, m42 * _scaler, m43 * _scaler, m44 * _scaler
        );
    }

    Matrix Matrix::operator * (const Matrix& _other) const
    {
        return Matrix(
            m11*_other.m11 + m12*_other.m21 + m13*_other.m31 + m14*_other.m41,
            m11*_other.m12 + m12*_other.m22 + m13*_other.m32 + m14*_other.m42,
            m11*_other.m13 + m12*_other.m23 + m13*_other.m33 + m14*_other.m43,
            m11*_other.m14 + m12*_other.m24 + m13*_other.m34 + m14*_other.m44,

            m21*_other.m11 + m22*_other.m21 + m23*_other.m31 + m24*_other.m41,
            m21*_other.m12 + m22*_other.m22 + m23*_other.m32 + m24*_other.m42,
            m21*_other.m13 + m22*_other.m23 + m23*_other.m33 + m24*_other.m43,
            m21*_other.m14 + m22*_other.m24 + m23*_other.m34 + m24*_other.m44,

            m31*_other.m11 + m32*_other.m21 + m33*_other.m31 + m34*_other.m41,
            m31*_other.m12 + m32*_other.m22 + m33*_other.m32 + m34*_other.m42,
            m31*_other.m13 + m32*_other.m23 + m33*_other.m33 + m34*_other.m43,
            m31*_other.m14 + m32*_other.m24 + m33*_other.m34 + m34*_other.m44,

            m41*_other.m11 + m42*_other.m21 + m43*_other.m31 + m44*_other.m41,
            m41*_other.m12 + m42*_other.m22 + m43*_other.m32 + m44*_other.m42,
            m41*_other.m13 + m42*_other.m23 + m43*_other.m33 + m44*_other.m43,
            m41*_other.m14 + m42*_other.m24 + m43*_other.m34 + m44*_other.m44
        );
    }

    Matrix::operator Matrix3 () const
    {
        return Matrix3(
            m11, m12, m13,
            m21, m22, m23,
            m31, m32, m33
        );
    }
}
