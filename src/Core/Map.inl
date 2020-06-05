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
    FORCE_INLINE typename Map<TKey, TValue>::Element& Map<TKey, TValue>::at(const u32& _index)
    {
        return mData[_index];
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::Element Map<TKey, TValue>::at(const u32& _index) const
    {
        return mData[_index];
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
    FORCE_INLINE u32 Map<TKey, TValue>::indexOfKey(const TKey& _what) const
    {
        return mData.indexOf([=] (const Element& _element)
        {
            return _element.first == _what;
        });
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE u32 Map<TKey, TValue>::indexOfValue(const TValue& _what, const u32 _from) const
    {
        return mData.indexOf([=] (const Element& _element)
        {
            return _element.second == _what;
        }, _from);
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::insert(const TKey& _key, const TValue& _value)
    {
        u32 index = indexOfKey(_key);
        if (index == mData.notFound)
        {
            mData.pushBack(Element(_key, _value));
        }

        return *this;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::insert(TKey&& _key, TValue&& _value)
    {
        u32 index = indexOfKey(_key);
        if (index == mData.notFound)
        {
            mData.pushBack(Element(std::forward<TKey>(_key), std::forward<TValue>(_value)));
        }

        return *this;
    }

    template<typename TKey, typename TValue>
    Map<TKey, TValue>& Map<TKey, TValue>::operator = (const std::initializer_list<Map<TKey, TValue>::Element>& _array)
    {
        for (auto i : _array)
        {
            insert(i.first, i.second);
        }

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

    template<typename TKey, typename TValue>
    FORCE_INLINE TValue Map<TKey, TValue>::operator [] (const TKey& _key) const
    {
        u32 index = indexOfKey(_key);
        MICHKA_ASSERT(index == mData.notFound, "Key not found.");

        return mData[index].second;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TValue& Map<TKey, TValue>::operator [] (const TKey& _key)
    {
        u32 index = indexOfKey(_key);

        if (index == mData.notFound)
        {
            if constexpr (Type<TValue>::hasDefaultConstructor)
            {
                mData.pushBack(Element(_key, TValue()));
                index = mData.getSize() - 1;
            }
            else
            {
                MICHKA_ASSERT(false, "Your type is not assaignable");
            }
        }

        return mData[index].second;
    }
}
