#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include "Core/Defines.h"

namespace Michka
{
    class MICHKA_API Vector4
    {
    public:
        FORCE_INLINE Vector4();
        FORCE_INLINE Vector4(const f32& _x, const f32& _y, const f32& _z, const f32& _w = 1.0f);
        FORCE_INLINE Vector4(const Vector4& _other);

        /**
         * @brief Get dot product of two points.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 dotProduct(const Vector4& _a, const Vector4& _b);

        /**
         * @brief Get dot product between this vector and another vector.
         *
         * @param _other
         */
        FORCE_INLINE f32 getDotProduct(const Vector4& _other) const;

        /**
         * @brief Get the length of vector.
         */
        FORCE_INLINE f32 getLength() const;

        /**
         * @brief Get the sqaured length of vector.
         */
        FORCE_INLINE f32 getSqauredLength() const;

        /**
         * @brief Set Vector coordinates.
         *
         * @param _x
         * @param _y
         * @param _z
         * @param _w
         * @return Self
         */
        FORCE_INLINE Vector4& set(const f32& _x, const f32& _y, const f32& _z, const f32& _w = 1.0f);

        /**
         * @brief Set X coordinate.
         *
         * @param _x
         * @return Self
         */
        FORCE_INLINE Vector4& setX(const f32& _x);

        /**
         * @brief Set Y coordinate.
         *
         * @param _y
         * @return Self
         */
        FORCE_INLINE Vector4& setY(const f32& _y);

        /**
         * @brief Set Z coordinate.
         *
         * @param _z
         * @return Self
         */
        FORCE_INLINE Vector4& setZ(const f32& _z);

        /**
         * @brief Set W coordinate.
         *
         * @param _z
         * @return Self
         */
        FORCE_INLINE Vector4& setW(const f32& _w);

        FORCE_INLINE Vector4& operator = (const Vector4& _other);

        FORCE_INLINE bool operator == (const Vector4& _other) const;
        FORCE_INLINE bool operator != (const Vector4& _other) const;

        FORCE_INLINE Vector4 operator + () const;
        FORCE_INLINE Vector4 operator - () const;

        FORCE_INLINE f32& operator [] (const u8& _d);
        FORCE_INLINE f32 operator [] (const u8& _d) const;

        FORCE_INLINE Vector4 operator + (const Vector4& _other) const;
        FORCE_INLINE Vector4& operator += (const Vector4& _other);
        FORCE_INLINE Vector4 operator + (const f32& _scaler) const;
        FORCE_INLINE Vector4& operator += (const f32& _scaler);
        friend FORCE_INLINE Vector4 operator + (const f32& _a, const Vector4& _b);

        FORCE_INLINE Vector4 operator - (const Vector4& _other) const;
        FORCE_INLINE Vector4& operator -= (const Vector4& _other);
        FORCE_INLINE Vector4 operator - (const f32& _scaler) const;
        FORCE_INLINE Vector4& operator -= (const f32& _scaler);
        friend FORCE_INLINE Vector4 operator - (const f32& _a, const Vector4& _b);

        // Note: These operators are NOT Cross/Dot  product.
        FORCE_INLINE Vector4 operator * (const Vector4& _other) const;
        FORCE_INLINE Vector4& operator *= (const Vector4& _other);
        FORCE_INLINE Vector4 operator * (const f32& _scaler) const;
        FORCE_INLINE Vector4& operator *= (const f32& _scaler);
        friend FORCE_INLINE Vector4 operator * (const f32& _a, const Vector4& _b);

        FORCE_INLINE Vector4 operator / (const Vector4& _other) const;
        FORCE_INLINE Vector4& operator /= (const Vector4& _other);
        FORCE_INLINE Vector4 operator / (const f32& _scaler) const;
        FORCE_INLINE Vector4& operator /= (const f32& _scaler);
        friend FORCE_INLINE Vector4 operator / (const f32& _a, const Vector4& _b);


    public:
        static const Vector4 up;
        static const Vector4 down;
        static const Vector4 left;
        static const Vector4 right;
        static const Vector4 forward;
        static const Vector4 back;
        static const Vector4 zero;
        static const Vector4 one;

    public:
        union
        {
            struct
            {
                f32 x;
                f32 y;
                f32 z;
                f32 w;
            };
            struct
            {
                f32 r;
                f32 g;
                f32 b;
                f32 a;
            };
            f32 asArray[4];
        };
    };
}

#include "Vector4.inl"

#endif // __VECTOR4_H__
