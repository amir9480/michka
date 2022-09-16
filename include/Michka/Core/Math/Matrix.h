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

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Michka/Core/Helpers.h"

namespace Michka
{
    class Vector3;
    class Matrix3;

    /**
     * @brief A 4x4 row major matrix.
     *
     * m11 m12 m13 m14
     * m21 m22 m23 m24
     * m31 m32 m33 m34
     * m41 m42 m43 m44
     */
    class MICHKA_API Matrix
    {
        MICHKA_CLASS();
    public:
        Matrix();
        Matrix(const f32 _array[16]);
        Matrix(const f32 _array[4][4]);
        Matrix(
            const f32& _11, const f32& _12, const f32& _13, const f32& _14,
            const f32& _21, const f32& _22, const f32& _23, const f32& _24,
            const f32& _31, const f32& _32, const f32& _33, const f32& _34,
            const f32& _41, const f32& _42, const f32& _43, const f32& _44
        );
        FORCE_INLINE Matrix(const Matrix& _other);

        /**
         * @brief Create a Orthgraphic Projection matrix.
         *
         * @param _left
         * @param _right
         * @param _top
         * @param _bottom
         * @param _zNear
         * @param _zFar
         */
        static Matrix createOrthgraphicProjection(const f32& _left, const f32& _right, const f32& _top, const f32& _bottom, const f32& _zNear, const f32& _zFar);

        /**
         * @brief Create a Orthgraphic Projection matrix.
         *
         * @param _width
         * @param _height
         * @param _zNear
         * @param _zFar
         */
        static Matrix createOrthgraphicProjection(const f32& _width, const f32& _height, const f32& _zNear, const f32& _zFar);

        /**
         * @brief Create a Perspective Projection matrix
         *
         * @param _fov
         * @param _aspectratio
         * @param _zNear
         * @param _zFar
         */
        static Matrix createPerspectiveProjection(const f32& _fov = 90.0f, const f32& _aspectRatio = 4.0f/3.0f, const f32& _zNear = 0.1f, const f32& _zFar = 1000.0f);

        /**
         * @brief Create a Rotation Matrix based on the axis and the angle.
         *
         * @param _axis  Should be normalized axis
         * @param _angle
         */
        static Matrix createRotationMatrixAxis(const Vector3& _axis, const f32& _angle);

        /**
         * @brief Create a Rotation Matrix.
         *
         * @param _pitch
         * @param _yaw
         * @param _roll
         */
        static Matrix createRotationMatrix(const f32& _pitch,const f32& _yaw, const f32& _roll);

        /**
         * @brief Create a Rotation Matrix just for X.
         *
         * @param _angle
         */
        static Matrix createRotationMatrixX(const f32& _angle);

        /**
         * @brief Create a Rotation Matrix just for Y.
         *
         * @param _angle
         */
        static Matrix createRotationMatrixY(const f32& _angle);

        /**
         * @brief Create a Rotation Matrix just for Z.
         *
         * @param _angle
         */
        static Matrix createRotationMatrixZ(const f32& _angle);

        /**
         * @brief Create a Scale Matrix.
         *
         * @param _scale
         */
        static Matrix createScaleMatrix(const Vector3& _scale);

        /**
         * @brief Create a Translation Matrix.
         *
         * @param _position
         */
        static Matrix createTranslationMatrix(const Vector3& _position);

        /**
         * @brief Create a View Matrix.
         *
         * @param _camerapos
         * @param _forward
         * @param _up
         */
        static Matrix createViewMatrix(const Vector3& _position, const Vector3& _forward, const Vector3& _up);

        /**
         * @brief Get the Determinant of the matrix.
         */
        f32 getDeterminant() const;

        /**
         * @brief Get the inversed copy of this matrix.
         */
        FORCE_INLINE Matrix getInversed() const;

        /**
         * @brief Get the inverse transposed copy of this matrix.
         */
        FORCE_INLINE Matrix getInverseTransposed() const;

        /**
         * @brief Get the transposed copy of this matrix.
         */
        FORCE_INLINE Matrix getTransposed() const;

        /**
         * @brief Inverse matrix.
         *
         * @return false if matrix can not inverse
         */
        bool inverse();

        /**
         * @brief Check matrix is identity.
         */
        FORCE_INLINE bool isIdentity() const;

        /**
         * @brief Check matrix can inverse.
         */
        FORCE_INLINE bool isInversable() const;

        /**
         * @brief Get value as string.
         */
        String toString() const;

        /**
         * @brief Transpose matrix.
         *
         * @return Self
         */
        Matrix& transpose();

        FORCE_INLINE Matrix& operator = (const Matrix& _other);

        FORCE_INLINE f32& operator () (const u32& _i);
        FORCE_INLINE f32 operator () (const u32& _i) const;
        FORCE_INLINE f32& operator () (const u32& _i, const u32& _j);
        FORCE_INLINE f32 operator () (const u32& _i, const u32& _j) const;
        FORCE_INLINE f32* operator [] (const u32& _i);
        FORCE_INLINE const f32* operator [] (const u32& _i) const;

        bool operator == (const Matrix& _other) const;
        FORCE_INLINE bool operator != (const Matrix& _other) const;

        Matrix operator - () const;
        FORCE_INLINE Matrix operator + () const;

        Matrix operator + (const Matrix& _other) const;
        Matrix operator - (const Matrix& _other) const;
        Matrix operator * (const f32& _scaler) const;
        Matrix operator * (const Matrix& _other) const;

        FORCE_INLINE Matrix& operator += (const Matrix& _other);
        FORCE_INLINE Matrix& operator -= (const Matrix& _other);
        FORCE_INLINE Matrix& operator *= (const f32& _scaler);
        FORCE_INLINE Matrix& operator *= (const Matrix& _other);

        operator Matrix3 () const;

    public:
        static const Matrix identity;
        static const Matrix zero;
        static const Matrix one;

    public:
        union
        {
            struct
            {
                f32 m11, m12, m13, m14;
                f32 m21, m22, m23, m24;
                f32 m31, m32, m33, m34;
                f32 m41, m42, m43, m44;
            };
            f32 m[16];
            f32 m2D[4][4];
        };
    };
}

#include "Core/Math/Matrix.inl"

#endif // __MATRIX_H__
