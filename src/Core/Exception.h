#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>

namespace Michka
{
    class Exception : std::exception
    {
    public:
        using std::exception::exception;

        virtual char const* getMessage() const
        {
            return what();
        }
    };
}

#endif // __EXCEPTION_H__
