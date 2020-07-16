#ifndef __PAIR_H__
#define __PAIR_H__

#include <utility>

namespace Michka
{
    template<typename T1, typename T2>
    struct Pair
    {
        FORCE_INLINE Pair();
        FORCE_INLINE Pair(const T1& _first, const T2& _second);
        FORCE_INLINE Pair(T1&& _first, T2&& _second);
        FORCE_INLINE Pair(const Pair<T1, T2>& _other);
        FORCE_INLINE Pair(Pair<T1, T2>&& _other);
        FORCE_INLINE ~Pair();

        FORCE_INLINE Pair<T1, T2>& operator = (const Pair<T1, T2>& _other);
        FORCE_INLINE Pair<T1, T2>& operator = (Pair<T1, T2>&& _other);

        T1 first;
        T2 second;
    };
}

#include "Pair.inl"

#endif // __PAIR_H__
