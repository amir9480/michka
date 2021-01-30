#include "Types.h"
#include "Core/Container/List.h"
#include "Core/Container/Position.h"
#include "Core/Container/Rect.h"
#include "Core/Container/Size.h"
#include "Core/Container/Vector.h"

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

    template<typename T>
    std::ostream& operator << (std::ostream& _out, const PositionTemplate<T>& _value)
    {
        return _out << _value.toString();
    }

    template<typename T>
    std::ostream& operator << (std::ostream& _out, const RectTemplate<T>& _value)
    {
        return _out << _value.toString();
    }

    template<typename T>
    std::ostream& operator << (std::ostream& _out, const SizeTemplate<T>& _value)
    {
        return _out << _value.toString();
    }
}
