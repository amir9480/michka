#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "Defines.h"
#include <utility>
#include <stdio.h>
#include <memory.h>
#include <type_traits>

#define MISHKA_ASSERT(condition, message)

namespace Mishka
{
	/**
	 * \brief Swap two variable value.
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
