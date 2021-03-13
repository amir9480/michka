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

#ifndef __LIST_H__
#define __LIST_H__

#include "Core/Helpers.h"
#include <initializer_list>
#include "MichkaGenerated/Core/Container/List.generated.h"

namespace Michka
{
    template<typename T>
    class List
    {
        MICHKA_CLASS(List<T>);

        template<class U>
        friend class List;
    public:
        class Element
        {
            friend class List;
            friend class Iterator;
            friend class ConstIterator;

            FORCE_INLINE Element(const T& _val);
            FORCE_INLINE Element(T&& _val);
            ~Element();

            T value;
            Element* next = nullptr;
            Element* prev = nullptr;
        };

        class ConstIterator
        {
            friend class List;
        public:
            FORCE_INLINE ConstIterator();

            FORCE_INLINE ConstIterator operator + (const i32& _number) const;
            FORCE_INLINE ConstIterator operator - (const i32& _number) const;
            FORCE_INLINE const T& operator [] (const i32& _number) const;
            FORCE_INLINE const T& operator * () const;
            FORCE_INLINE const T* operator -> () const;
            FORCE_INLINE operator bool () const;
            FORCE_INLINE bool operator ! () const;
            FORCE_INLINE ConstIterator& operator ++ ();
            FORCE_INLINE ConstIterator& operator -- ();
            FORCE_INLINE bool operator == (const ConstIterator& _other) const;
            FORCE_INLINE bool operator != (const ConstIterator& _other) const;
            FORCE_INLINE T operator [] (const u32& _index) const;
        private:
            FORCE_INLINE ConstIterator(typename List<T>::Element* _element);

            Element* mElement = nullptr;
        };

        class Iterator : public ConstIterator
        {
            friend class List;
        public:
            Iterator();

            FORCE_INLINE T& operator * ();
            FORCE_INLINE T* operator -> ();
            FORCE_INLINE T& operator [] (const u32& _index);
        private:
            FORCE_INLINE Iterator(typename List<T>::Element* _element);
        };
    public:
        FORCE_INLINE List();
        FORCE_INLINE List(const std::initializer_list<T>& _array);
        FORCE_INLINE List(const List<T>& _other);
        FORCE_INLINE List(List<T>&& _other);
        FORCE_INLINE ~List();

        /**
         * @brief Iterator to begin of array.
         */
        FORCE_INLINE Iterator begin();

        /**
         * @brief Iterator to begin of array for constants.
         */
        FORCE_INLINE ConstIterator begin() const;

        /**
         * @brief Clear list.
         *
         * @return Self
         */
        FORCE_INLINE List<T>& clear();

        /**
         * @brief Iterator to end of array.
         */
        FORCE_INLINE Iterator end();

        /**
         * @brief Iterator to end of array for constants.
         */
        FORCE_INLINE ConstIterator end() const;

        /**
         * @brief Filter list items by a callback.
         *
         * @param _callback
         * @return Self
         */
        List<T>& filter(const std::function<bool(const T&)>& _callback);

        /**
         * @brief Get first item.
         */
        FORCE_INLINE T& first();
        FORCE_INLINE T first() const;

        /**
         * @brief Get count of items in list.
         */
        FORCE_INLINE u32 getSize() const;

        /**
         * @brief Get filtered list by a compare callback.
         *
         * @param _callback
         * @return Filtered List
         */
        FORCE_INLINE List<T> getFiltered(const std::function<bool(const T&)>& _callback) const;

        /**
         * @brief Get reversed copy of the list.
         *
         * @return Reversed List
         */
        FORCE_INLINE List<T> getReversed() const;

        /**
         * @brief Get sorted copy of this list.
         *
         * @param _direction
         * @return Sorted List
         */
        FORCE_INLINE List<T> getSorted(const SortDirection& _direction = SortDirection::ascending) const;

        /**
         * @brief Get sorted copy of this list with custom callback.
         *
         * @param _callback
         * @return Sorted List
         */
        FORCE_INLINE List<T> getSorted(const std::function<bool(const T&, const T&)>& _callback) const;

        /**
         * @brief Get unique copy of this list.
         *
         * @param _what
         * @return Self
         */
        FORCE_INLINE List<T> getUnique();

        /**
         * @brief Get unique copy of this list.
         *
         * @param _callback
         * @return Self
         */
        FORCE_INLINE List<T> getUnique(const std::function<bool(const T&, const T&)>& _callback);

        /**
         * @brief Join list elements as a string.
         *
         * @param _seperator
         */
        String implode(const String& _seperator = ",") const;

        /**
         * @brief Find index of a value with offset of from.
         *
         * @param _what
         * @param _from
         * @return index of value. notFound if nothing found.
         */
        u32 indexOf(const T& _what, const u32 _from = 0) const;

        /**
         * @brief Find index of a value with offset of from with custom a callback.
         *
         * @param _callback
         * @param _from
         * @return index of value. notFound if nothing found.
         */
        u32 indexOf(const std::function<bool(const T&)>& _callback, const u32 _from = 0) const;

        /**
         * @brief Find index of a value with offset of from with custom comparison function.
         *
         * @tparam T2
         * @param _callback
         * @param _what
         * @param _from
         * @return index of value. notFound if nothing found.
         */
        template<typename T2>
        u32 indexOf(const std::function<bool(const T&, const T2&)>& _callback , const T2& _what, const u32 _from = 0) const;

        /**
         * @brief Insert new item in specifed index.
         *
         * @param _index
         * @param _item
         * @return Self
         */
        List<T>& insert(const u32& _index, const T& _item);
        List<T>& insert(const u32& _index, T&& _item);

        /**
         * @brief Insert multiple items in specifed index.
         *
         * @param _index
         * @param _items
         * @return Self
         */
        FORCE_INLINE List<T>& insert(const u32& _index, const List<T>& _items);
        FORCE_INLINE List<T>& insert(const u32& _index, const std::initializer_list<T>& _items);
        List<T>& insert(const u32& _index, const T* _items, const u32& _size);

        /**
         * @brief Check list is empty.
         */
        FORCE_INLINE bool isEmpty() const;

        /**
         * @brief Check list is not empty.
         */
        FORCE_INLINE bool isNotEmpty() const;

        /**
         * @brief Get last item.
         */
        FORCE_INLINE T& last();
        FORCE_INLINE T last() const;

        /**
         * @brief Find index of a value with offset of from but in reversed order.
         *
         * @param _what
         * @param _from
         * @return index of value. notFound if nothing found.
         */
        u32 lastIndexOf(const T& _what, const u32 _from = u32Info::max) const;

        /**
         * @brief Find index of a value with offset of from with custom a callback but in reversed order.
         *
         * @param _callback
         * @param _from
         * @return index of value. notFound if nothing found.
         */
        u32 lastIndexOf(const std::function<bool(const T&)>& _callback, const u32 _from = u32Info::max) const;

        /**
         * @brief Find index of a value with offset of from with custom comparison function but in reversed order.
         *
         * @tparam T2
         * @param _callback
         * @param _what
         * @param _from
         * @return index of value. notFound if nothing found.
         */
        template<typename T2>
        u32 lastIndexOf(const std::function<bool(const T&, const T2&)>& _callback , const T2& _what, const u32 _from = u32Info::max) const;

        /**
         * @brief Get last item value then remove it.
         *
         * @return Last Item Value
         */
        FORCE_INLINE T popBack();

        /**
         * @brief Get first item value then remove it.
         *
         * @return First Item Value
         */
        FORCE_INLINE T popFront();

        /**
         * @brief Add new item to end of list.
         *
         * @param _item
         * @return Self
         */
        FORCE_INLINE List<T>& pushBack(const T& _item);
        FORCE_INLINE List<T>& pushBack(T&& _item);

        /**
         * @brief Add new item to begin of list.
         *
         * @param _item
         * @return Self
         */
        FORCE_INLINE List<T>& pushFront(const T& _item);
        FORCE_INLINE List<T>& pushFront(T&& _item);

        /**
         * @brief Remove items from list.
         *
         * @param _index
         * @param _count
         * @return Self
         */
        List<T>& remove(const u32& _index, const u32& _count = 1);

        /**
         * @brief Reverse the list.
         *
         * @return Self
         */
        List<T>& reverse();

        /**
         * @brief Sort list.
         *
         * @param _direction
         * @return Self
         */
        List<T>& sort(const SortDirection& _direction = SortDirection::ascending);

        /**
         * @brief Sort list with a custom callback.
         *
         * @param _callback
         * @return Self
         */
        List<T>& sort(const std::function<bool(const T&, const T&)>& _callback);

        /**
         * @brief Swap two values at specific indexes.
         *
         * @param _index1
         * @param _index2
         * @return Self
         */
        FORCE_INLINE List<T>& swap(const u32& _index1, const u32& _index2);

        /**
         * @brief Swap values of this list with another list.
         *
         * @param _other
         * @return Self
         */
        FORCE_INLINE List<T>& swap(List<T>& _other);

        /**
         * @brief Get value of specific index and then remove it.
         *
         * @param _index
         */
        T take(const u32& _index);

        /**
         * @brief Get values as string.
         *
         * @return String
         */
        String toString() const;

        /**
         * @brief Make each item unique and remove duplicates.
         *
         * @param _what
         * @return Self
         */
        List<T>& unique();

        /**
         * @brief Make each item unique and remove duplicates.
         *
         * @param _callback
         * @return Self
         */
        List<T>& unique(const std::function<bool(const T&, const T&)>& _callback);

        FORCE_INLINE List<T>& operator = (const std::initializer_list<T>& _array);
        FORCE_INLINE List<T>& operator = (const List<T>& _other);
        List<T>& operator = (List<T>&& _other);

        FORCE_INLINE T& operator [] (const u32& _index);
        FORCE_INLINE T operator [] (const u32& _index) const;

        template<typename T2>
        bool operator == (const List<T2>& _other) const;

        template<typename T2>
        FORCE_INLINE bool operator != (const List<T2>& _other) const;

        FORCE_INLINE List<T>& operator += (const List<T>& _other);
        FORCE_INLINE List<T> operator + (const List<T>& _other) const;

        /**
         * @brief Same push back.
         * @sa pushBack
         *
         * @param _item
         * @return Self
         */
        FORCE_INLINE List<T>& operator << (const T& _item);
        FORCE_INLINE List<T>& operator << (T&& _item);

    protected:
        /**
         * @brief Find element at specific index.
         *
         * @param _index
         * @return Element*
         */
        Element* findElement(const u32& _index) const;

    public:
        /**
         * @brief Not found index for search functions.
         */
        static const u32 notFound = u32Info::max;

    protected:
        Element*         mFirst = nullptr;
        Element*         mLast = nullptr;
        u32              mSize = 0;
    };
}

#include "List.inl"

#endif // __LIST_H__
