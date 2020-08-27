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

#include <gtest/gtest.h>
#include <utility>
#include "Core/Container/String.h"
#include "Core/Foundation/Types.h"
#include "Core/Helpers.h"
#include "../Classes/Person.h"
#include "../Classes/Student.h"

#define HELPER_TEST_MACRO(...) MICHKA_OVERLOADED_MACRO(_HELPER_TEST_MACRO, __VA_ARGS__)
#define _HELPER_TEST_MACRO0() 0
#define _HELPER_TEST_MACRO1(_A1) 1
#define _HELPER_TEST_MACRO2(_A1, _A2) 2
#define _HELPER_TEST_MACRO3(_A1, _A2, _A3) 3

#define HELPER_TEST_VA_MACRO(...) MICHKA_OVERLOADED_VA_MACRO(_HELPER_TEST_VA_MACRO_, __VA_ARGS__)
#define _HELPER_TEST_VA_MACRO_ZERO() 0
#define _HELPER_TEST_VA_MACRO_MULTIPLE(...) 1

TEST(HelpersTest, CountArguments)
{
    ASSERT_EQ(MICHKA_COUNT_ARGS(), 0);
    ASSERT_EQ(MICHKA_COUNT_ARGS(1), 1);
    ASSERT_EQ(MICHKA_COUNT_ARGS(1, 2), 2);
    ASSERT_EQ(MICHKA_COUNT_ARGS(1, 2, 3), 3);
    ASSERT_EQ(MICHKA_COUNT_ARGS(1, 2, 3, 4), 4);
    ASSERT_EQ(MICHKA_COUNT_ARGS(1, 2, 3, 4, 5), 5);
    ASSERT_EQ(
        MICHKA_COUNT_ARGS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120),
        120
    );
}

TEST(HelpersTest, HasMemberFunction)
{
    bool test1 = HasToString<Person>::value;
    ASSERT_TRUE(test1);
    bool test2 = HasToString<Student>::value;
    ASSERT_FALSE(test2);
    bool test3 = MichkaHasMemberFunction::HasToString<Person, Michka::String()>::value;
    ASSERT_TRUE(test1);
    bool test4 = MichkaHasMemberFunction::HasToString<Student, Michka::String()>::value;
    ASSERT_FALSE(test2);
}

TEST(HelpersTest, Max)
{
    ASSERT_EQ(Michka::max(1.0f, 2.0f), 2.0f);
    ASSERT_EQ(Michka::max(1.0f, 2.0f, 3.0f), 3.0f);
    ASSERT_EQ(Michka::max(1.0f, 2.0f, 3.0f, 4.0f), 4.0f);
    ASSERT_EQ(Michka::max(1.0f, 2.0f, 3.0f, 4.0f, 5.0f), 5.0f);
}

TEST(HelpersTest, Min)
{
    ASSERT_EQ(Michka::min(1.0f, 2.0f), 1.0f);
    ASSERT_EQ(Michka::min(1.0f, 2.0f, 3.0f), 1.0f);
    ASSERT_EQ(Michka::min(1.0f, 2.0f, 3.0f, 4.0f), 1.0f);
    ASSERT_EQ(Michka::min(1.0f, 2.0f, 3.0f, 4.0f, 5.0f), 1.0f);
}

TEST(HelpersTest, OverloadedMacro)
{
    ASSERT_EQ(HELPER_TEST_MACRO(), 0);
    ASSERT_EQ(HELPER_TEST_MACRO(1), 1);
    ASSERT_EQ(HELPER_TEST_MACRO(1, 2), 2);
    ASSERT_EQ(HELPER_TEST_MACRO(1, 2, 3), 3);

    ASSERT_EQ(HELPER_TEST_VA_MACRO(), 0);
    ASSERT_EQ(HELPER_TEST_VA_MACRO(1), 1);
    ASSERT_EQ(HELPER_TEST_VA_MACRO(1, 2), 1);
    ASSERT_EQ(HELPER_TEST_VA_MACRO(1, 2, 3), 1);
}

TEST(HelpersTest, Swap)
{
    int a = 10, b = 20;
    Michka::swap(a, b);
    ASSERT_EQ(a, 20);
    ASSERT_EQ(b, 10);

    Michka::String astr = "Hello", bstr = "Bye";
    Michka::swap(astr, bstr);
    ASSERT_TRUE(astr == "Bye");
    ASSERT_TRUE(bstr == "Hello");
}
