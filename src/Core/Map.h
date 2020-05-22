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
            Element() : Pair() {}
            Element(const TKey& _first, const TValue& _second) : Pair(_first, _second) {}
            Element(const Element& _other) : Pair(_other) {}
            Element(Element&& _other) : Pair(_other) {}
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


        Map<TKey, TValue>& operator = (const std::initializer_list<Element>& _array);
        Map<TKey, TValue>& operator = (const Map<TKey, TValue>& _other);
        Map<TKey, TValue>& operator = (Map<TKey, TValue>&& _other);
    protected:
        Vector<Element> mData;
    };
}

#include "Map.inl"

#endif // __MAP_H__
