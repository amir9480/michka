// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
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

#ifndef __PERSON_H__
#define __PERSON_H__

#include "Core/Container/String.h"

// A class just for testing
class Person
{
public:
    Person(const Michka::String& _name)
    {
        mName = _name;
    }

    Person(const Person& _other)
    {
        mName = _other.mName;
    }

    Person(Person&& _other)
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

    Michka::String toString() const
    {
        return "Person(" + mName + ")";
    }

    bool operator == (const Michka::String& _name) const
    {
        return mName == _name;
    }

    bool operator == (const Person& _other) const
    {
        return mName == _other.mName;
    }
protected:
    Michka::String mName;
};

static std::ostream& operator << (std::ostream& _out, const Person& _value)
{
    _out << "Person(" << _value.getName().toUtf8().cstr() << ")";
    return _out;
}

#endif // __PERSON_H__
