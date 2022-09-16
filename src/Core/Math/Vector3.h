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

#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "Core/Helpers.h"

namespace Michka
{
    class Matrix;
    class Matrix3;
    class Vector4;

    class MICHKA_API Vector3
    {
        MICHKA_CLASS();
    public:
        FORCE_INLINE Vector3();
        FORCE_INLINE Vector3(const f32& _x, const f32& _y, const f32& _z);
        FORCE_INLINE Vector3(const Vector3& _other);

        /**
         * @brief Angel between two directions.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 angle(const Vector3& _a, const Vector3& _b);

        /**
         * @brief Get cross product of two directions.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static Vector3 crossProduct(const Vector3& _a, const Vector3& _b);

        /**
         * @brief Distance between two points.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 distance(const Vector3& _a, const Vector3& _b);

        /**
         * @brief Get dot product of two points.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 dotProduct(const Vector3& _a, const Vector3& _b);

        /**
         * @brief Get the angel between this vector direction and another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getAngleFrom(const Vector3& _other) const;

        /**
         * @brief Get cross product of this vector and another vector.
         *
         * @param _other
         */
        FORCE_INLINE Vector3 getCrossProduct(const Vector3& _other) const;

        /**
         * @brief Get the distance from this vector to another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getDistanceFrom(const Vector3& _other) const;

        /**
         * @brief Get dot product between this vector and another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getDotProduct(const Vector3& _other) const;

        /**
         * @brief Get the length of vector.
         */
        FORCE_INLINE f32 getLength() const;

        /**
         * @brief Get the normalized copy of this vector.
         */
        FORCE_INLINE Vector3 getNormalized() const;

        /**
         * @brief Get the reflected copy of this vector.
         */
        FORCE_INLINE Vector3 getReflected(const Vector3& _normal) const;

        /**
         * @brief Get the sqaured length of vector.
         */
        FORCE_INLINE f32 getSqauredLength() const;

        /**
         * @brief Check vector can be normalize.
         */
        FORCE_INLINE bool isNormalizable() const;

        /**
         * @brief Check vector is normalized.
         */
        FORCE_INLINE bool isNormalized() const;

        /**
         * @brief Get linear interpolation between two vector.
         *
         * @param _a
         * @param _b
         * @param _position
         */
        FORCE_INLINE static Vector3 lerp(const Vector3& _a, const Vector3& _b, const f32& _position);

        /**
         * @brief Normalize vector.
         *
         * @return false if vector is not normalizable.
         */
        FORCE_INLINE bool normalize();

        /**
         * @brief Reflect a vector by a normal vector.
         *
         * @param _normal
         * @return Self
         */
        FORCE_INLINE Vector3& reflect(const Vector3& _normal);

        /**
         * @brief Set Vector coordinates.
         *
         * @param _x
         * @param _y
         * @param _z
         * @return Self
         */
        FORCE_INLINE Vector3& set(const f32& _x, const f32& _y, const f32& _z);

        /**
         * @brief Set X coordinate.
         *
         * @param _x
         * @return Self
         */
        FORCE_INLINE Vector3& setX(const f32& _x);

        /**
         * @brief Set Y coordinate.
         *
         * @param _y
         * @return Self
         */
        FORCE_INLINE Vector3& setY(const f32& _y);

        /**
         * @brief Set Z coordinate.
         *
         * @param _z
         * @return Self
         */
        FORCE_INLINE Vector3& setZ(const f32& _z);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Vector3& operator = (const Vector3& _other);

        FORCE_INLINE bool operator == (const Vector3& _other) const;
        FORCE_INLINE bool operator != (const Vector3& _other) const;

        FORCE_INLINE Vector3 operator + () const;
        FORCE_INLINE Vector3 operator - () const;

        FORCE_INLINE f32& operator [] (const u8& _d);
        FORCE_INLINE f32 operator [] (const u8& _d) const;

        FORCE_INLINE Vector3 operator + (const Vector3& _other) const;
        FORCE_INLINE Vector3& operator += (const Vector3& _other);
        FORCE_INLINE Vector3 operator + (const f32& _scaler) const;
        FORCE_INLINE Vector3& operator += (const f32& _scaler);
        friend FORCE_INLINE Vector3 operator + (const f32& _a, const Vector3& _b);

        FORCE_INLINE Vector3 operator - (const Vector3& _other) const;
        FORCE_INLINE Vector3& operator -= (const Vector3& _other);
        FORCE_INLINE Vector3 operator - (const f32& _scaler) const;
        FORCE_INLINE Vector3& operator -= (const f32& _scaler);
        friend FORCE_INLINE Vector3 operator - (const f32& _a, const Vector3& _b);

        // Note: These operators are NOT Cross/Dot product.
        FORCE_INLINE Vector3 operator * (const Vector3& _other) const;
        FORCE_INLINE Vector3& operator *= (const Vector3& _other);
        FORCE_INLINE Vector3 operator * (const f32& _scaler) const;
        FORCE_INLINE Vector3& operator *= (const f32& _scaler);
        friend FORCE_INLINE Vector3 operator * (const f32& _a, const Vector3& _b);
        Vector3 operator * (const Matrix3& _other) const;
        Vector3& operator *= (const Matrix3& _other);
        // Will act to the matrix like a 3x4 matrix.
        Vector3 operator * (const Matrix& _other) const;
        Vector3& operator *= (const Matrix& _other);

        FORCE_INLINE Vector3 operator / (const Vector3& _other) const;
        FORCE_INLINE Vector3& operator /= (const Vector3& _other);
        FORCE_INLINE Vector3 operator / (const f32& _scaler) const;
        FORCE_INLINE Vector3& operator /= (const f32& _scaler);
        friend FORCE_INLINE Vector3 operator / (const f32& _a, const Vector3& _b);

        operator Vector4 () const;

    public:
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 left;
        static const Vector3 right;
        static const Vector3 forward;
        static const Vector3 back;
        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 infinity;
        static const Vector3 nan;

    public:
        union
        {
            struct
            {
                f32 x;
                f32 y;
                f32 z;
            };
            struct
            {
                f32 r;
                f32 g;
                f32 b;
            };
            struct
            {
                f32 red;
                f32 green;
                f32 blue;
            };
            f32 asArray[3];
        };
    };
}

#include "Vector3.inl"

#endif // __VECTOR3_H__
