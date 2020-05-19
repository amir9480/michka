#ifndef __HELPERS_H__
#define __HELPERS_H__

#define MICHKA_ASSERT(_CONDITION, _MESSAGE)

#define MICHKA_GLUE(_X, _Y) _X _Y

#define ___MICHKA_COUNT_ARGS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125,count, ...) count
#define __MICHKA_COUNT_ARGS(_ARGS) ___MICHKA_COUNT_ARGS _ARGS
#define MICHKA_COUNT_ARGS(...) __MICHKA_COUNT_ARGS((__VA_ARGS__, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#define ___MICHKA_OVERLOADED_MACRO(_NAME, _COUNT) _NAME##_COUNT
#define __MICHKA_OVERLOADED_MACRO(_NAME, _COUNT) ___MICHKA_OVERLOADED_MACRO(_NAME, _COUNT)
#define _MICHKA_OVERLOADED_MACRO(_NAME, _COUNT) __MICHKA_OVERLOADED_MACRO(_NAME, _COUNT)
#define MICHKA_OVERLOADED_MACRO(_NAME, ...) MICHKA_GLUE(_MICHKA_OVERLOADED_MACRO(_NAME, MICHKA_COUNT_ARGS(__VA_ARGS__)), (__VA_ARGS__))


#define MICHKA_SINGLETON_CLASS(CLASSNAME)\
	CLASSNAME(const CLASSNAME&) = delete;\
	CLASSNAME(CLASSNAME&&) = delete;\
	CLASSNAME& operator=(const CLASSNAME&) = delete;\
	CLASSNAME& operator=(CLASSNAME&&) = delete;\
	public:\
	static CLASSNAME& instance()\
	{\
		static CLASSNAME o;\
		return o;\
	}\
	private:

namespace Michka
{
	/**
	 * @brief Swap two variable value.
	 */
	template<typename T>
	FORCE_INLINE void swap(T& _a, T& _b);

	template<typename T>
	FORCE_INLINE const T& min(const T& _a, const T& _b);

	template<typename T>
	FORCE_INLINE const T& max(const T& _a, const T& _b);
}

#include "Helpers.inl"

#endif // __HELPERS_H__
