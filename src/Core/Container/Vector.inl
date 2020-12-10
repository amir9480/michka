// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
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

#include "Vector.h"
#include "Core/Memory/Memory.h"
#include "Core/Helpers.h"

namespace Michka
{
    template<typename T>
    FORCE_INLINE Vector<T>::Vector()
    {
        //
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
    FORCE_INLINE typename Vector<T>::Iterator Vector<T>::begin()
    {
        return mData;
    }

    template<typename T>
    FORCE_INLINE typename Vector<T>::ConstIterator Vector<T>::begin() const
    {
        return mData;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::clear()
    {
        if (mData)
        {
            if constexpr (Type<T>::isClass && Type<T>::hasDestructor)
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
    FORCE_INLINE typename Vector<T>::Iterator Vector<T>::end()
    {
        return (mData + mSize);
    }

    template<typename T>
    FORCE_INLINE typename Vector<T>::ConstIterator Vector<T>::end() const
    {
        return (mData + mSize);
    }

    template<typename T>
    Vector<T>& Vector<T>::filter(const std::function<bool(const T&)>& _callback)
    {
        *this = getFiltered(_callback);

        return *this;
    }

    template<typename T>
    FORCE_INLINE T& Vector<T>::first()
    {
        return *begin();
    }

    template<typename T>
    FORCE_INLINE T Vector<T>::first() const
    {
        return *begin();
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
    FORCE_INLINE Vector<T> Vector<T>::getFiltered(const std::function<bool(const T&)>& _callback) const
    {
        Vector<u32> indexes;
        indexes.resize(mSize);
        for (u32 i = 0; i < mSize; i++)
        {
            if (_callback(mData[i]))
            {
                indexes.pushBack(i);
            }
        }
        Vector<T> out;
        out.resize(indexes.getSize());
        for (auto i : indexes)
        {
            out.pushBack(mData[i]);
        }

        return out;
    }

    template<typename T>
    FORCE_INLINE Vector<T> Vector<T>::getReversed() const
    {
        Vector<T> out = *this;
        out.reverse();

        return out;
    }

    template<typename T>
    FORCE_INLINE Vector<T> Vector<T>::getSorted(const SortDirection& _direction) const
    {
        Vector<T> out = *this;
        out.sort(_direction);

        return out;
    }

    template<typename T>
    FORCE_INLINE Vector<T> Vector<T>::getSorted(const std::function<bool(const T&, const T&)>& _callback) const
    {
        Vector<T> out = *this;
        out.sort(_callback);

        return out;
    }

    template<typename T>
    String Vector<T>::implode(const String& _seperator) const
    {
        String out;
        if constexpr (HasToString<Type<T>::RemovedPointerType>::value)
        {
            for (auto element : *this)
            {
                if constexpr (Type<T>::isPointer)
                {
                    out += _seperator + element->toString();
                }
                else
                {
                    out += _seperator + element.toString();
                }
            }
        }
        else if constexpr (Type<T>::isNumeric)
        {
            for (auto element : *this)
            {
                out += _seperator + String::number(element);
            }
        }
        else if constexpr (Type<T>::is<String>() || Type<T>::is<String8>() || Type<T>::is<String32>())
        {
            for (auto element : *this)
            {
                out += _seperator + element;
            }
        }

        return out.getTrimed(_seperator);
    }

    template<typename T>
    u32 Vector<T>::indexOf(const T& _what, const u32 _from) const
    {
        static_assert(Type<T>::hasOperator<>::equal, "Your type does not have operator \'==\' to comparison");

        for (u32 i = _from; i < mSize; i++)
        {
            if (mData[i] == _what)
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    u32 Vector<T>::indexOf(const std::function<bool(const T&)>& _callback, const u32 _from) const
    {
        for (u32 i = _from; i < mSize; i++)
        {
            if (_callback(mData[i]))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    template<typename T2>
    u32 Vector<T>::indexOf(const std::function<bool(const T&, const T2&)>& _callback , const T2& _what, const u32 _from) const
    {
        for (u32 i = _from; i < mSize; i++)
        {
            if (_callback(mData[i], _what))
            {
                return i;
            }
        }

        return notFound;
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
#           undef new
            new(mData + _index) T(_item);
#           define new MICHKA_NEW
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
    FORCE_INLINE bool Vector<T>::isEmpty() const
    {
        return mSize == 0;
    }

    template<typename T>
    FORCE_INLINE bool Vector<T>::isNotEmpty() const
    {
        return mSize != 0;
    }

    template<typename T>
    FORCE_INLINE T& Vector<T>::last()
    {
        return *(end() - 1);
    }

    template<typename T>
    FORCE_INLINE T Vector<T>::last() const
    {
        return *(end() - 1);
    }

    template<typename T>
    u32 Vector<T>::lastIndexOf(const T& _what, const u32 _from) const
    {
        static_assert(Type<T>::hasOperator<>::equal, "Your type does not have operator \'==\' to comparison");

        for (u32 i = min(_from, mSize - 1); i < mSize; i--)
        {
            if (mData[i] == _what)
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    u32 Vector<T>::lastIndexOf(const std::function<bool(const T&)>& _callback, const u32 _from) const
    {
        for (u32 i = min(_from, mSize - 1); i < mSize; i--)
        {
            if (_callback(mData[i]))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    template<typename T2>
    u32 Vector<T>::lastIndexOf(const std::function<bool(const T&, const T2&)>& _callback , const T2& _what, const u32 _from) const
    {
        for (u32 i = min(_from, mSize - 1); i < mSize; i--)
        {
            if (_callback(mData[i], _what))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    FORCE_INLINE T Vector<T>::popBack()
    {
        return take(mSize - 1);
    }

    template<typename T>
    FORCE_INLINE T Vector<T>::popFront()
    {
        return take(0);
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
    Vector<T>& Vector<T>::remove(const u32& _index, const u32& _count)
    {
        if (_count > 0 && _index < mSize)
        {
            u32 count = min(mSize - _index, _count);
            for (u32 i = _index; i < mSize - count; i++)
            {
                mData[i] = std::move(mData[i + count]);
            }
            for (u32 i = mSize - count; i < mSize; i++)
            {
                mData[i].~T();
            }
            mSize -= count;
        }

        return *this;
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
            mCapacity = ((_newCapacity / capacityStep) + (_newCapacity % capacityStep > 0 ? 1 : 0)) * capacityStep;
            if (mData)
            {
                mData = static_cast<T*>(Memory.realloc(mData, mCapacity * sizeof(T)));
            }
            else
            {
                mData = static_cast<T*>(Memory.malloc(mCapacity * sizeof(T)));
            }
            mSize = min(mSize, mCapacity);
        }

        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::reverse()
    {
        u32 mSizeOnTwo = mSize/2;
        for (u32 i = 0; i < mSizeOnTwo; i++)
        {
            Michka::swap(mData[i], mData[(mSize - 1) - i]);
        }

        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::sort(const SortDirection& _direction)
    {
        Michka::sort(mData, mSize, _direction);

        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::sort(const std::function<bool(const T&, const T&)>& _callback)
    {
        Michka::sort(mData, mSize, _callback);

        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::swap(const u32& _index1, const u32& _index2)
    {
        Michka::swap(mData[_index1], mData[_index2]);

        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::swap(Vector<T>& _other)
    {
        Michka::swap(mData, _other.mData);
        Michka::swap(mSize, _other.mSize);
        Michka::swap(mCapacity, _other.mCapacity);

        return *this;
    }

    template<typename T>
    T Vector<T>::take(const u32& _index)
    {
        T value = std::move(mData[_index]);
        remove(_index);

        return value;
    }

    template<typename T>
    String Vector<T>::toString() const
    {
        String out = implode();
        if (out.isEmpty())
        {
            out = "Vector(size=" + String::number(mSize) + ")";
        }
        else
        {
            out = "Vector{" + out + "}";
        }
        return out;
    }

    template<typename T>
    template<typename T2>
    bool Vector<T>::operator == (const Vector<T2>& _other) const
    {
        if (mSize != _other.mSize)
        {
            return false;
        }
        for (u32 i = 0; i < mSize; i++)
        {
            if (mData[i] != _other.mData[i])
            {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    template<typename T2>
    FORCE_INLINE bool Vector<T>::operator != (const Vector<T2>& _other) const
    {
        return !(*this == _other);
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::operator += (const Vector<T>& _other)
    {
        insert(mSize, _other);

        return *this;
    }

    template<typename T>
    FORCE_INLINE Vector<T> Vector<T>::operator + (const Vector<T>& _other) const
    {
        Vector<T> temp = *this;
        temp += _other;

        return temp;
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
    FORCE_INLINE T Vector<T>::operator [] (const u32& _index) const
    {
        return mData[_index];
    }

    template<typename T>
    FORCE_INLINE T& Vector<T>::operator [] (const u32& _index)
    {
        return mData[_index];
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::operator << (const T& _item)
    {
        return pushBack(_item);
    }

    template<typename T>
    FORCE_INLINE Vector<T>& Vector<T>::operator << (T&& _item)
    {
        return pushBack(std::forward<T>(_item));
    }
}
