#include "Map.h"

namespace Michka
{
    template<typename TKey, typename TValue>
    TKey& Map<TKey, TValue>::Element::key()
    {
        return first;
    }

    template<typename TKey, typename TValue>
    TKey Map<TKey, TValue>::Element::key() const
    {
        return first;
    }

    template<typename TKey, typename TValue>
    TValue& Map<TKey, TValue>::Element::value()
    {
        return second;
    }

    template<typename TKey, typename TValue>
    TValue Map<TKey, TValue>::Element::value() const
    {
        return second;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Map()
    {
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Map(const std::initializer_list<Map<TKey, TValue>::Element>& _array)
    {
        *this = _array;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Map(const Map<TKey, TValue>& _other)
    {
        *this = _other;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Map(Map<TKey, TValue>&& _other)
    {
        *this = std::move(_other);
    }

    template<typename TKey, typename TValue>
    Map<TKey, TValue>::~Map()
    {
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::Iterator Map<TKey, TValue>::begin()
    {
        return mData.begin();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::ConstIterator Map<TKey, TValue>::begin() const
    {
        return mData.begin();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::clear()
    {
        mData.clear();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::Iterator Map<TKey, TValue>::end()
    {
        return mData.end();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::ConstIterator Map<TKey, TValue>::end() const
    {
        return mData.end();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE u32 Map<TKey, TValue>::getSize() const
    {
        return mData.getSize();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE u32 Map<TKey, TValue>::getCapacity() const
    {
        return mData.getCapacity();
    }

    template<typename TKey, typename TValue>
    Map<TKey, TValue>& Map<TKey, TValue>::operator = (const std::initializer_list<Map<TKey, TValue>::Element>& _array)
    {
        mData = _array;

        return *this;
    }

    template<typename TKey, typename TValue>
    Map<TKey, TValue>& Map<TKey, TValue>::operator = (const Map<TKey, TValue>& _other)
    {
        mData = _other;

        return *this;
    }

    template<typename TKey, typename TValue>
    Map<TKey, TValue>& Map<TKey, TValue>::operator = (Map<TKey, TValue>&& _other)
    {
        mData = std::move(_other.mData);

        return *this;
    }
}
