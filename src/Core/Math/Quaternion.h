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

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Core/Defines.h"
#include "Core/Reflection/ReflectionClass.h"
#include "MichkaGenerated/Core/Math/Quaternion.generated.h"

#define QUATERNION_EPSILON 0.0002f

namespace Michka
{
    class Matrix3;
    class Vector3;

    /**
     * @brief Quaternion class using for rotations
     */
    class MICHKA_API Quaternion
    {
        MICHKA_CLASS(Quaternion);
    public:
        FORCE_INLINE Quaternion();
        FORCE_INLINE Quaternion(const f32& _x, const f32& _y, const f32& _z, const f32& _w);
        Quaternion(const f32& _x, const f32& _y, const f32& _z);
        Quaternion(const Vector3& _euler);
        Quaternion(const Vector3& _axis, const f32& _angle);
        Quaternion(const Vector3& _from, const Vector3& _to);
        Quaternion(const Vector3& _right, const Vector3& _up, const Vector3& _forward);
        Quaternion(const Matrix3& _matrix);
        FORCE_INLINE Quaternion(const Quaternion& _other);

        /**
         * @brief Conjugate the Quaternion. (x, y, z, w) -> (-x, -y, -z, w)
         *
         * @return Self
         */
        FORCE_INLINE Quaternion& conjugate();

        /**
         * @brief Get cross product of two quaternion.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static Quaternion crossProduct(const Quaternion& _a, const Quaternion& _b);

        /**
         * @brief Get dot product of two quaternion.
         *
         * @param _a
         * @param _b
         */
        FORCE_INLINE static f32 dotProduct(const Quaternion& _a, const Quaternion& _b);

        /**
         * @brief Get the conjugated copy of this quaternion. (x, y, z, w) -> (-x, -y, -z, w)
         *
         * @param _other
         */
        FORCE_INLINE Quaternion getConjugated() const;

        /**
         * @brief Get the cross product of this quaternion and another.
         *
         * @param _other
         */
        FORCE_INLINE Quaternion getCrossProduct(const Quaternion& _other) const;

        /**
         * @brief Get the cross product of this quaternion and another.
         *
         * @param _other
         */
        FORCE_INLINE f32 getDotProduct(const Quaternion& _other) const;

        /**
         * @brief Get exponent of quaternion.
         *
         * @return Quaternion
         */
        Quaternion getExponent() const;

        /**
         * @brief Get rotated forward axis.
         */
        Vector3 getForward() const;

        /**
         * @brief Get the inversed copy of this quaternion.
         */
        FORCE_INLINE Quaternion getInversed() const;

        /**
         * @brief Get the magnitude of quaternion.
         */
        FORCE_INLINE f32 getLength() const;

        /**
         * @brief Get logarithm of quaternion.
         */
        Quaternion getLog()const;

        /**
         * @brief Get the normalized copy of this quaternion.
         */
        FORCE_INLINE Quaternion getNormalized() const;

        /**
         * @brief Get rotated right axis.
         */
        Vector3 getRight() const;

        /**
         * @brief Get the sqaured magnitude of quaternion.
         */
        FORCE_INLINE f32 getSqauredLength() const;

        /**
         * @brief Get rotated up axis.
         */
        Vector3 getUp() const;

        /**
         * @brief Inverse quaternion.
         *
         * @return false if quaternion can not inverse
         */
        bool inverse();

        /**
         * @brief Check quaternion is identity.
         */
        FORCE_INLINE bool isIdentity() const;

        /**
         * @brief Check quaternion can inverse.
         */
        FORCE_INLINE bool isInversable() const;

        /**
         * @brief Check quaternion can be normalize.
         */
        FORCE_INLINE bool isNormalizable() const;

        /**
         * @brief Check quaternion is normalized.
         */
        FORCE_INLINE bool isNormalized() const;

        /**
         * @brief Get normalized linear interpolation between two quaternions.
         *
         * @param _a
         * @param _b
         * @param _position
         * @param _shortestPath
         */
        FORCE_INLINE static Quaternion lerp(const Quaternion& _a, const Quaternion& _b, const f32& _position, const bool& _shortestPath = false);

        /**
         * @brief Normalize quaternion.
         *
         * @return false if quaternion is not normalizable.
         */
        FORCE_INLINE bool normalize();

        /**
         * @brief Set valus directly.
         *
         * @param _x
         * @param _y
         * @param _z
         * @param _w
         * @return Self
         */
        FORCE_INLINE Quaternion& set(const f32& _x, const f32& _y, const f32& _z, const f32& _w);

        /**
         * @brief Set value from euler angles.
         *
         * @param _x
         * @param _y
         * @param _z
         * @return Self
         */
        Quaternion& set(const f32& _x, const f32& _y, const f32& _z);

        /**
         * @brief Set value from euler angles.
         *
         * @param _euler
         * @return Self
         */
        Quaternion& set(const Vector3& _euler);

        /**
         * @brief Set from an axis and an angle.
         *
         * @param _axis
         * @param _angle
         * @return Self
         */
        Quaternion& set(const Vector3& _axis, const f32& _angle);

        /**
         * @brief Set value where quaternion will convert axis \p _from to axis \p _to.
         *
         * @param _from
         * @param _to
         * @return Self
         */
        Quaternion& set(const Vector3& _from, const Vector3& _to);

        /**
         * @brief Set from a rotation matrix.
         *
         * @param _matrix
         * @return Self
         */
        Quaternion& set(const Matrix3& _matrix);

        /**
         * @brief Set from axes.
         *
         * @param _right
         * @param _up
         * @param _forward
         */
        void set(const Vector3& _right, const Vector3& _up, const Vector3& _forward);

        /**
         * @brief Get spherical interpolation between two quaternions.
         *
         * @param _a
         * @param _b
         * @param _position
         */
        static Quaternion slerp(Quaternion _a, Quaternion _b, const f32& _position);

        /**
         * @brief Convert to axes.
         *
         * @param _right
         * @param _up
         * @param _forward
         */
        void toAxes(Vector3 &_right, Vector3 &_up, Vector3 &_forward) const;

        /**
         * @brief Convert to axis and angle.
         *
         * @param _axis
         * @param _angle
         */
        void toAxisAngle(Vector3& _axis, f32& _angle) const;

        /**
         * @brief Convert to euler angles.
         */
        Vector3 toEulerAngels() const;

        /**
         * @brief Convert to rotation matrix.
         */
        Matrix3 toMatrix() const;

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Quaternion& operator = (const Quaternion& _other);

        FORCE_INLINE bool operator == (const Quaternion& _other) const;
        FORCE_INLINE bool operator != (const Quaternion& _other) const;

        FORCE_INLINE f32& operator [] (const u8& _d);
        FORCE_INLINE f32 operator [] (const u8& _d) const;

        FORCE_INLINE Quaternion operator + () const;
        FORCE_INLINE Quaternion operator - () const;

        FORCE_INLINE Quaternion operator * (const Quaternion& _other) const;
        FORCE_INLINE Quaternion& operator *= (const Quaternion& _other);

        FORCE_INLINE Quaternion operator * (const f32& _scaler) const;
        FORCE_INLINE Quaternion& operator *= (const f32& _scaler);
        friend FORCE_INLINE Quaternion operator * (const f32& _a, const Quaternion& _b);

        FORCE_INLINE Quaternion operator / (const Quaternion& _other) const;
        FORCE_INLINE Quaternion& operator /= (const Quaternion& _other);

        FORCE_INLINE Quaternion operator / (const f32& _scaler) const;
        FORCE_INLINE Quaternion& operator /= (const f32& _scaler);
        friend FORCE_INLINE Quaternion operator / (const f32& _a, const Quaternion& _b);

        FORCE_INLINE Quaternion operator + (const Quaternion& _other) const;
        FORCE_INLINE Quaternion& operator += (const Quaternion& _other);

        FORCE_INLINE Quaternion operator - (const Quaternion& _other) const;
        FORCE_INLINE Quaternion& operator -= (const Quaternion& _other);

    public:
        static const Quaternion identity;
        static const Quaternion zero;
    public:
        union
        {
            struct
            {
                f32 x, y, z, w;
            };
            f32 m[4];
        };
    };
}

#include "Quaternion.inl"

#endif // __QUATERNION_H__
