#include "Michka/Core/Container/Hash.h"
#include "Michka/Core/Container/String.h"
#include "Michka/Core/Helpers.h"
#include <functional>

namespace Michka
{
    namespace Hash
    {
        template<typename T>
        FORCE_INLINE u64 make(const T& _value)
        {
            if constexpr (Type<T>::is<Michka::String>() || Type<T>::is<Michka::String32>())
            {
                return std::hash<std::string>{}(_value.toUtf8().cstr());
            }
            else if constexpr (Type<T>::is<Michka::String8>())
            {
                return std::hash<std::string>{}(_value.cstr());
            }
            else if constexpr (Type<T>::isCString)
            {
                return std::hash<std::string>{}(String8(_value).cstr());
            }
            else if constexpr (HasToString<T>::value)
            {
                return std::hash<std::string>{}(_value.toString().toUtf8().cstr());
            }
            else if constexpr (Type<T>::isNumeric)
            {
                return std::hash<std::string>{}(String8::number(_value).cstr());
            }
            else
            {
                return std::hash<T>{}(_value);
            }

            return 0; // @NOCOVERAGE
        }
    }
}
