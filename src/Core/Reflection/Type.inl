#include "Type.h"

namespace Michka
{
    template<typename T>
    template<typename T2>
    constexpr inline const bool TypeBase<T>::is()
    {
        return std::is_same<T, T2>::value;
    }
}
