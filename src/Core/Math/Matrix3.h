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

#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include "Core/Defines.h"
#include "Core/Reflection/ReflectionClass.h"

namespace Michka
{
    class Vector3;
    class Matrix;

    /**
     * @brief A 3x3 row major matrix.
     *
     * m11 m12 m13
     * m21 m22 m23
     * m31 m32 m33
     */
    class MICHKA_API Matrix3
    {
        MICHKA_CLASS(Matrix3);
    public:
        Matrix3();
        Matrix3(const f32 _array[9]);
        Matrix3(const f32 _array[3][3]);
        Matrix3(
            const f32& _11, const f32& _12, const f32& _13,
            const f32& _21, const f32& _22, const f32& _23,
            const f32& _31, const f32& _32, const f32& _33
        );
        FORCE_INLINE Matrix3(const Matrix3& _other);

        /**
         * @brief Create a Rotation Matrix based on the axis and the angle.
         *
         * @param _axis  Should be normalized axis
         * @param _angle
         */
        static Matrix3 createRotationMatrixAxis(const Vector3& _axis, const f32& _angle);

        /**
         * @brief Create a Rotation Matrix.
         *
         * @param _pitch
         * @param _yaw
         * @param _roll
         */
        static Matrix3 createRotationMatrix(const f32& _pitch,const f32& _yaw, const f32& _roll);

        /**
         * @brief Create a Rotation Matrix just for X.
         *
         * @param _angle
         */
        static Matrix3 createRotationMatrixX(const f32& _angle);

        /**
         * @brief Create a Rotation Matrix just for Y.
         *
         * @param _angle
         */
        static Matrix3 createRotationMatrixY(const f32& _angle);

        /**
         * @brief Create a Rotation Matrix just for Z.
         *
         * @param _angle
         */
        static Matrix3 createRotationMatrixZ(const f32& _angle);

        /**
         * @brief Create a Scale Matrix.
         *
         * @param _scale
         */
        static Matrix3 createScaleMatrix(const Vector3& _scale);

        /**
         * @brief Create a Translation Matrix.
         *
         * @param _position
         */
        static Matrix3 createTranslationMatrix(const Vector3& _position);

        /**
         * @brief Get the Determinant of the matrix.
         */
        f32 getDeterminant() const;

        /**
         * @brief Get the inversed copy of this matrix.
         */
        FORCE_INLINE Matrix3 getInversed() const;

        /**
         * @brief Get the inverse transposed copy of this matrix.
         */
        FORCE_INLINE Matrix3 getInverseTransposed() const;

        /**
         * @brief Get the transposed copy of this matrix.
         */
        FORCE_INLINE Matrix3 getTransposed() const;

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
        Matrix3& transpose();

        FORCE_INLINE Matrix3& operator = (const Matrix3& _other);

        FORCE_INLINE f32& operator () (const u32& _i);
        FORCE_INLINE f32 operator () (const u32& _i) const;
        FORCE_INLINE f32& operator () (const u32& _i, const u32& _j);
        FORCE_INLINE f32 operator () (const u32& _i, const u32& _j) const;
        FORCE_INLINE f32* operator [] (const u32& _i);
        FORCE_INLINE const f32* operator [] (const u32& _i) const;

        bool operator == (const Matrix3& _other) const;
        FORCE_INLINE bool operator != (const Matrix3& _other) const;

        Matrix3 operator - () const;
        FORCE_INLINE Matrix3 operator + () const;

        Matrix3 operator + (const Matrix3& _other) const;
        Matrix3 operator - (const Matrix3& _other) const;
        Matrix3 operator * (const f32& _scaler) const;
        Matrix3 operator * (const Matrix3& _other) const;

        FORCE_INLINE Matrix3& operator += (const Matrix3& _other);
        FORCE_INLINE Matrix3& operator -= (const Matrix3& _other);
        FORCE_INLINE Matrix3& operator *= (const f32& _scaler);
        FORCE_INLINE Matrix3& operator *= (const Matrix3& _other);

        operator Matrix () const;

    public:
        static const Matrix3 identity;
        static const Matrix3 zero;
        static const Matrix3 one;

    public:
        union
        {
            struct
            {
                f32 m11, m12, m13;
                f32 m21, m22, m23;
                f32 m31, m32, m33;
            };
            f32 m[9];
            f32 m2D[3][3];
        };
    };
}

#include "Matrix3.inl"

#endif // __MATRIX3_H__
