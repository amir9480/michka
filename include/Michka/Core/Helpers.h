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

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <functional>
#include <type_traits>
#include "Michka/Core/Defines.h"
#include "Reflection/Type.h"

#define ____MICHKA_COMMA ,
#define ___MICHKA_COMMA ____MICHKA_COMMA
#define __MICHKA_COMMA ___MICHKA_COMMA
#define _MICHKA_COMMA __MICHKA_COMMA
#define MICHKA_COMMA _MICHKA_COMMA

/**
 * @brief Attach two statements with a space
 *
 */
#define MICHKA_GLUE(_X, _Y) _X _Y

/**
 * @brief To pass arguments that contains , as a single argument to macros.
 *
 * TEST(MICHKA_ARGUMENT(Map<Tkey, TValue>), Argument2)
 */
#define MICHKA_ARGUMENT(...) __VA_ARGS__

#define ____MICHKA_COUNT_ARGS(...) _N, __VA_ARGS__
#define ___MICHKA_COUNT_ARGS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _COUNT, ...) _COUNT
#define __MICHKA_COUNT_ARGS(_ARGS) ___MICHKA_COUNT_ARGS _ARGS
#define _MICHKA_COUNT_ARGS(...) __MICHKA_COUNT_ARGS((__VA_ARGS__, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define MICHKA_COUNT_ARGS(...) _MICHKA_COUNT_ARGS(____MICHKA_COUNT_ARGS(__VA_ARGS__))

#define ___MICHKA_OVERLOADED_MACRO(_NAME, _COUNT) _NAME##_COUNT
#define __MICHKA_OVERLOADED_MACRO(_NAME, _COUNT) ___MICHKA_OVERLOADED_MACRO(_NAME, _COUNT)
#define _MICHKA_OVERLOADED_MACRO(_NAME, _COUNT) __MICHKA_OVERLOADED_MACRO(_NAME, _COUNT)
#define MICHKA_OVERLOADED_MACRO(_NAME, ...) MICHKA_GLUE(_MICHKA_OVERLOADED_MACRO(_NAME, MICHKA_COUNT_ARGS(__VA_ARGS__)), (__VA_ARGS__))

#define ___MICHKA_VA_COUNT_ARGS(...) __MICHKA_COUNT_ARGS((__VA_ARGS__, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, MULTIPLE, ZERO))
#define __MICHKA_VA_COUNT_ARGS(...) ___MICHKA_VA_COUNT_ARGS(____MICHKA_COUNT_ARGS(__VA_ARGS__))
#define MICHKA_OVERLOADED_VA_MACRO(_NAME, ...) MICHKA_GLUE(_MICHKA_OVERLOADED_MACRO(_NAME, __MICHKA_VA_COUNT_ARGS(__VA_ARGS__)), (__VA_ARGS__))

#define MICHKA_VA_COMMA(...) MICHKA_OVERLOADED_VA_MACRO(_MICHKA_VA_COMMA_, __VA_ARGS__)
#define _MICHKA_VA_COMMA_ZERO()
#define _MICHKA_VA_COMMA_MULTIPLE(...) ,

#define MICHKA_NON_COPYABLE_CLASS(_CLASSNAME) \
    _CLASSNAME(const _CLASSNAME&) = delete; \
    _CLASSNAME(_CLASSNAME&&) = delete; \
    _CLASSNAME& operator = (const _CLASSNAME&) = delete; \
    _CLASSNAME& operator = (_CLASSNAME&&) = delete;

#define MICHKA_SINGLETON_CLASS(_CLASSNAME) \
    MICHKA_NON_COPYABLE_CLASS(_CLASSNAME) \
    public: \
    static _CLASSNAME& instance() \
    { \
        static _CLASSNAME o; \
        return o; \
    } \
    private:

#define MICHKA_ATTACH(...) MICHKA_OVERLOADED_MACRO(_MICHKA_ATTACH, __VA_ARGS__)

#define _MICHKA_ATTACH2(_A, _B) _A##_B
#define _MICHKA_ATTACH3(_A, _B, _C) _A##_B##_C
#define _MICHKA_ATTACH4(_A, _B, _C, _D) _A##_B##_C##_D
#define _MICHKA_ATTACH5(_A, _B, _C, _D, _E) _A##_B##_C##_D##_E

/**
 * @brief this macro is using to detect a member function exists or not.
 *
 * @example
 * First define class with this macro:
 * @code{.cpp}
 * MICHKA_HAS_MEMBER_FUNCTION_ADD(HasGetSum, int, getSum, int, int); // int getSum(int, int)
 * @endcode
 *
 * To check method exists in specific class:
 * @code{.cpp}
 * HasGetSum<YourClassToCheck>::value
 * @endcode
 *
 * If you have a overloaded method you can also check for other types of method.
 * @code{.cpp}
 * MichkaHasMemberFunction::HasGetSum<YourClassToCheck, float(float, float, float)>::value
 * @endcode
 */
#define MICHKA_HAS_MEMBER_FUNCTION_ADD(_NAME, _RETURN_TYPE, _FUNCTION_NAME, ...) \
    namespace MichkaHasMemberFunction \
    { \
        template<typename, typename T> \
        class MICHKA_ATTACH(, _NAME) \
        { \
            static_assert( \
                std::integral_constant<T, false>::value, \
                "Second template parameter needs to be of function type." \
            ); \
        }; \
        template<typename Class, typename ReturnType, typename... Args> \
        class _NAME<Class, ReturnType(Args...)> \
        { \
            template<typename T> \
            static constexpr auto check(T*) \
            -> typename std::is_same< \
                    decltype(std::declval<T>()._FUNCTION_NAME(std::declval<Args>()...)), \
                    ReturnType \
                >::type; \
        \
            template<typename> \
            static constexpr std::false_type check(...); \
        \
            typedef decltype(check<Class>(0)) type; \
        \
        public: \
            static constexpr bool value = type::value; \
        }; \
    } \
    template<typename Class> \
    class _NAME : public MichkaHasMemberFunction::_NAME<Class, _RETURN_TYPE(__VA_ARGS__)> \
    { \
    }

MICHKA_HAS_MEMBER_FUNCTION_ADD(HasToString, Michka::String, toString);

/**
 * @brief To easily define binary operators for enums
 */
#define MICHKA_ENUM_OPERATORS(_ENUM) \
    FORCE_INLINE _ENUM operator ~ (const _ENUM& _a) \
    { \
        return (_ENUM)(~(int)_a); \
    } \
    FORCE_INLINE _ENUM operator | (const _ENUM& _a, const _ENUM& _b) \
    { \
        return (_ENUM)((int)_a | (int)_b); \
    } \
    FORCE_INLINE _ENUM operator & (const _ENUM& _a, const _ENUM& _b) \
    { \
        return (_ENUM)((int)_a & (int)_b); \
    } \
    FORCE_INLINE _ENUM operator ^ (const _ENUM& _a, const _ENUM& _b) \
    { \
        return (_ENUM)((int)_a ^ (int)_b); \
    } \
    FORCE_INLINE _ENUM& operator |= (_ENUM& _a, const _ENUM& _b) \
    { \
        return (_ENUM&)((int&)_a |= (int)_b); \
    } \
    FORCE_INLINE _ENUM& operator &= (_ENUM& _a, const _ENUM& _b) \
    { \
        return (_ENUM&)((int&)_a &= (int)_b); \
    } \
    FORCE_INLINE _ENUM& operator ^= (_ENUM& _a, const _ENUM& _b) \
    { \
        return (_ENUM&)((int&)_a ^= (int)_b); \
    } \
    FORCE_INLINE _ENUM operator | (const _ENUM& _a, const int& _b) \
    { \
        return (_ENUM)((int)_a | _b); \
    } \
    FORCE_INLINE _ENUM operator & (const _ENUM& _a, const int& _b) \
    { \
        return (_ENUM)((int)_a & _b); \
    } \
    FORCE_INLINE _ENUM operator ^ (const _ENUM& _a, const int& _b) \
    { \
        return (_ENUM)((int)_a ^ _b); \
    } \
    FORCE_INLINE _ENUM& operator |= (_ENUM& _a, const int& _b) \
    { \
        return (_ENUM&)((int&)_a |= _b); \
    } \
    FORCE_INLINE _ENUM& operator &= (_ENUM& _a, const int& _b) \
    { \
        return (_ENUM&)((int&)_a &= _b); \
    } \
    FORCE_INLINE _ENUM& operator ^= (_ENUM& _a, const int& _b) \
    { \
        return (_ENUM&)((int&)_a ^= _b); \
    }


/*!
 * @example
 *
 * void michkaCallOnStart()
 * {
 *     // This would be called before main function start
 * }
 */
#define michkaCallOnStart() \
static  MICHKA_ATTACH(__michka_call, __LINE__)(); \
namespace \
{ \
    struct MICHKA_ATTACH(__michka_fake_type, __LINE__) \
    { \
        MICHKA_ATTACH(__michka_fake_type, __LINE__)() \
        { \
            MICHKA_ATTACH(__michka_call, __LINE__)(); \
        } \
        static const MICHKA_ATTACH(__michka_fake_type, __LINE__) m; \
    }; \
    const MICHKA_ATTACH(__michka_fake_type, __LINE__) MICHKA_ATTACH(__michka_fake_type, __LINE__)::m; \
} \
static void MICHKA_ATTACH(__michka_call, __LINE__)()

/*!
 * @example
 *
 * void michkaCallOnEnd()
 * {
 *     // This would be called after main function end
 * }
 */
#define michkaCallOnEnd() \
static  MICHKA_ATTACH(__michka_call, __LINE__)(); \
namespace \
{ \
    struct MICHKA_ATTACH(__michka_fake_type, __LINE__) \
    { \
        ~ MICHKA_ATTACH(__michka_fake_type, __LINE__)() \
        { \
            MICHKA_ATTACH(__michka_call, __LINE__)(); \
        } \
        static const MICHKA_ATTACH(__michka_fake_type, __LINE__) m; \
    }; \
    const MICHKA_ATTACH(__michka_fake_type, __LINE__) MICHKA_ATTACH(__michka_fake_type, __LINE__)::m; \
} \
static void MICHKA_ATTACH(__michka_call, __LINE__)()

/**
 * @brief Define struct reflection.
 */
#define MICHKA_STRUCT(...)

/**
 * @brief Define class reflection.
 */
#define MICHKA_CLASS(...) \
    public: \
        MICHKA_STRUCT(__VA_ARGS__) \
    private:

namespace Michka
{
    enum class SortDirection
    {
        ascending,
        descending
    };

    template<typename T>
    FORCE_INLINE T max(const T& _a);

    /**
     * @brief Get maximum between multiple number.
     *
     * @tparam T
     * @tparam T2
     * @param _a
     * @param _b
     */
    template<typename T, typename... T2>
    FORCE_INLINE T max(const T& _a, const T2&... _b);

    template<typename T>
    FORCE_INLINE T min(const T& _a);

    /**
     * @brief Get minimum between multiple number.
     *
     * @tparam T
     * @tparam T2
     * @param _a
     * @param _b
     */
    template<typename T, typename... T2>
    FORCE_INLINE T min(const T& _a, const T2&... _b);

    /**
     * @brief Sort any iteratable.
     *
     * @tparam T
     * @tparam ElementType
     * @param _array
     * @param _direction
     */
    template<typename T, typename ElementType = Type<T>::RemovedPointerType>
    FORCE_INLINE void sort(T _array, const u32& _size, const SortDirection& _direction);

    /**
     * @brief Sort any iteratable with custom callback.
     *
     * @tparam T
     * @tparam ElementType
     * @param _array
     * @param _callback
     */
    template<typename T, typename ElementType = Type<T>::RemovedPointerType>
    FORCE_INLINE void sort(T _array, const u32& _size, const std::function<bool(const ElementType&, const ElementType&)>& _callback);

    /**
     * @brief Swap two variable value.
     */
    template<typename T>
    FORCE_INLINE void swap(T& _a, T& _b);
}

#include "Core/Helpers.inl"

#endif // __HELPERS_H__
