// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
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

#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "Core/Defines.h"

namespace Michka
{
    class Vector3;
    class Vector4;

    class MICHKA_API Vector2
    {
    public:
        FORCE_INLINE Vector2();
        FORCE_INLINE Vector2(const f32& _x, const f32& _y);
        FORCE_INLINE Vector2(const Vector2& _other);

        /**
         * @brief Angel between two directions.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 angle(const Vector2& _a, const Vector2& _b);

        /**
         * @brief Distance between two points.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 distance(const Vector2& _a, const Vector2& _b);

        /**
         * @brief Get dot product of two points.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 dotProduct(const Vector2& _a, const Vector2& _b);

        /**
         * @brief Get the angel between this vector direction and another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getAngleFrom(const Vector2& _other) const;

        /**
         * @brief Get the distance from this vector to another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getDistanceFrom(const Vector2& _other) const;

        /**
         * @brief Get dot product between this vector and another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getDotProduct(const Vector2& _other) const;

        /**
         * @brief Get the length of vector.
         */
        FORCE_INLINE f32 getLength() const;

        /**
         * @brief Get the normalized copy of this vector.
         */
        FORCE_INLINE Vector2 getNormalized() const;

        /**
         * @brief Get the reflected copy of this vector.
         */
        FORCE_INLINE Vector2 getReflected(const Vector2& _normal) const;

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
        FORCE_INLINE Vector2& reflect(const Vector2& _normal);

        /**
         * @brief Set Vector coordinates.
         *
         * @param _x
         * @param _y
         * @return Self
         */
        FORCE_INLINE Vector2& set(const f32& _x, const f32& _y);

        /**
         * @brief Set X coordinate.
         *
         * @param _x
         * @return Self
         */
        FORCE_INLINE Vector2& setX(const f32& _x);

        /**
         * @brief Set Y coordinate.
         *
         * @param _y
         * @return Self
         */
        FORCE_INLINE Vector2& setY(const f32& _y);

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Vector2& operator = (const Vector2& _other);

        FORCE_INLINE bool operator == (const Vector2& _other) const;
        FORCE_INLINE bool operator != (const Vector2& _other) const;

        FORCE_INLINE Vector2 operator + () const;
        FORCE_INLINE Vector2 operator - () const;

        FORCE_INLINE f32& operator [] (const u8& _d);
        FORCE_INLINE f32 operator [] (const u8& _d) const;

        FORCE_INLINE Vector2 operator + (const Vector2& _other) const;
        FORCE_INLINE Vector2& operator += (const Vector2& _other);
        FORCE_INLINE Vector2 operator + (const f32& _scaler) const;
        FORCE_INLINE Vector2& operator += (const f32& _scaler);
        friend FORCE_INLINE Vector2 operator + (const f32& _a, const Vector2& _b);

        FORCE_INLINE Vector2 operator - (const Vector2& _other) const;
        FORCE_INLINE Vector2& operator -= (const Vector2& _other);
        FORCE_INLINE Vector2 operator - (const f32& _scaler) const;
        FORCE_INLINE Vector2& operator -= (const f32& _scaler);
        friend FORCE_INLINE Vector2 operator - (const f32& _a, const Vector2& _b);

        // Note: These operators are NOT Cross/Dot  product.
        FORCE_INLINE Vector2 operator * (const Vector2& _other) const;
        FORCE_INLINE Vector2& operator *= (const Vector2& _other);
        FORCE_INLINE Vector2 operator * (const f32& _scaler) const;
        FORCE_INLINE Vector2& operator *= (const f32& _scaler);
        friend FORCE_INLINE Vector2 operator * (const f32& _a, const Vector2& _b);

        FORCE_INLINE Vector2 operator / (const Vector2& _other) const;
        FORCE_INLINE Vector2& operator /= (const Vector2& _other);
        FORCE_INLINE Vector2 operator / (const f32& _scaler) const;
        FORCE_INLINE Vector2& operator /= (const f32& _scaler);
        friend FORCE_INLINE Vector2 operator / (const f32& _a, const Vector2& _b);

        operator Vector3 () const;
        operator Vector4 () const;

    public:
        static const Vector2 up;
        static const Vector2 down;
        static const Vector2 left;
        static const Vector2 right;
        static const Vector2 forward;
        static const Vector2 back;
        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 infinity;

    public:
        union
        {
            struct
            {
                f32 x;
                f32 y;
            };
            f32 asArray[2];
        };
    };
}

#include "Vector2.inl"

#endif // __VECTOR2_H__
