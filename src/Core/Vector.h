#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Defines.h"
#include <initializer_list>

namespace Michka
{
    template<typename T>
    class MICHKA_API Vector
    {
    public:
        FORCE_INLINE Vector();
        FORCE_INLINE Vector(const std::initializer_list<T>& _array);
        FORCE_INLINE Vector(const Vector<T>& _other);
        FORCE_INLINE Vector(Vector<T>&& _other);
        FORCE_INLINE ~Vector();

        /**
         * \brief Clear vector.
         *
         * \return Self
         */
        FORCE_INLINE Vector<T>& clear();

        /**
         * \brief Get count of items in vector.
         */
        FORCE_INLINE u32 getSize() const;

        /**
         * \brief Get capacity of vector.
         */
        FORCE_INLINE u32 getCapacity() const;

        /**
         * \brief Insert new item in specifed index.
         *
         * \param _index
         * \param _item
         * \return Self
         */
        Vector<T>& insert(const u32& _index, const T& _item);
        Vector<T>& insert(const u32& _index, T&& _item);

        /**
         * \brief Insert multiple items in specifed index.
         *
         * \param _index
         * \param _item
         * \return Self
         */
        FORCE_INLINE Vector<T>& insert(const u32& _index, const Vector<T>& _items);
        FORCE_INLINE Vector<T>& insert(const u32& _index, const std::initializer_list<T>& _items);
        Vector<T>& insert(const u32& _index, const T* _items, const u32& _size);

        /**
         * \brief Add new item to end of vector.
         *
         * \param _item
         * \return Self
         */
        FORCE_INLINE Vector<T>& pushBack(const T& _item);
        FORCE_INLINE Vector<T>& pushBack(T&& _item);

        /**
         * \brief Add new item to begin of vector.
         *
         * \param _item
         * \return Self
         */
        FORCE_INLINE Vector<T>& pushFront(const T& _item);
        FORCE_INLINE Vector<T>& pushFront(T&& _item);

        /**
         * \brief Resize capacity of vector.
         *
         * \return Self
         */
        Vector<T>& resize(const u32& _newCapacity);

        FORCE_INLINE Vector<T>& operator = (const std::initializer_list<T>& _array);
        FORCE_INLINE Vector<T>& operator = (const Vector<T>& _other);
        Vector<T>& operator = (Vector<T>&& _other);

		FORCE_INLINE T& operator[] (const u32& _index);
		FORCE_INLINE T operator[] (const u32& _index) const;
    protected:
        T* mData = nullptr;
        u32 mSize = 0;
        u32 mCapacity = 0;
        static const u32 capacityStep = 8;
    };
}

#include "Vector.inl"

#endif // __VECTOR_H__
