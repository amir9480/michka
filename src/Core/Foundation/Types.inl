#include "Types.h"

namespace Michka
{
    template<typename T>
    std::ostream& operator << (std::ostream& _out, const List<T>& _value)
    {
        return _out << _value.toString();
    }

    template<typename T>
    std::ostream& operator << (std::ostream& _out, const Vector<T>& _value)
    {
        return _out << _value.toString();
    }
}
