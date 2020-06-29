#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Core/Defines.h"

namespace Michka
{
    namespace Math
    {
        static const f32 pi               = 3.14159265358979323846f;
        static const f32 twoPi            = 6.28318530717958647692f;
        static const f32 halfPi           = 1.57079632679489661923f;
        static const f32 radianPerDegree  = 0.01745329251994329576f;
        static const f32 degreePerRadian  = 57.29577951308232087684f;
        static const f32 epsilon          = 0.00001f;
        static const f32 infinity         = INFINITY;

        /**
         * @brief Absolute number
         *
         * @tparam T
         * @param _number
         */
        template<typename T>
        FORCE_INLINE T abs(const T& _number);

        /**
         * @brief Arc cos
         *
         * @param _number
         */
        FORCE_INLINE f32 acos(const f32& _number);

        /**
         * @brief Arc cotan
         *
         * @param _number
         */
        FORCE_INLINE f32 acotan(const f32& _number);

        /**
         * @brief Arc sin
         *
         * @param _number
         */
        FORCE_INLINE f32 asin(const f32& _number);

        /**
         * @brief Arc tan
         *
         * @param _number
         */
        FORCE_INLINE f32 atan(const f32& _number);

        /**
         * @brief Round value up.
         *
         * @param _number
         */
        FORCE_INLINE f32 ceil(const f32& _number);

        /**
         * @brief clamp number to a range.
         *
         * @tparam T
         * @param _value
         * @param _min
         * @param _max
         */
        template<typename T>
        FORCE_INLINE T clamp(const T& _value, const T& _min = 0, const T& _max = 1);

        /**
         * @brief Cos
         *
         * @param _degree
         */
        FORCE_INLINE f32 cos(const f32& _degree);

        /**
         * @brief Cotan
         *
         * @param _degree
         */
        FORCE_INLINE f32 cotan(const f32& _degree);

        /**
         * @brief Convert degrees to radians
         *
         * @param _degrees
         */
        FORCE_INLINE f32 degreesToRadians(const f32& _degrees);

        /**
         * @brief Check two float point number are equal or not.
         *
         * @tparam T
         * @param _a
         * @param _b
         * @param _epsilon
         */
        template<typename T>
        FORCE_INLINE bool equals(const T& _a, const T& _b, const T& _epsilon = epsilon);

        /**
         * @brief Round value down.
         *
         * @param _number
         */
        FORCE_INLINE f32 floor(const f32& _number);

        /**
         * @brief Check float number is infinite.
         *
         * @param _number
         */
        FORCE_INLINE bool isInf(const f32& _number);

        /**
         * @brief Check float number is Not A Number.
         *
         * @param _number
         */
        FORCE_INLINE bool isNaN(const f32& _number);

        /**
         * @brief Lerp between two numbers.
         *
         * @param _start
         * @param _end
         * @param _position
         */
        FORCE_INLINE f32 lerp(const f32& _start, const f32& _end, const f32& _position);

        /**
         * @brief Get remainder of _a/_b
         *
         * @param _a
         * @param _b
         */
        template<typename T>
        FORCE_INLINE T mod(const T& _a, const T& _b);

        /**
         * @brief Convert radians to degrees
         *
         * @param _radians
         */
        FORCE_INLINE f32 radiansToDegrees(const f32& _radians);

        /**
         * @brief Round.
         *
         * @param _number
         * @param _precision
         */
        FORCE_INLINE f32 round(const f32& _number, const f32& _precision = epsilon);

        /**
         * @brief Get sign of a number.
         *
         * @tparam T
         * @param _number
         * @return -1 / 0 / +1
         */
        template<typename T>
        FORCE_INLINE i8 sign(const T& _number);

        /**
         * @brief Sin
         *
         * @param _degree
         */
        FORCE_INLINE f32 sin(const f32& _degree);

        /**
         * @brief Square root
         *
         * @param _number
         */
        FORCE_INLINE f32 sqrt(const f32& _number);

        /**
         * @brief Tan
         *
         * @param _degree
         */
        FORCE_INLINE f32 tan(const f32& _degree);
    }
}

#include "Utility.inl"

#endif // __UTILITY_H__
