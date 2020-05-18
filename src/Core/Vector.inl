#include "Vector.h"
#include "Memory.h"

namespace Michka
{
    template<typename T>
    FORCE_INLINE Vector<T>::Vector()
    {
    }

    template<typename T>
    FORCE_INLINE Vector<T>::Vector(const std::initializer_list<T>& _array)
    {
        insert(0, _array.begin(), u32(_array.size()));
    }

    template<typename T>
    FORCE_INLINE Vector<T>::Vector(const Vector<T>& _other)
    {
        insert(0, _other.mData, _other.mSize);
    }

    template<typename T>
    FORCE_INLINE Vector<T>::Vector(Vector<T>&& _other)
    {
        *this = std::move(_other);
    }

    template<typename T>
    FORCE_INLINE Vector<T>::~Vector()
    {
        clear();
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::clear()
    {
        if (mData)
        {
            if constexpr (Type<T>::isClass)
            {
                for (register u32 i = 0; i < mSize; i++)
                {
                    mData[i].~T();
                }
            }
            Memory.free(mData);
            mData = nullptr;
        }
        mSize = 0;
        mCapacity = 0;
        return *this;
    }

    template<typename T>
    FORCE_INLINE u32 Vector<T>::getSize() const
    {
        return mSize;
    }

    template<typename T>
    FORCE_INLINE u32 Vector<T>::getCapacity() const
    {
        return mCapacity;
    }

    template<typename T>
    Vector<T>& Vector<T>::insert(const u32& _index, const T& _item)
    {
        if (mSize + 1 >= mCapacity)
        {
            resize(mCapacity + capacityStep);
        }
        memcpy((void*)(mData + _index + 1), (void*)(mData + _index), (mSize - _index) * sizeof(T));
        if constexpr (Type<T>::isClass)
        {
            new(mData + _index) T(_item);
        }
        else
        {
            mData[_index] = _item;
        }
        mSize++;
        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::insert(const u32& _index, T&& _item)
    {
        if (mSize + 1 >= mCapacity)
        {
            resize(mCapacity + capacityStep);
        }
        memcpy((void*)(mData + _index + 1), (void*)(mData + _index), (mSize - _index) * sizeof(T));
        if constexpr (Type<T>::isClass)
        {
#           undef new
            new(mData + _index) T(std::move(_item));
#           define new MICHKA_NEW
        }
        else
        {
            mData[_index] = std::move(_item);
        }
        mSize++;
        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::insert(const u32& _index, const Vector<T>& _items)
    {
        return insert(_index, _items.mData, _items.getSize());
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::insert(const u32& _index, const std::initializer_list<T>& _items)
    {
        return insert(_index, _items.begin(), u32(_items.size()));
    }

    template<typename T>
    Vector<T>& Vector<T>::insert(const u32& _index, const T* _items, const u32& _size)
    {
        if (mSize + _size >= mCapacity)
        {
            resize(mCapacity + max(capacityStep, _size));
        }
        memcpy((void*)(mData + _index + _size), (void*)(mData + _index), (mSize - _index) * sizeof(T));
        if constexpr (Type<T>::isClass)
        {
            for (u32 i = 0; i < _size; i++)
            {
#               undef new
                new(mData + _index + i) T(_items[i]);
#               define new MICHKA_NEW
            }
        }
        else
        {
            memcpy((void*)(mData + _index), (void*)_items, _size * sizeof(T));
        }
        mSize += _size;
        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::pushBack(const T& _item)
    {
        return insert(getSize(), _item);
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::pushBack(T&& _item)
    {
        return insert(getSize(), std::move(_item));
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::pushFront(const T& _item)
    {
        return insert(0, _item);
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::pushFront(T&& _item)
    {
        return insert(0, std::move(_item));
    }

    template<typename T>
    Vector<T>& Vector<T>::resize(const u32& _newCapacity)
    {
        if (_newCapacity != mCapacity)
        {
            T* old = mData;
            u32 oldSize = mSize;
            u32 newCapacity = ((_newCapacity / capacityStep) + (_newCapacity % capacityStep > 0 ? 1 : 0)) * capacityStep;
            mData = static_cast<T*>(Memory.malloc(newCapacity * sizeof(T)));
            mCapacity = _newCapacity;
            mSize = min(mSize, mCapacity);
            if (old)
            {
                u32 oldSizeLimited = min(oldSize, mSize);
                memcpy((void*)mData, (void*)old, oldSizeLimited * sizeof(T));
                Memory.free(old);
            }
        }
        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::operator = (const std::initializer_list<T>& _array)
    {
        clear();
        insert(0, _array.begin(), u32(_array.size()));
        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::operator = (const Vector<T>& _other)
    {
        clear();
        insert(0, _other.mData, _other.getSize());
        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::operator = (Vector<T>&& _other)
    {
        clear();
        mData = _other.mData;
        mSize = _other.mSize;
        mCapacity = _other.mCapacity;
        _other.mData = nullptr;
        _other.mSize = 0;
        _other.mCapacity = 0;
        return *this;
    }

    template<typename T>
    FORCE_INLINE T Vector<T>::operator[] (const u32& _index) const
    {
        return mData[_index];
    }

    template<typename T>
    FORCE_INLINE T& Vector<T>::operator[] (const u32& _index)
    {
        return mData[_index];
    }
}
