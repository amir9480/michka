#include "Pair.h"

namespace Michka
{
    template<typename T1, typename T2>
    Pair<T1, T2>::Pair()
    {
    }

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(const T1& _first, const T2& _second)
    {
        first = _first;
        second = _second;
    }

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(const Pair<T1, T2>& _other)
    {
        *this = _other;
    }

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(Pair<T1, T2>&& _other)
    {
        *this = std::move(_other);
    }

    template<typename T1, typename T2>
    Pair<T1, T2>::~Pair()
    {
    }

    template<typename T1, typename T2>
    Pair<T1, T2>& Pair<T1, T2>::operator = (const Pair<T1, T2>& _other)
    {
        first = _other.first;
        second = _other.second;

        return *this;
    }

    template<typename T1, typename T2>
    Pair<T1, T2>& Pair<T1, T2>::operator = (Pair<T1, T2>&& _other)
    {
        first = std::move(_other.first);
        second = std::move(_other.second);

        return *this;
    }
}
