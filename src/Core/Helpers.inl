#include "Helpers.h"

namespace Mishka
{
    template<typename T>
    FORCE_INLINE void swap(T& _a, T& _b)
    {
		T temp = std::move(_a);
		_a = std::move(_b);
		_b = std::move(temp);
    }

    template<typename T>
	FORCE_INLINE const T& min(const T& _a, const T& _b)
    {
        return _a < _b ? _a : _b;
    }

	template<typename T>
	FORCE_INLINE const T& max(const T& _a, const T& _b)
    {
        return _a > _b ? _a : _b;
    }
}
