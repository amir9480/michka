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

#ifndef __TYPES_H__
#define __TYPES_H__

#include "Core/Defines.h"
#include <float.h>
#include <typeinfo>
#include <type_traits>

namespace Michka
{
    /**
     * @see TypeBase::hasOperator
     */
    namespace OperatorCheck
    {
        struct NoType{bool _m[2];};
        template<typename _T1, typename _T2>
        inline NoType operator == (const _T1&, const _T2&);
        template<typename _T1, typename _T2>
        inline NoType operator != (const _T1&, const _T2&);
        template<typename _T1, typename _T2>
        inline NoType operator > (const _T1&, const _T2&);
        template<typename _T1, typename _T2>
        inline NoType operator < (const _T1&, const _T2&);
        template<typename _T1, typename _T2>
        inline NoType operator >= (const _T1&, const _T2&);
        template<typename _T1, typename _T2>
        inline NoType operator <= (const _T1&, const _T2&);

        template<typename T1, typename T2 = T1>
        struct hasEqual{const static bool value = !std::is_same<decltype(*(T1*)(0) == *(T2*)(0)), NoType>::value;};

        template<typename T1, typename T2 = T1>
        struct hasNotEqual{const static bool value = !std::is_same<decltype(*(T1*)(0) != *(T2*)(0)), NoType>::value;};

        template<typename T1, typename T2 = T1>
        struct hasGreater{const static bool value = !std::is_same<decltype(*(T1*)(0) > *(T2*)(0)), NoType>::value;};

        template<typename T1, typename T2 = T1>
        struct hasLess{const static bool value = !std::is_same<decltype(*(T1*)(0) < *(T2*)(0)), NoType>::value;};

        template<typename T1, typename T2 = T1>
        struct hasGreaterOrEqual{const static bool value = !std::is_same<decltype(*(T1*)(0) >= *(T2*)(0)), NoType>::value;};

        template<typename T1, typename T2 = T1>
        struct hasLessOrEqual{const static bool value = !std::is_same<decltype(*(T1*)(0) <= *(T2*)(0)), NoType>::value;};
    }

    /**
     * @brief Set of type properties.
     *
     * @tparam T
     */
    template<typename T>
    struct TypeBase
    {
        /**
         * @brief Type without pointer.
         */
        using RemovedPointerType = typename std::remove_pointer<T>::type;

        /**
         * @brief Type without reference.
         */
        using RemovedReferenceType = typename std::remove_reference<T>::type;

        /**
         * @brief Type without const.
         */
        using RemovedConstType = typename std::remove_const<T>::type;

        /**
         * @brief Type without volatile.
         */
        using RemovedVolatileType = typename std::remove_volatile<T>::type;

        /**
         * @brief Sizeof type
         */
        static inline const u32 size = sizeof(T);

        /**
         * @brief Name of type if was native. "Unknown" for custom types like classes and enums.
         */
        static inline const char* name = "Unknown";

        /**
         * @brief Type id name.
         */
        static inline const char* typeName = typeid(T).name();

        /**
         * @brief Type raw name.
         */
        static inline const char* rawName = typeid(T).raw_name();

        /**
         * @brief Type id hash.
         */
        static inline const u64 hash = typeid(T).hash_code();

        /**
         * @brief Minimum possilbe value for numeric types.
         */
        static inline const u32 min = 0;

        /**
         * @brief Maximum possilbe value for numeric types.
         */
        static inline const u32 max = 0;

        /**
         * @brief Is type signed for numeric types.
         */
        static inline const bool isSigned = std::is_signed<T>::value;

        /**
         * @brief Is type unsigned for numeric types.
         */
        static inline const bool isUnsigned = std::is_unsigned<T>::value;

        /**
         * @brief Is type integral for numeric types.
         */
        static inline const bool isIntegral = std::is_integral<T>::value;

        /**
         * @brief Is type real for numeric types.
         */
        static inline const bool isFloat = std::is_floating_point<T>::value;

        /**
         * @brief Is type a numeric types.
         */
        static inline const bool isNumeric = std::is_arithmetic<T>::value;

        /**
         * @brief Is type a custom class.
         */
        static inline const bool isClass = __is_class(T);

        /**
         * @brief Is type a custom union.
         */
        static inline const bool isUnion = __is_union(T);

        /**
         * @brief Is type a custom enum.
         */
        static inline const bool isEnum = __is_enum(T);

        /**
         * @brief Is type a pointer type.
         */
        static inline const bool isPointer = std::is_pointer<T>::value;

        /**
         * @brief Is type a c string
         */
        static inline const bool isCString =
            (std::is_array<typename std::remove_cv<RemovedReferenceType>::type>::value && std::is_same<char, typename std::remove_extent<typename std::remove_cv<RemovedReferenceType>::type>::type>::value) ||
            std::is_same<char *, typename std::remove_cv<RemovedReferenceType>::type>::value ||
            std::is_same<const char *, typename std::remove_cv<RemovedReferenceType>::type>::value ||
            std::is_same<char[], typename std::remove_cv<RemovedReferenceType>::type>::value ||
            std::is_same<const char [], typename std::remove_cv<RemovedReferenceType>::type>::value;

        /**
         * @brief Is type assaignable.
         */
        static inline const bool hasCopyAssign = std::is_assignable<std::remove_reference<T>::type&, T>::value;

        /**
         * @brief Is type move assaignable.
         */
        static inline const bool hasMoveAssign = std::is_move_assignable<T>::value;

        /**
         * @brief Is type has a default constructor.
         */
        static inline const bool hasDefaultConstructor = std::is_default_constructible<T>::value;

        /**
         * @brief Is type has a destrucor function.
         */
        static inline const bool hasDestructor = std::is_trivially_destructible<T>::value;

        /**
         * @brief Check type is same.
         */
        template<typename T2>
        static constexpr inline const bool is();

        /**
         * @brief Check specific operator exists or not.
         */
        template<typename T2 = T>
        struct hasOperator
        {
            static inline const bool equal = OperatorCheck::hasEqual<T, T2>::value;
            static inline const bool notEqual = OperatorCheck::hasNotEqual<T, T2>::value;
            static inline const bool less = OperatorCheck::hasLess<T, T2>::value;
            static inline const bool greater = OperatorCheck::hasGreater<T, T2>::value;
            static inline const bool lessOrEqual = OperatorCheck::hasLessOrEqual<T, T2>::value;
            static inline const bool greaterOrEqual = OperatorCheck::hasGreaterOrEqual<T, T2>::value;
        };
    };

    template<typename T>
    struct Type : public TypeBase<T>
    {};

    /* --------------------------------- Boolean -------------------------------- */
    template<>
    struct Type<bool>: TypeBase<bool>
    {
        static inline const char* name = "bool";
        static inline const bool max = true;
        static inline const bool min = false;
    };

    /* ---------------------------- Signed Integrals ---------------------------- */

    template<>
    struct Type<char>: TypeBase<char>
    {
        static inline const char* name = "char";
        static inline const char max =  0x7f;
        static inline const char min = -0x80;
    };

    template<>
    struct Type<signed char>: TypeBase<signed char>
    {
        static inline const char* name = "signed char";
        static inline const char max =  0x7f;
        static inline const char min = -0x80;
    };

    template<>
    struct Type<short int>: TypeBase<short int>
    {
        static inline const char* name = "short int";
        static inline const short int max =  0x7fff;
        static inline const short int min = -0x8000;
    };

    template<>
    struct Type<int>: TypeBase<int>
    {
        static inline const char* name = "int";
        static inline const int max =  0x7fffffff;
        static inline const int min = -0x7fffffff - 1;
    };

    template<>
    struct Type<long int>: TypeBase<long int>
    {
        static inline const char* name = "long int";
        static inline const int max =  0x7fffffff;
        static inline const int min = -0x7fffffff - 1;
    };

    template<>
    struct Type<long long int>: TypeBase<long long int>
    {
        static inline const char* name = "long long int";
        static inline const long long int max =  0x7fffffffffffffff;
        static inline const long long int min = -0x7fffffffffffffff - 1;
    };

    /* --------------------------- Unsinged Integrals --------------------------- */

    template<>
    struct Type<unsigned char>: TypeBase<unsigned char>
    {
        static inline const char* name = "unsigned char";
        static inline const unsigned char min = 0;
        static inline const unsigned char max = 0xff;
    };

    template<>
    struct Type<unsigned short int>: TypeBase<unsigned short int>
    {
        static inline const char* name = "unsigned short int";
        static inline const unsigned short int min = 0;
        static inline const unsigned short int max = 0xffff;
    };

    template<>
    struct Type<unsigned int>: TypeBase<unsigned int>
    {
        static inline const char* name = "unsigned int";
        static inline const unsigned int min = 0;
        static inline const unsigned int max = 0xffffffff;
    };

    template<>
    struct Type<unsigned long int>: TypeBase<unsigned long int>
    {
        static inline const char* name = "unsigned long int";
        static inline const unsigned int min = 0;
        static inline const unsigned int max = 0xffffffff;
    };

    template<>
    struct Type<unsigned long long int>: TypeBase<unsigned long long int>
    {
        static inline const char* name = "unsigned long long int";
        static inline const unsigned long long int min = 0;
        static inline const unsigned long long int max = 0xffffffffffffffff;
    };

    /* ----------------------------- Floating point ----------------------------- */

    template<>
    struct Type<float>: TypeBase<float>
    {
        static inline const char* name = "float";
        static inline const float max = FLT_MAX;
        static inline const float min = FLT_MIN;
        static inline const float epsilon = 1.19209e-07f;
    };

    template<>
    struct Type<double>: TypeBase<double>
    {
        static inline const char* name = "double";
        static inline const double max = DBL_MAX;
        static inline const double min = DBL_MIN;
        static inline const double epsilon = 2.22045e-16;
    };

    template<>
    struct Type<long double>: TypeBase<long double>
    {
        static inline const char* name = "long double";
        static inline const long double max = LDBL_MAX;
        static inline const long double min = LDBL_MIN;
        static inline const long double epsilon = 1.0842e-19L;
    };

    /* ----------------------------- Character Types ---------------------------- */

    template<>
    struct Type<wchar_t>: TypeBase<wchar_t>
    {
        static inline const char* name = "wchar_t";
        static inline const wchar_t max = 0xffff;
        static inline const wchar_t min = 0;
    };

    template<>
    struct Type<char16_t>: TypeBase<char16_t>
    {
        static inline const char* name = "char16_t";
        static inline const char16_t max = 0xffff;
        static inline const char16_t min = 0;
    };

    template<>
    struct Type<char32_t>: TypeBase<char32_t>
    {
        static inline const char* name = "char32_t";
        static inline const char32_t max = 0xffffffff;
        static inline const char32_t min = 0;
    };

    typedef Type<i8> i8Info;
    typedef Type<i16> i16Info;
    typedef Type<i32> i32Info;
    typedef Type<i64> i64Info;
    typedef Type<u8> u8Info;
    typedef Type<u16> u16Info;
    typedef Type<u32> u32Info;
    typedef Type<u64> u64Info;
}

#include "Type.inl"

#endif // __TYPES_H__
