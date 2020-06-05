#ifndef __MAP_H__
#define __MAP_H__

#include "Vector.h"
#include "Pair.h"

namespace Michka
{
    template<typename TKey, typename TValue>
    class Map
    {
    public:
        struct Element: public Pair<TKey, TValue>
        {
            Element(TKey&& _first, TValue&& _second): Pair(std::forward<TKey>(_first), std::forward<TValue>(_second)) {}
            Element(const TKey& _first, const TValue& _second) : Pair(_first, _second) {}
            Element(const Element& _other) : Pair(_other) {}
            Element(Element&& _other) : Pair(std::forward<Pair<TKey, TValue>>(_other)) {}
            ~Element() {}

            TKey& key();
            TKey key() const;
            TValue& value();
            TValue value() const;
        };

        typedef Element* Iterator;
        typedef const Element* ConstIterator;

    public:
        FORCE_INLINE Map();
        FORCE_INLINE Map(const std::initializer_list<Element>& _array);
        FORCE_INLINE Map(const Map<TKey, TValue>& _other);
        FORCE_INLINE Map(Map<TKey, TValue>&& _other);
        virtual ~Map();

        /**
         * @brief Get key and value in specific index
         *
         * @param _index
         * @return Element
         */
		FORCE_INLINE Element& at(const u32& _index);
		FORCE_INLINE Element at(const u32& _index) const;

        /**
         * @brief Iterator to begin of array.
         */
        FORCE_INLINE Iterator begin();

        /**
         * @brief Iterator to begin of array for constants.
         */
        FORCE_INLINE ConstIterator begin() const;

        /**
         * @brief Clear map.
         *
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& clear();

        /**
         * @brief Iterator to end of array.
         */
        FORCE_INLINE Iterator end();

        /**
         * @brief Iterator to end of array for constants.
         */
        FORCE_INLINE ConstIterator end() const;

        /**
         * @brief Get count of items in map.
         */
        FORCE_INLINE u32 getSize() const;

        /**
         * @brief Get capacity of map.
         */
        FORCE_INLINE u32 getCapacity() const;

        /**
         * @brief Find index of a key.
         *
         * @param _what
         * @return TKey
         */
        FORCE_INLINE u32 indexOfKey(const TKey& _what) const;

        /**
         * @brief Find index of a value.
         *
         * @param _what
         * @param _from
         * @return TKey
         */
        FORCE_INLINE u32 indexOfValue(const TValue& _what, const u32 _from = 0) const;

        /**
         * @brief Insert into map.
         *
         * @param _what
         * @param _from
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& insert(const TKey& _key, const TValue& _value);
        FORCE_INLINE Map<TKey, TValue>& insert(TKey&& _key, TValue&& _value);

        Map<TKey, TValue>& operator = (const std::initializer_list<Element>& _array);
        Map<TKey, TValue>& operator = (const Map<TKey, TValue>& _other);
        Map<TKey, TValue>& operator = (Map<TKey, TValue>&& _other);

		FORCE_INLINE TValue& operator [] (const TKey& _key);
		FORCE_INLINE TValue operator [] (const TKey& _key) const;
    protected:
        Vector<Element> mData;
    };
}

#include "Map.inl"

#endif // __MAP_H__
