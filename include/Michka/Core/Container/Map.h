// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2021 amir alizadeh.                                          //
//                                                                                 //
// Permission is hereby granted, free of charge, to any person obtaining a copy    //
// of this software and associated documentation files (the "Software"), to deal   //
// in the Software without restriction, including without limitation the rights    //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       //
// copies of the Software, and to permit persons to whom the Software is           //
// furnished to do so, subject to the following conditions:                        //
//                                                                                 //
// The above copyright notice and this permission notice shall be included in all  //
// copies or substantial portions of the Software.                                 //
//                                                                                 //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
// SOFTWARE.                                                                       //
// ------------------------------------------------------------------------------- //

#ifndef __MAP_H__
#define __MAP_H__

#include "Vector.h"
#include "Pair.h"
#include "Michka/Core/Helpers.h"

namespace Michka
{
    template<typename TKey, typename TValue>
    class MICHKA_API Map
    {
    public:
        struct Element: public Pair<TKey, TValue>
        {
            FORCE_INLINE Element(TKey&& _first, TValue&& _second);
            FORCE_INLINE Element(const TKey& _first, const TValue& _second);
            FORCE_INLINE Element(const Element& _other);
            FORCE_INLINE Element(Element&& _other);

            FORCE_INLINE TKey& key();
            FORCE_INLINE TKey key() const;
            FORCE_INLINE TValue& value();
            FORCE_INLINE TValue value() const;

            using Pair<TKey, TValue>::operator =;

            FORCE_INLINE Element& operator = (const Element& _other);
            FORCE_INLINE Element& operator = (Element&& _other);

            FORCE_INLINE bool operator == (const Element& _other) const;
            FORCE_INLINE bool operator != (const Element& _other) const;
        };

        typedef Element* Iterator;
        typedef const Element* ConstIterator;

    public:
        FORCE_INLINE Map();
        FORCE_INLINE Map(const std::initializer_list<Element>& _array);
        FORCE_INLINE Map(const Map<TKey, TValue>& _other);
        FORCE_INLINE Map(Map<TKey, TValue>&& _other);

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
         * @brief Get first item.
         */
        FORCE_INLINE Element& first();
        FORCE_INLINE Element first() const;

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
         * @brief Get last item.
         */
        FORCE_INLINE Element& last();
        FORCE_INLINE Element last() const;

        /**
         * @brief Remove specific key.
         *
         * @param _key
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& remove(const TKey& _key);

        /**
         * @brief Remove at specific index instead of searching for key.
         *
         * @param _index
         * @return Self
         */
        FORCE_INLINE Map<TKey, TValue>& removeAt(const u32& _index);

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

#include "Core/Container/Map.inl"

#endif // __MAP_H__
