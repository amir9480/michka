#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Core/Defines.h"
#include "Core/Helpers.h"
#include <initializer_list>

namespace Michka
{
    template<typename T>
    class MICHKA_API Vector
    {
    public:
        typedef T* Iterator;
        typedef const T* ConstIterator;
    public:
        FORCE_INLINE Vector();
        FORCE_INLINE Vector(const std::initializer_list<T>& _array);
        FORCE_INLINE Vector(const Vector<T>& _other);
        FORCE_INLINE Vector(Vector<T>&& _other);
        FORCE_INLINE ~Vector();

        /**
         * @brief Iterator to begin of array.
         */
        FORCE_INLINE Iterator begin();

        /**
         * @brief Iterator to begin of array for constants.
         */
        FORCE_INLINE ConstIterator begin() const;

        /**
         * @brief Clear vector.
         *
         * @return Self
         */
        FORCE_INLINE Vector<T>& clear();

        /**
         * @brief Iterator to end of array.
         */
        FORCE_INLINE Iterator end();

        /**
         * @brief Iterator to end of array for constants.
         */
        FORCE_INLINE ConstIterator end() const;

        /**
         * @brief Filter vector items by a callback.
         *
         * @param _callback
         * @return Self
         */
        Vector<T>& filter(const std::function<bool(const T&)>& _callback);

        /**
         * @brief Get capacity of vector.
         */
        FORCE_INLINE u32 getCapacity() const;

        /**
         * @brief Get count of items in vector.
         */
        FORCE_INLINE u32 getSize() const;

        /**
         * @brief Get filtered vector by a compare callback.
         *
         * @param _callback
         * @return Filtered Vector
         */
        FORCE_INLINE Vector<T> getFiltered(const std::function<bool(const T&)>& _callback) const;

        /**
         * @brief Get reversed copy of the vector.
         *
         * @return Reversed Vector
         */
        FORCE_INLINE Vector<T> getReversed() const;

        /**
         * @brief Get sorted copy of this vector.
         *
         * @param _direction
         * @return Sorted Vector
         */
        FORCE_INLINE Vector<T> getSorted(const SortDirection& _direction = SortDirection::Ascending) const;

        /**
         * @brief Get sorted copy of this vector with custom callback.
         *
         * @param _callback
         * @return Sorted Vector
         */
        FORCE_INLINE Vector<T> getSorted(const std::function<bool(const T&, const T&)>& _callback) const;

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
        Vector<T>& insert(const u32& _index, const T& _item);
        Vector<T>& insert(const u32& _index, T&& _item);

        /**
         * @brief Insert multiple items in specifed index.
         *
         * @param _index
         * @param _items
         * @return Self
         */
        FORCE_INLINE Vector<T>& insert(const u32& _index, const Vector<T>& _items);
        FORCE_INLINE Vector<T>& insert(const u32& _index, const std::initializer_list<T>& _items);
        Vector<T>& insert(const u32& _index, const T* _items, const u32& _size);

		/**
		 * @brief Check vector is empty.
		 */
		FORCE_INLINE bool isEmpty() const;

		/**
		 * @brief Check vector is not empty.
		 */
		FORCE_INLINE bool isNotEmpty() const;

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
         * @brief Add new item to end of vector.
         *
         * @param _item
         * @return Self
         */
        FORCE_INLINE Vector<T>& pushBack(const T& _item);
        FORCE_INLINE Vector<T>& pushBack(T&& _item);

        /**
         * @brief Add new item to begin of vector.
         *
         * @param _item
         * @return Self
         */
        FORCE_INLINE Vector<T>& pushFront(const T& _item);
        FORCE_INLINE Vector<T>& pushFront(T&& _item);

        /**
         * @brief Remove items from vector.
         *
         * @param _index
         * @param _count
         * @return Self
         */
        Vector<T>& remove(const u32& _index, const u32& _count = 1);

        /**
         * @brief Resize capacity of vector.
         *
         * @return Self
         */
        Vector<T>& resize(const u32& _newCapacity);

        /**
         * @brief Reverse the vector.
         *
         * @return Self
         */
        Vector<T>& reverse();

        /**
         * @brief Sort vector.
         *
         * @param _direction
         * @return Self
         */
        Vector<T>& sort(const SortDirection& _direction = SortDirection::Ascending);

        /**
         * @brief Sort vector with a custom callback.
         *
         * @param _callback
         * @return Self
         */
        Vector<T>& sort(const std::function<bool(const T&, const T&)>& _callback);

        /**
         * @brief Swap two values at specific indexes.
         *
         * @param _index1
         * @param _index2
         * @return Self
         */
        FORCE_INLINE Vector<T>& swap(const u32& _index1, const u32& _index2);

        /**
         * @brief Swap values of this vector with another vector.
         *
         * @param _other
         * @return Self
         */
        FORCE_INLINE Vector<T>& swap(Vector<T>& _other);

        /**
         * @brief Get value of specific index and then remove it.
         *
         * @param _index
         */
        T take(const u32& _index);

        FORCE_INLINE Vector<T>& operator = (const std::initializer_list<T>& _array);
        FORCE_INLINE Vector<T>& operator = (const Vector<T>& _other);
        Vector<T>& operator = (Vector<T>&& _other);

		FORCE_INLINE T& operator [] (const u32& _index);
		FORCE_INLINE T operator [] (const u32& _index) const;

        template<typename T2>
        bool operator == (const Vector<T2>& _other) const;

        template<typename T2>
        FORCE_INLINE bool operator != (const Vector<T2>& _other) const;

        FORCE_INLINE Vector<T>& operator += (const Vector<T>& _other);
        FORCE_INLINE Vector<T> operator + (const Vector<T>& _other) const;

        /**
         * @brief Same push back.
         * @sa pushBack
         *
         * @param _item
         * @return Self
         */
        FORCE_INLINE Vector<T>& operator << (const T& _item);
        FORCE_INLINE Vector<T>& operator << (T&& _item);
    public:
		/**
		 * @brief Not found index for search functions.
		 */
		static const u32 notFound = u32Info::max;

    protected:
        T*               mData = nullptr;
        u32              mSize = 0;
        u32              mCapacity = 0;
        static const u32 capacityStep = 8;
    };
}

#include "Vector.inl"

#endif // __VECTOR_H__
