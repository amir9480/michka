#include "Person.h"
#include <ostream>

u32 Person::count = 0;

std::ostream& operator << (std::ostream& _out, const Person& _value)
{
    _out << "Person(" << _value.getName().toUtf8().cstr() << ")";
    return _out;
}
