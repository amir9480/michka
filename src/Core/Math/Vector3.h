#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "Core/Defines.h"

namespace Michka
{
    class MICHKA_API Vector3
    {
    public:
        FORCE_INLINE Vector3();
        FORCE_INLINE Vector3(const f32& _x, const f32& _y, const f32& _z);
        FORCE_INLINE Vector3(const Vector3& _other);

        /**
         * @brief Get the length of vector.
         */
        FORCE_INLINE f32 getLength() const;

        /**
         * @brief Get normalized copy of this vector.
         */
        FORCE_INLINE Vector3 getNormalized() const;

        /**
         * @brief Get the sqaured length of vector.
         */
        FORCE_INLINE f32 getSqauredLength() const;

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
         * @brief Set Vector coordinates.
         *
         * @param _x
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

        FORCE_INLINE Vector3& operator = (const Vector3& _other);

        FORCE_INLINE bool operator == (const Vector3& _other) const;
        FORCE_INLINE bool operator != (const Vector3& _other) const;

        FORCE_INLINE Vector3 operator + () const;
        FORCE_INLINE Vector3 operator - () const;

        FORCE_INLINE f32& operator [] (const u8& _d);
        FORCE_INLINE f32 operator [] (const u8& _d) const;

        // Note: These operators are NOT Cross/Dot  product.
        FORCE_INLINE Vector3 operator * (const Vector3& _other) const;
        FORCE_INLINE Vector3& operator *= (const Vector3& _other);
        FORCE_INLINE Vector3 operator * (const f32& _scaler) const;
        FORCE_INLINE Vector3& operator *= (const f32& _scaler);
        friend FORCE_INLINE Vector3 operator * (const f32& _a, const Vector3& _b);

        FORCE_INLINE Vector3 operator / (const Vector3& _other) const;
        FORCE_INLINE Vector3& operator /= (const Vector3& _other);
        FORCE_INLINE Vector3 operator / (const f32& _scaler) const;
        FORCE_INLINE Vector3& operator /= (const f32& _scaler);
        friend FORCE_INLINE Vector3 operator / (const f32& _a, const Vector3& _b);


    public:
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 left;
        static const Vector3 right;
        static const Vector3 forward;
        static const Vector3 back;
        static const Vector3 zero;
        static const Vector3 one;

    public:
        f32 x = 0.0f;
        f32 y = 0.0f;
        f32 z = 0.0f;
    };
}

#include "Vector3.inl"

#endif // __VECTOR3_H__
