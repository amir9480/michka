#include "Helpers.h"
#include "Defines.h"
#include "Reflection/Type.h"

namespace Michka
{
    template<typename T>
    FORCE_INLINE void swap(T& _a, T& _b)
    {
		T temp = std::move(_a);
		_a = std::move(_b);
		_b = std::move(temp);
    }

    template<typename T>
	FORCE_INLINE const T& min(const T& _a, const T& _b)
    {
        return _a < _b ? _a : _b;
    }

	template<typename T>
	FORCE_INLINE const T& max(const T& _a, const T& _b)
    {
        return _a > _b ? _a : _b;
    }

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

    template<typename T, typename ElementType>
    FORCE_INLINE void sort(T _array, const u32& _size, const SortDirection& _direction)
    {
        if (_direction == SortDirection::Ascending)
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
}
