#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <utility>
#include <stdio.h>
#include <memory.h>

#define MISHKA_ASSERT(condition, message)

namespace Mishka
{
	/**
	 * \brief Swap two variable value.
	 */
	template<typename T>
	void swap(T& _a, T& _b)
	{
		T temp = std::move(_a);
		_a = std::move(_b);
		_b = std::move(temp);
	}
}

#endif // __HELPERS_H__
