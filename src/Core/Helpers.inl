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

#include "Helpers.h"
#include "Defines.h"
#include "Reflection/Type.h"

namespace Michka
{
    namespace Private
    {
        template<typename T, typename ElementType>
        FORCE_INLINE int quickSortPartitionAscending(T _array, const i32& _low, const i32& _high)
        {
            ElementType pivot = _array[_high];
            i32 partitionIndex = (_low - 1);

            for (i32 i = _low; i < _high; i++)
            {
                if (_array[i] <= pivot)
                {
                    partitionIndex++;
                    swap(_array[partitionIndex], _array[i]);
                }
            }
            swap(_array[partitionIndex + 1], _array[_high]);

            return (partitionIndex + 1);
        }

        template<typename T, typename ElementType>
        void quickSortAscending(T _array, const i32& _low, const i32& _high)
        {
            if (_low < _high)
            {
                int partitionIndex = quickSortPartitionAscending<T, ElementType>(_array, _low, _high);
                quickSortAscending<T, ElementType>(_array, _low, partitionIndex - 1);
                quickSortAscending<T, ElementType>(_array, partitionIndex + 1, _high);
            }
        }

        template<typename T, typename ElementType>
        FORCE_INLINE int quickSortPartitionDescending(T _array, const i32& _low, const i32& _high)
        {
            ElementType pivot = _array[_high];
            i32 partitionIndex = (_low - 1);

            for (i32 i = _low; i < _high; i++)
            {
                if (_array[i] >= pivot)
                {
                    partitionIndex++;
                    swap(_array[partitionIndex], _array[i]);
                }
            }
            swap(_array[partitionIndex + 1], _array[_high]);

            return (partitionIndex + 1);
        }

        template<typename T, typename ElementType>
        void quickSortDescending(T _array, const i32& _low, const i32& _high)
        {
            if (_low < _high)
            {
                int partitionIndex = quickSortPartitionDescending<T, ElementType>(_array, _low, _high);
                quickSortDescending<T, ElementType>(_array, _low, partitionIndex - 1);
                quickSortDescending<T, ElementType>(_array, partitionIndex + 1, _high);
            }
        }

        template<typename T, typename ElementType>
        FORCE_INLINE int quickSortPartitionCustom(T _array, const i32& _low, const i32& _high, const std::function<bool(const ElementType&, const ElementType&)>& _callback)
        {
            ElementType pivot = _array[_high];
            i32 partitionIndex = (_low - 1);

            for (i32 i = _low; i < _high; i++)
            {
                if (_callback(_array[i], pivot))
                {
                    partitionIndex++;
                    swap(_array[partitionIndex], _array[i]);
                }
            }
            swap(_array[partitionIndex + 1], _array[_high]);

            return (partitionIndex + 1);
        }

        template<typename T, typename ElementType>
        void quickSortCustom(T _array, const i32& _low, const i32& _high, const std::function<bool(const ElementType&, const ElementType&)>& _callback)
        {
            if (_low < _high)
            {
                int partitionIndex = quickSortPartitionCustom<T, ElementType>(_array, _low, _high, _callback);
                quickSortCustom<T, ElementType>(_array, _low, partitionIndex - 1, _callback);
                quickSortCustom<T, ElementType>(_array, partitionIndex + 1, _high, _callback);
            }
        }
    }

    template<typename T>
    FORCE_INLINE T max(const T& _a)
    {
        return _a;
    }

    template<typename T, typename... T2>
    FORCE_INLINE T max(const T& _a, const T& _b, const T2&... _other)
    {
        return _a > _b ? max(_a, _other...) : max(_b, _other...);
    }

    template<typename T>
    FORCE_INLINE T min(const T& _a)
    {
        return _a;
    }

    template<typename T, typename... T2>
    FORCE_INLINE T min(const T& _a, const T& _b, const T2&... _other)
    {
        return _a < _b ? min(_a, _other...) : min(_b, _other...);
    }

    template<typename T, typename ElementType>
    FORCE_INLINE void sort(T _array, const u32& _size, const SortDirection& _direction)
    {
        if (_direction == SortDirection::ascending)
        {
            static_assert(Type<ElementType>::hasOperator<>::lessOrEqual, "Your type doesn't have <= operator to compare.");
            Private::quickSortAscending<T, ElementType>(_array, 0, i32(_size) - 1);
        }
        else
        {
            static_assert(Type<ElementType>::hasOperator<>::greaterOrEqual, "Your type doesn't have >= operator to compare.");
            Private::quickSortDescending<T, ElementType>(_array, 0, i32(_size) - 1);
        }
    }

    template<typename T, typename ElementType>
    FORCE_INLINE void sort(T _array, const u32& _size, const std::function<bool(const ElementType&, const ElementType&)>& _callback)
    {
        Private::quickSortCustom<T, ElementType>(_array, 0, i32(_size) - 1, _callback);
    }

    template<typename T>
    FORCE_INLINE void swap(T& _a, T& _b)
    {
        T temp = std::move(_a);
        _a = std::move(_b);
        _b = std::move(temp);
    }
}
