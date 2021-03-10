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

#include "ClassReflection.h"

namespace Michka
{
    ClassReflection::ClassReflection(const char* _name, const char* _rawname, const char* _typename, const u64& _typehash, const char* _filename) :
        mName(_name),
        mRawName(_rawname),
        mTypeName(_typename),
        mTypeHash(_typehash),
        mFileName(_filename)
    {
        //
    }

    ClassReflection::~ClassReflection()
    {
        //
    }

    const char* ClassReflection::getFileName() const
    {
        return mFileName;
    }

    const char* ClassReflection::getName() const
    {
        return mName;
    }

    const char* ClassReflection::getRawName() const
    {
        return mRawName;
    }

    u64 ClassReflection::getTypeHash() const
    {
        return mTypeHash;
    }

    const char* ClassReflection::getTypeName() const
    {
        return mTypeName;
    }

    ClassReflection& ClassReflection::setName(const char* _name)
    {
        mName = _name;
        return *this;
    }
}
