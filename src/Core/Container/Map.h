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
            Element(Element&& _other) : Pair(std::forward<Element>(_other)) {}
            ~Element() {}

            TKey& key();
            TKey key() const;
            TValue& value();
            TValue value() const;

            using Pair<TKey, TValue>::operator =;

            Element& operator = (const Element& _other);
            Element& operator = (Element&& _other);

            bool operator == (const Element& _other) const;
            bool operator != (const Element& _other) const;
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
         * @brief Filter map items by a callback.
         *
         * @param _callback
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& filter(const std::function<bool(const Element&)>& _callback);

        /**
         * @brief Get capacity of map.
         */
        FORCE_INLINE u32 getCapacity() const;

        /**
         * @brief Get filtered map by a compare callback.
         *
         * @param _callback
         * @return Filtered Vector
         */
        FORCE_INLINE Map<TKey, TValue> getFiltered(const std::function<bool(const Element&)>& _callback) const;

        /**
         * @brief Get count of items in map.
         */
        FORCE_INLINE u32 getSize() const;

        /**
         * @brief Get value of a key. if not exists returns default.
         *
         * @param _key
         * @param _default
         * @return Value of key
         */
        FORCE_INLINE TValue getValue(const TKey& _key, const TValue& _default = TValue()) const;

        /**
         * @brief Check specific key exists.
         *
         * @param _key
         * @return true if exists
         */
        FORCE_INLINE bool hasKey(const TKey& _key) const;

        /**
         * @brief Check specific value exists.
         *
         * @param _value
         * @return true if exists
         */
        FORCE_INLINE bool hasValue(const TValue& _value) const;

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

		/**
		 * @brief Check map is empty.
		 */
		FORCE_INLINE bool isEmpty() const;

		/**
		 * @brief Check map is not empty.
		 */
		FORCE_INLINE bool isNotEmpty() const;

        /**
         * @brief Remove specific key.
         *
         * @param _key
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& remove(const TKey& _key);

        /**
         * @brief Resize capacity of map.
         *
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& resize(const u32& _newCapacity);

        /**
         * @brief Swap two values at specific keys.
         *
         * @param _key1
         * @param _key2
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& swap(const TKey& _key1, const TKey& _key2);

        /**
         * @brief Swap values of this map with another vector.
         *
         * @param _other
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& swap(Map<TKey, TValue>& _other);

        /**
         * @brief Get value of specific key and then remove it.
         *
         * @param _key
         */
        FORCE_INLINE TValue take(const TKey& _key);

        Map<TKey, TValue>& operator = (const std::initializer_list<Element>& _array);
        Map<TKey, TValue>& operator = (const Map<TKey, TValue>& _other);
        Map<TKey, TValue>& operator = (Map<TKey, TValue>&& _other);

		FORCE_INLINE TValue& operator [] (const TKey& _key);
		FORCE_INLINE TValue operator [] (const TKey& _key) const;

        FORCE_INLINE bool operator == (const Map<TKey, TValue>& _other) const;
        FORCE_INLINE bool operator != (const Map<TKey, TValue>& _other) const;

    public:
    /**
     * @brief Not found index for search functions.
     */
    static const u32 notFound = Vector<Element>::notFound;

    protected:
        Vector<Element> mData;
    };
}

#include "Map.inl"

#endif // __MAP_H__
