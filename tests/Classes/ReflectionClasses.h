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

#ifndef __TEST_REFLECTION_CLASSES_H__
#define __TEST_REFLECTION_CLASSES_H__

#include "Michka/Core/Reflection/TypeInfo.h"

class ParentClass1
{
    MICHKA_CLASS();
public:
    int a1 = 0;
};

class ParentClass2
{
    MICHKA_CLASS();
public:
    int a2 = 0;
};

class ParentClass3
{
    MICHKA_CLASS();
public:
    int a3 = 0;
};

class ParentClass4
{
    MICHKA_CLASS();
public:
    int a4 = 0;
};

class ParentClass5
{
    MICHKA_CLASS();
public:
    int a5 = 0;
};

class ParentClass6
{
    MICHKA_CLASS();
public:
    int a6 = 0;
};

class ParentClass7
{
    MICHKA_CLASS();
public:
    int a7 = 0;
};

class ParentClass8
{
    MICHKA_CLASS();
public:
    int a8 = 0;
};

class ParentClass9
{
    MICHKA_CLASS();
public:
    int a9 = 0;
};

class ParentClass10
{
    MICHKA_CLASS();
public:
    int a10 = 0;
};

class ChildClass0
{
    MICHKA_CLASS();
public:
    int b0;
};

class ChildClass1: public ParentClass1
{
    MICHKA_CLASS();
public:
    int b1 = 0;
};

class ChildClass2: public ParentClass1, public ParentClass2
{
    MICHKA_CLASS();
public:
    int b2 = 0;
};

class ChildClass3: public ParentClass1, public ParentClass2, public ParentClass3
{
    MICHKA_CLASS();
public:
    int b3 = 0;
};

class ChildClass4: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4
{
    MICHKA_CLASS();
public:
    int b4 = 0;
};

class ChildClass5: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4, public ParentClass5
{
    MICHKA_CLASS();
public:
    int b5 = 0;
};

class ChildClass6: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4, public ParentClass5, public ParentClass6
{
    MICHKA_CLASS();
public:
    int b6 = 0;
};

class ChildClass7: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4, public ParentClass5, public ParentClass6, public ParentClass7
{
    MICHKA_CLASS();
public:
    int b7 = 0;
};

class ChildClass8: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4, public ParentClass5, public ParentClass6, public ParentClass7, public ParentClass8
{
    MICHKA_CLASS();
public:
    int b8 = 0;
};

class ChildClass9: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4, public ParentClass5, public ParentClass6, public ParentClass7, public ParentClass8, public ParentClass9
{
    MICHKA_CLASS();
public:
    int b9 = 0;
};

class ChildClass10: public ParentClass1, public ParentClass2, public ParentClass3, public ParentClass4, public ParentClass5, public ParentClass6, public ParentClass7, public ParentClass8, public ParentClass9, public ParentClass10
{
    MICHKA_CLASS();
public:
    int b10 = 0;
};

class ChildClass10Nested: public ChildClass10
{
    MICHKA_CLASS(CustomAttribute="Hello 1", CustomAttribute2=666);

public:
    class Child: public ParentClass5
    {
        MICHKA_CLASS();
    public:
        int childTest = 0;
    };

    int b100 = 0;
};

#endif // __TEST_REFLECTION_CLASSES_H__
