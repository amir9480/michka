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

#include <gtest/gtest.h>
#include <type_traits>
#include "Core/Helpers.h"
#include "Core/Container/Map.h"
#include "Core/Reflection/TypeInfo.h"
#include "../../Classes/ReflectionClasses.h"

TEST(ClassReflectionTest, Name)
{
    ASSERT_STREQ(ChildClass0::className(), "ChildClass0");
    ASSERT_STREQ(ChildClass1::className(), "ChildClass1");
}

TEST(ClassReflectionTest, Parent)
{
    ASSERT_TRUE((std::is_same<ChildClass0::Self, ChildClass0>::value));

    ASSERT_TRUE((std::is_same<ChildClass0::Parent, void>::value));

    ASSERT_TRUE((std::is_same<ChildClass1::Parent, ParentClass1>::value));

    ASSERT_TRUE((std::is_same<ChildClass2::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass2::Parent2, ParentClass2>::value));

    ASSERT_TRUE((std::is_same<ChildClass3::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass3::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass3::Parent3, ParentClass3>::value));

    ASSERT_TRUE((std::is_same<ChildClass4::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass4::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass4::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass4::Parent4, ParentClass4>::value));

    ASSERT_TRUE((std::is_same<ChildClass5::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass5::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass5::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass5::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass5::Parent5, ParentClass5>::value));

    ASSERT_TRUE((std::is_same<ChildClass6::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass6::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass6::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass6::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass6::Parent5, ParentClass5>::value));
    ASSERT_TRUE((std::is_same<ChildClass6::Parent6, ParentClass6>::value));

    ASSERT_TRUE((std::is_same<ChildClass7::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass7::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass7::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass7::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass7::Parent5, ParentClass5>::value));
    ASSERT_TRUE((std::is_same<ChildClass7::Parent6, ParentClass6>::value));
    ASSERT_TRUE((std::is_same<ChildClass7::Parent7, ParentClass7>::value));

    ASSERT_TRUE((std::is_same<ChildClass8::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent5, ParentClass5>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent6, ParentClass6>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent7, ParentClass7>::value));
    ASSERT_TRUE((std::is_same<ChildClass8::Parent8, ParentClass8>::value));

    ASSERT_TRUE((std::is_same<ChildClass9::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent5, ParentClass5>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent6, ParentClass6>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent7, ParentClass7>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent8, ParentClass8>::value));
    ASSERT_TRUE((std::is_same<ChildClass9::Parent9, ParentClass9>::value));

    ASSERT_TRUE((std::is_same<ChildClass10::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent5, ParentClass5>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent6, ParentClass6>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent7, ParentClass7>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent8, ParentClass8>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent9, ParentClass9>::value));
    ASSERT_TRUE((std::is_same<ChildClass10::Parent10, ParentClass10>::value));

    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent, ChildClass10>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent, ParentClass1>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent2, ParentClass2>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent3, ParentClass3>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent4, ParentClass4>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent5, ParentClass5>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent6, ParentClass6>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent7, ParentClass7>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent8, ParentClass8>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent9, ParentClass9>::value));
    ASSERT_TRUE((std::is_same<ChildClass10Nested::Parent::Parent10, ParentClass10>::value));
}
