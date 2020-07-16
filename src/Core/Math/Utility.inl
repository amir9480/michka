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

#include "Utility.h"
#include "Core/Reflection/Type.h"
#include <math.h>

namespace Michka
{
    namespace Math
    {
        template<typename T>
        FORCE_INLINE T abs(const T& _number)
        {
            return _number < 0 ? -_number : _number;
        }

        FORCE_INLINE f32 acos(const f32& _number)
        {
            return acosf(_number) * degreePerRadian;
        }

        FORCE_INLINE f32 acotan(const f32& _number)
        {
            return atanf(1.0f / _number) * degreePerRadian;
        }

        FORCE_INLINE f32 asin(const f32& _number)
        {
            return asinf(_number) * degreePerRadian;
        }

        FORCE_INLINE f32 atan(const f32& _number)
        {
            return atanf(_number) * degreePerRadian;
        }

        FORCE_INLINE f32 atan2(const f32& _x, const f32& _y)
        {
            return atan2f(_x, _y) * degreePerRadian;
        }

        FORCE_INLINE f32 ceil(const f32& _number)
        {
            return ceilf(_number);
        }

        FORCE_INLINE f32 cos(const f32& _degree)
        {
            return cosf(_degree * radianPerDegree);
        }

        FORCE_INLINE f32 cotan(const f32& _degree)
        {
            // TODO : Implement faster way
            return cos(_degree) / sin(_degree);
        }

        FORCE_INLINE f32 degreesToRadians(const f32& _degrees)
        {
            return _degrees * radianPerDegree;
        }

        template<typename T>
        FORCE_INLINE bool equals(const T& _a, const T& _b, const T& _epsilon)
        {
            if constexpr (Type<T>::isIntegral)
            {
                return _a == _b;
            }
            return abs(_a - _b) < _epsilon;
        }

        FORCE_INLINE f32 floor(const f32& _number)
        {
            return floorf(_number);
        }

        FORCE_INLINE bool isInf(const f32& _number)
        {
            return std::isinf(_number);
        }

        FORCE_INLINE bool isNaN(const f32& _number)
        {
            return std::isnan(_number);
        }

        FORCE_INLINE f32 lerp(const f32& _start, const f32& _end, const f32& _position)
        {
            return _start + (_position * (_end - _start));
        }

        template<typename T>
        FORCE_INLINE T max(const T& _a)
        {
            return _a;
        }

        template<typename T, typename... T2>
        FORCE_INLINE T max(const T& _a, const T& _b, const T2&... _other)
        {
            return _a > _b ? max(_a, _other...) : max(_b, _other...);
        }

        template<typename T>
        FORCE_INLINE T min(const T& _a)
        {
            return _a;
        }

        template<typename T, typename... T2>
        FORCE_INLINE T min(const T& _a, const T& _b, const T2&... _other)
        {
            return _a < _b ? min(_a, _other...) : min(_b, _other...);
        }

        template<typename T>
        FORCE_INLINE T mod(const T& _a, const T& _b)
        {
            if constexpr (Type<T>::is<f32>())
            {
                return fmodf(_a, _b);
            }
            else if constexpr (Type<T>::is<f64>())
            {
                return fmod(_a, _b);
            }
            else if constexpr (Type<T>::is<f96>())
            {
                return fmodl(_a, _b);
            }
            else
            {
                return _a % _b;
            }
        }

        FORCE_INLINE f32 radiansToDegrees(const f32& _radians)
        {
            return _radians * degreePerRadian;
        }

        FORCE_INLINE f32 round(const f32& _number, const f32& _precision)
        {
            f32 number = abs(_number);
            f32 precision = abs(_precision);
            if (mod(number, precision) >= precision * 0.5f)
            {
                return (ceil(number / precision) * precision) * sign(_number);
            }
            return (floor(number / precision) * precision) * sign(_number);
        }

        template<typename T>
        FORCE_INLINE i8 sign(const T& _number)
        {
            if (_number > 0)
            {
                return 1;
            }
            else if (_number == 0)
            {
                return 0;
            }
            return -1;
        }

        template<typename T>
        FORCE_INLINE T clamp(const T& _value, const T& _min, const T& _max, const T& _epsilon)
        {
            if (_value <= _min + _epsilon)
            {
                return _min;
            }
            if (_value >= _max - _epsilon)
            {
                return _max;
            }
            return _value;
        }

        FORCE_INLINE f32 sin(const f32& _degree)
        {
            return sinf(_degree * radianPerDegree);
        }

        FORCE_INLINE f32 sqrt(const f32& _number)
        {
            return sqrtf(_number);
        }

        FORCE_INLINE f32 tan(const f32& _degree)
        {
            return tanf(_degree * radianPerDegree);
        }
    }
}
