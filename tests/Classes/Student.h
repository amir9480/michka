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

#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <ostream>
#include "Michka/Core/Container/String.h"

// A class just for testing
class Student
{
public:
    Student()
    {
        //
    }

    Student(const Michka::String& _name)
    {
        mName = _name;
    }

    Student(const Student& _other)
    {
        mName = _other.mName;
    }

    Student(Student&& _other)
    {
        mName = std::move(_other.mName);
    }

    Michka::String getName() const
    {
        return mName;
    }

    void setName(const Michka::String& _name)
    {
        mName = _name;
    }

    bool operator == (const Michka::String& _name) const
    {
        return mName == _name;
    }

    bool operator == (const Student& _other) const
    {
        return mName == _other.mName;
    }
protected:
    Michka::String mName;
};

static std::ostream& operator << (std::ostream& _out, const Student& _value)
{
    _out << "Student(" << _value.getName().toUtf8().cstr() << ")";
    return _out;
}

#endif // __STUDENT_H__
