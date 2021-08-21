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

#include "List.h"
#include "Core/Container/String.h"
#include "Core/Memory/Memory.h"
#include "Core/Helpers.h"
#include "Vector.h"

namespace Michka
{
    /* --------------------------------- Element -------------------------------- */

    template<typename T>
    FORCE_INLINE List<T>::Element::Element(const T& _val):
        value(_val)
    {
        //
    }

    template<typename T>
    FORCE_INLINE List<T>::Element::Element(T&& _val):
        value(std::forward<T>(_val))
    {
        //
    }

    /* ----------------------------- Const Iterator ----------------------------- */

    template<typename T>
    FORCE_INLINE List<T>::ConstIterator::ConstIterator()
    {
        //
    }

    template<typename T>
    FORCE_INLINE List<T>::ConstIterator::ConstIterator(typename List<T>::Element* _element)
    {
        mElement = _element;
    }

    template<typename T>
    FORCE_INLINE typename List<T>::ConstIterator List<T>::ConstIterator::operator + (const i32& _number) const
    {
        ConstIterator out(mElement);
        for (i32 i = 0; i < _number; i++)
        {
            out.mElement = out.mElement->next;
        }

        return out;
    }

    template<typename T>
    FORCE_INLINE typename List<T>::ConstIterator List<T>::ConstIterator::operator - (const i32& _number) const
    {
        ConstIterator out(mElement);
        for (i32 i = 0; i < _number; i++)
        {
            out.mElement = out.mElement->prev;
        }

        return out;
    }

    template<typename T>
    FORCE_INLINE const T& List<T>::ConstIterator::operator * () const
    {
        return mElement->value;
    }

    template<typename T>
    FORCE_INLINE const T*  List<T>::ConstIterator::operator -> () const
    {
        return &(mElement->value);
    }

    template<typename T>
    FORCE_INLINE const T& List<T>::ConstIterator::operator [] (const i32& _number) const
    {
        return ((*this) + _number).mElement->value;
    }

    template<typename T>
    FORCE_INLINE List<T>::ConstIterator::operator bool () const
    {
        return mElement != nullptr;
    }

    template<typename T>
    FORCE_INLINE bool List<T>::ConstIterator::operator ! () const
    {
        return mElement == nullptr;
    }

    template<typename T>
    FORCE_INLINE typename List<T>::ConstIterator& List<T>::ConstIterator::operator ++ ()
    {
        mElement = mElement->next;
        return *this;
    }

    template<typename T>
    FORCE_INLINE typename List<T>::ConstIterator& List<T>::ConstIterator::operator -- ()
    {
        mElement = mElement->prev;
        return *this;
    }

    template<typename T>
    FORCE_INLINE bool List<T>::ConstIterator::operator == (const ConstIterator& _other) const
    {
        return mElement == _other.mElement;
    }

    template<typename T>
    FORCE_INLINE bool List<T>::ConstIterator::operator != (const ConstIterator& _other) const
    {
        return mElement != _other.mElement;
    }

    template<typename T>
    FORCE_INLINE T List<T>::ConstIterator::operator [] (const u32& _index) const
    {
        Element* element = mElement;
        for (u32 i = 0; i < _index; i++)
        {
            element = element->next;
        }

        return element->value;
    }

    /* -------------------------------- Iterator -------------------------------- */

    template<typename T>
    List<T>::Iterator::Iterator()
        : ConstIterator()
    {
        //
    }

    template<typename T>
    FORCE_INLINE List<T>::Iterator::Iterator(typename List<T>::Element* _element)
        : ConstIterator(_element)
    {
        //
    }

    template<typename T>
    FORCE_INLINE T& List<T>::Iterator::operator * ()
    {
        return mElement->value;
    }

    template<typename T>
    FORCE_INLINE T* List<T>::Iterator::operator -> ()
    {
        return &(mElement->value);
    }

    template<typename T>
    FORCE_INLINE T& List<T>::Iterator::operator [] (const u32& _index)
    {
        Element* element = mElement;
        for (u32 i = 0; i < _index; i++)
        {
            element = element->next;
        }

        return element->value;
    }

    /* ---------------------------------- List ---------------------------------- */

    template<typename T>
    FORCE_INLINE List<T>::List()
    {
        //
    }

    template<typename T>
    FORCE_INLINE List<T>::List(const std::initializer_list<T>& _array)
    {
        *this = _array;
    }

    template<typename T>
    FORCE_INLINE List<T>::List(const List<T>& _other)
    {
        *this = _other;
    }

    template<typename T>
    FORCE_INLINE List<T>::List(List<T>&& _other)
    {
        *this = std::forward<List<T>>(_other);
    }

    template<typename T>
    FORCE_INLINE List<T>::~List()
    {
        clear();
    }

    template<typename T>
    FORCE_INLINE typename List<T>::Iterator List<T>::begin()
    {
        return Iterator(mFirst);
    }

    template<typename T>
    FORCE_INLINE typename List<T>::ConstIterator List<T>::begin() const
    {
        return ConstIterator(mFirst);
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::clear()
    {
        Element* element = mFirst;
        Element* nextElement = nullptr;
        while(element)
        {
            nextElement = element->next;
            delete element;
            element = nextElement;
        }
        mFirst = nullptr;
        mLast = nullptr;
        mSize = 0;
        return *this;
    }

    template<typename T>
    FORCE_INLINE typename List<T>::Iterator List<T>::end()
    {
        return nullptr;
    }

    template<typename T>
    FORCE_INLINE typename List<T>::ConstIterator List<T>::end() const
    {
        return nullptr;
    }

    template<typename T>
    List<T>& List<T>::filter(const std::function<bool(const T&)>& _callback)
    {
        *this = getFiltered(_callback);

        return *this;
    }

    template<typename T>
    FORCE_INLINE T& List<T>::first()
    {
        return mFirst->value;
    }

    template<typename T>
    FORCE_INLINE T List<T>::first() const
    {
        return mFirst->value;
    }

    template<typename T>
    FORCE_INLINE u32 List<T>::getSize() const
    {
        return mSize;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::getFiltered(const std::function<bool(const T&)>& _callback) const
    {
        Vector<u32> indexes;
        indexes.resize(mSize);
        for (u32 i = 0; i < mSize; i++)
        {
            if (_callback(findElement(i)->value))
            {
                indexes.pushBack(i);
            }
        }
        List<T> out;
        for (auto i : indexes)
        {
            out.pushBack(findElement(i)->value);
        }

        return out;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::getReversed() const
    {
        List<T> out = *this;
        out.reverse();

        return out;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::getSorted(const SortDirection& _direction) const
    {
        List<T> out = *this;
        out.sort(_direction);

        return out;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::getSorted(const std::function<bool(const T&, const T&)>& _callback) const
    {
        List<T> out = *this;
        out.sort(_callback);

        return out;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::getUnique()
    {
        List<T> out = *this;
        out.unique();

        return out;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::getUnique(const std::function<bool(const T&, const T&)>& _callback)
    {
        List<T> out = *this;
        out.unique(_callback);

        return out;
    }

    template<typename T>
    u32 List<T>::indexOf(const T& _what, const u32 _from) const
    {
        static_assert(Type<T>::hasOperator<>::equal, "Your type does not have operator \'==\' to comparison");

        for (u32 i = _from; i < mSize; i++)
        {
            if (findElement(i)->value == _what)
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    u32 List<T>::indexOf(const std::function<bool(const T&)>& _callback, const u32 _from) const
    {
        for (u32 i = _from; i < mSize; i++)
        {
            if (_callback(findElement(i)->value))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    template<typename T2>
    u32 List<T>::indexOf(const std::function<bool(const T&, const T2&)>& _callback , const T2& _what, const u32 _from) const
    {
        for (u32 i = _from; i < mSize; i++)
        {
            if (_callback(findElement(i)->value, _what))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    List<T>& List<T>::insert(const u32& _index, const T& _item)
    {
        Element* newElement = new Element(_item);
        if (_index == 0)
        {
            newElement->next = mFirst;
            mFirst = newElement;
            if (newElement->next)
            {
                newElement->next->prev = newElement;
            }
            if (mLast == nullptr)
            {
                mLast = mFirst;
            }
        }
        else if (_index == mSize)
        {
            newElement->prev = mLast;
            mLast = newElement;
            newElement->prev->next = newElement;
        }
        else
        {
            Element* elementAtIndex = findElement(_index);
            newElement->prev = elementAtIndex->prev;
            newElement->next = elementAtIndex;
            newElement->prev->next = newElement;
            newElement->next->prev = newElement;
        }
        mSize++;

        return *this;
    }

    template<typename T>
    List<T>& List<T>::insert(const u32& _index, T&& _item)
    {
        Element* newElement = new Element(std::forward<T>(_item));
        if (_index == 0)
        {
            newElement->next = mFirst;
            mFirst = newElement;
            if (newElement->next)
            {
                newElement->next->prev = newElement;
            }
            if (mLast == nullptr)
            {
                mLast = mFirst;
            }
        }
        else if (_index == mSize)
        {
            newElement->prev = mLast;
            mLast = newElement;
            newElement->prev->next = newElement;
        }
        else
        {
            Element* elementAtIndex = findElement(_index);
            newElement->prev = elementAtIndex->prev;
            newElement->next = elementAtIndex;
            newElement->prev->next = newElement;
            newElement->next->prev = newElement;
        }
        mSize++;

        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::insert(const u32& _index, const List<T>& _items)
    {
        for (u32 i = 0; i < _items.getSize(); i++)
        {
            insert(_index + i, _items[i]);
        }

        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::insert(const u32& _index, const std::initializer_list<T>& _items)
    {
        return insert(_index, _items.begin(), u32(_items.size()));
    }

    template<typename T>
    List<T>& List<T>::insert(const u32& _index, const T* _items, const u32& _size)
    {
        for (u32 i = 0; i < _size; i++)
        {
            insert(_index + i, _items[i]);
        }

        return *this;
    }

    template<typename T>
    FORCE_INLINE bool List<T>::isEmpty() const
    {
        return mSize == 0;
    }

    template<typename T>
    FORCE_INLINE bool List<T>::isNotEmpty() const
    {
        return mSize != 0;
    }

    template<typename T>
    String List<T>::join(const String& _seperator) const
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
    FORCE_INLINE T& List<T>::last()
    {
        return mLast->value;
    }

    template<typename T>
    FORCE_INLINE T List<T>::last() const
    {
        return mLast->value;
    }

    template<typename T>
    u32 List<T>::lastIndexOf(const T& _what, const u32 _from) const
    {
        static_assert(Type<T>::hasOperator<>::equal, "Your type does not have operator \'==\' to comparison");

        for (u32 i = min(_from, mSize - 1); i < mSize; i--)
        {
            if (findElement(i)->value == _what)
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    u32 List<T>::lastIndexOf(const std::function<bool(const T&)>& _callback, const u32 _from) const
    {
        for (u32 i = min(_from, mSize - 1); i < mSize; i--)
        {
            if (_callback(findElement(i)->value))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    template<typename T2>
    u32 List<T>::lastIndexOf(const std::function<bool(const T&, const T2&)>& _callback , const T2& _what, const u32 _from) const
    {
        for (u32 i = min(_from, mSize - 1); i < mSize; i--)
        {
            if (_callback(findElement(i)->value, _what))
            {
                return i;
            }
        }

        return notFound;
    }

    template<typename T>
    FORCE_INLINE T List<T>::popBack()
    {
        return take(mSize - 1);
    }

    template<typename T>
    FORCE_INLINE T List<T>::popFront()
    {
        return take(0);
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::pushBack(const T& _item)
    {
        return insert(getSize(), _item);
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::pushBack(T&& _item)
    {
        return insert(getSize(), std::move(_item));
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::pushFront(const T& _item)
    {
        return insert(0, _item);
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::pushFront(T&& _item)
    {
        return insert(0, std::forward<T>(_item));
    }

    template<typename T>
    List<T>& List<T>::remove(const u32& _index, const u32& _count)
    {
        if (_count > 0 && _index < mSize)
        {
            u32 count = min(mSize - _index, _count);
            Element* removeStart = findElement(_index);
            Element* removeEnd = findElement(_index + count);
            Element* nextElement = nullptr;
            if (removeStart->prev)
            {
                removeStart->prev->next = removeEnd;
            }
            else
            {
                mFirst = removeEnd;
            }
            if (removeEnd)
            {
                removeEnd->prev = removeStart->prev;
            }
            else
            {
                mLast = removeStart->prev;
            }
            while (removeStart != removeEnd)
            {
                nextElement = removeStart->next;
                delete removeStart;
                removeStart = nextElement;
            }
            mSize -= count;
        }

        return *this;
    }

    template<typename T>
    List<T>& List<T>::reverse()
    {
        Element* element = mFirst;
        while (element)
        {
            Michka::swap(element->prev, element->next);
            element = element->prev;
        }
        Michka::swap(mFirst, mLast);

        return *this;
    }

    template<typename T>
    List<T>& List<T>::sort(const SortDirection& _direction)
    {
        Michka::sort<List<T>::Iterator, T>(begin(), mSize, _direction);

        return *this;
    }

    template<typename T>
    List<T>& List<T>::sort(const std::function<bool(const T&, const T&)>& _callback)
    {
        Michka::sort<List<T>::Iterator, T>(begin(), mSize, _callback);

        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::swap(const u32& _index1, const u32& _index2)
    {
        if (_index1 != _index2)
        {
            Element* first = findElement(_index1);
            Element* second = findElement(_index2);
            Michka::swap(first->value, second->value);
        }

        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::swap(List<T>& _other)
    {
        Michka::swap(mFirst, _other.mFirst);
        Michka::swap(mLast, _other.mLast);
        Michka::swap(mSize, _other.mSize);

        return *this;
    }

    template<typename T>
    T List<T>::take(const u32& _index)
    {
        Element* element = findElement(_index);
        T value = std::move(element->value);
        remove(_index);

        return value;
    }

    template<typename T>
    String List<T>::toString() const
    {
        String out = join();
        if (out.isEmpty())
        {
            out = "List(size=" + String::number(mSize) + ")";
        }
        else
        {
            out = "List{" + out + "}";
        }
        return out;
    }

    template<typename T>
    List<T>& List<T>::unique()
    {
        u32 index = notFound;
        for (u32 i = 0; i < getSize(); i++)
        {
            while ((index = indexOf((*this)[i], i + 1)) != notFound)
            {
                remove(index);
            }
        }

        return *this;
    }

    template<typename T>
    List<T>& List<T>::unique(const std::function<bool(const T&, const T&)>& _callback)
    {
        u32 index = notFound;
        for (u32 i = 0; i < getSize(); i++)
        {
            while ((index = indexOf(_callback, (*this)[i], i + 1)) != notFound)
            {
                remove(index);
            }
        }

        return *this;
    }

    template<typename T>
    typename List<T>::Element* List<T>::findElement(const u32& _index) const
    {
        Element* element = mFirst;
        for (u32 i = 0; i < _index; i++)
        {
            element = element->next;
        }
        return element;
    }


    template<typename T>
    template<typename T2>
    bool List<T>::operator == (const List<T2>& _other) const
    {
        if (mSize != _other.mSize)
        {
            return false;
        }
        for (u32 i = 0; i < mSize; i++)
        {
            if (findElement(i)->value != _other.findElement(i)->value)
            {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    template<typename T2>
    FORCE_INLINE bool List<T>::operator != (const List<T2>& _other) const
    {
        return !(*this == _other);
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::operator += (const List<T>& _other)
    {
        u32 size = mSize;
        insert(size, _other);

        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T> List<T>::operator + (const List<T>& _other) const
    {
        List<T> temp = *this;
        temp += _other;

        return temp;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::operator = (const std::initializer_list<T>& _array)
    {
        clear();
        insert(0, _array);

        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::operator = (const List<T>& _other)
    {
        clear();
        insert(0, _other);

        return *this;
    }

    template<typename T>
    List<T>& List<T>::operator = (List<T>&& _other)
    {
        clear();
        Michka::swap(mFirst, _other.mFirst);
        Michka::swap(mLast, _other.mLast);
        Michka::swap(mSize, _other.mSize);
        return *this;
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::operator << (const T& _item)
    {
        return pushBack(_item);
    }

    template<typename T>
    FORCE_INLINE List<T>& List<T>::operator << (T&& _item)
    {
        return pushBack(std::forward<T>(_item));
    }

    template<typename T>
    FORCE_INLINE T List<T>::operator [] (const u32& _index) const
    {
        return findElement(_index)->value;
    }

    template<typename T>
    FORCE_INLINE T& List<T>::operator [] (const u32& _index)
    {
        return findElement(_index)->value;
    }
}
