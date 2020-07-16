#include "Map.h"
#include "Core/Exception/Exception.h"

namespace Michka
{
    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Element::Element(TKey&& _first, TValue&& _second) : Pair(std::forward<TKey>(_first), std::forward<TValue>(_second))
    {
        //
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Element::Element(const TKey& _first, const TValue& _second) : Pair(_first, _second)
    {
        //
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Element::Element(const Element& _other) : Pair(_other)
    {
        //
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>::Element::Element(Element&& _other) : Pair(std::forward<Element>(_other))
    {
        //
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TKey& Map<TKey, TValue>::Element::key()
    {
        return first;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TKey Map<TKey, TValue>::Element::key() const
    {
        return first;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TValue& Map<TKey, TValue>::Element::value()
    {
        return second;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TValue Map<TKey, TValue>::Element::value() const
    {
        return second;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::Element::operator == (const Map<TKey, TValue>::Element& _other) const
    {
        return first == _other.first && second == _other.second;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::Element::operator != (const Map<TKey, TValue>::Element& _other) const
    {
        return !(*this == _other);
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::Element& Map<TKey, TValue>::Element::operator = (const Map<TKey, TValue>::Element& _other)
    {
        first = _other.first;
        second = _other.second;

        return *this;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE typename Map<TKey, TValue>::Element& Map<TKey, TValue>::Element::operator = (Map<TKey, TValue>::Element&& _other)
    {
        first = std::move(_other.first);
        second = std::move(_other.second);

        return *this;
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
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::filter(const std::function<bool(const Element&)>& _callback)
    {
        *this = getFiltered(_callback);

        return *this;
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
    FORCE_INLINE Map<TKey, TValue> Map<TKey, TValue>::getFiltered(const std::function<bool(const Element&)>& _callback) const
    {
        Michka::Map<TKey, TValue> out;
        out.mData = mData.getFiltered(_callback);

        return out;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TValue Map<TKey, TValue>::getValue(const TKey& _key, const TValue& _default) const
    {
        u32 index = indexOfKey(_key);
        if (index != notFound)
        {
            return mData[index].second;
        }

        return _default;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::hasKey(const TKey& _key) const
    {
        return indexOfKey(_key) != notFound;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::hasValue(const TValue& _value) const
    {
        return indexOfValue(_value) != notFound;
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
    FORCE_INLINE bool Map<TKey, TValue>::isEmpty() const
    {
        return mData.isEmpty();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::isNotEmpty() const
    {
        return mData.isNotEmpty();
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::remove(const TKey& _key)
    {
        if (u32 index = indexOfKey(_key) != notFound)
        {
            mData.remove(index);
        }

        return *this;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::resize(const u32& _newCapacity)
    {
        mData.resize(_newCapacity);

        return *this;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::swap(const TKey& _key1, const TKey& _key2)
    {
        Michka::swap(mData[indexOfKey(_key1)].second, mData[indexOfKey(_key2)].second);

        return *this;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE Map<TKey, TValue>& Map<TKey, TValue>::swap(Map<TKey, TValue>& _other)
    {
        mData.swap(_other.mData);

        return *this;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE TValue Map<TKey, TValue>::take(const TKey& _key)
    {
        return mData.take(indexOfKey(_key)).second;
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
        mData = _other.mData;

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
        if (index == mData.notFound)
        {
            throw Exception("Map::operator[] : Key not found.");
        }

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
                throw Exception("Map::operator[] : Your type is not assaignable.");
            }
        }

        return mData[index].second;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::operator == (const Map<TKey, TValue>& _other) const
    {
        return mData == _other.mData;
    }

    template<typename TKey, typename TValue>
    FORCE_INLINE bool Map<TKey, TValue>::operator != (const Map<TKey, TValue>& _other) const
    {
        return !(*this == _other);
    }
}
