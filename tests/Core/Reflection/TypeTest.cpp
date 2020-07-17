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
#include <limits>
#include <cstring>
#include <type_traits>
#include "Core/Reflection/Type.h"
#include "Core/Helpers.h"
#include "Core/Types.h"
#include "../../Classes/Person.h"

#define TYPE_NAME_TEST(TYPE, TYPENAME) ASSERT_TRUE(strcmp(Michka::Type<TYPE>::name, TYPENAME) == 0)
#define TYPE_MIN_TEST(TYPE) ASSERT_EQ(Michka::Type<TYPE>::min, std::numeric_limits<TYPE>::min())
#define TYPE_MAX_TEST(TYPE) ASSERT_EQ(Michka::Type<TYPE>::max, std::numeric_limits<TYPE>::max())
#define TYPE_IS_INTEGRAL(TYPE) ASSERT_EQ(Michka::Type<TYPE>::isIntegral, std::is_integral<TYPE>::value)
#define TYPE_IS_FLOAT(TYPE) ASSERT_EQ(Michka::Type<TYPE>::isFloat, std::is_floating_point<TYPE>::value)
#define TYPE_IS_SIGNED(TYPE) ASSERT_EQ(Michka::Type<TYPE>::isSigned, std::is_signed<TYPE>::value)
#define TYPE_IS_UNSIGNED(TYPE) ASSERT_EQ(Michka::Type<TYPE>::isUnsigned, std::is_unsigned<TYPE>::value)

#define TYPE_TEST(...) MICHKA_OVERLOADED_MACRO(_TYPE_TEST_, __VA_ARGS__)

#define __TYPE_TEST(TYPE) \
    TYPE_MIN_TEST(TYPE); \
    TYPE_MAX_TEST(TYPE); \
    TYPE_IS_INTEGRAL(TYPE); \
    TYPE_IS_FLOAT(TYPE); \
    TYPE_IS_SIGNED(TYPE); \
    TYPE_IS_UNSIGNED(TYPE);

#define _TYPE_TEST_1(TYPE) \
    TYPE_NAME_TEST(TYPE, #TYPE); \
    __TYPE_TEST(TYPE);

#define _TYPE_TEST_2(TYPE, TYPENAME) \
    TYPE_NAME_TEST(TYPE, TYPENAME); \
    __TYPE_TEST(TYPE);

class MichkaTestClass {};
union MichkaTestUnion {};
enum MichkaTestEnum {};

TEST(TypeTest, Compare)
{
    int a = 100;
    ASSERT_FALSE(Michka::Type<int>::is<float>());
    ASSERT_FALSE(Michka::Type<decltype(a)>::is<float>());
    ASSERT_FALSE(Michka::Type<decltype(a)>::is<u32>());
    ASSERT_TRUE(Michka::Type<decltype(a)>::is<int>());
}

TEST(TypeTest, HasOperator)
{
    int a = 100;
    ASSERT_TRUE(Michka::Type<decltype(a)>::hasOperator<const int>::equal);
    ASSERT_TRUE(Michka::Type<decltype(a)>::hasOperator<float>::equal);
    ASSERT_TRUE(Michka::Type<int>::hasOperator<>::equal);
    ASSERT_TRUE(Michka::Type<int>::hasOperator<>::notEqual);
    ASSERT_TRUE(Michka::Type<int>::hasOperator<>::less);
    ASSERT_TRUE(Michka::Type<int>::hasOperator<>::lessOrEqual);
    ASSERT_TRUE(Michka::Type<int>::hasOperator<>::greater);
    ASSERT_TRUE(Michka::Type<int>::hasOperator<>::greaterOrEqual);

    ASSERT_FALSE(Michka::Type<Person>::hasOperator<int>::equal);
    ASSERT_FALSE(Michka::Type<Person>::hasOperator<int>::notEqual);
    ASSERT_FALSE(Michka::Type<Person>::hasOperator<int>::less);
    ASSERT_FALSE(Michka::Type<Person>::hasOperator<int>::lessOrEqual);
    ASSERT_FALSE(Michka::Type<Person>::hasOperator<int>::greater);
    ASSERT_FALSE(Michka::Type<Person>::hasOperator<int>::greaterOrEqual);
}

TEST(TypeTest, Range)
{
    ASSERT_TRUE(true);
    TYPE_TEST(short, "short int");
    TYPE_TEST(short int);
    TYPE_TEST(signed short, "short int");
    TYPE_TEST(signed short int, "short int");
    TYPE_TEST(unsigned short, "unsigned short int");
    TYPE_TEST(unsigned short int);
    TYPE_TEST(int);
    TYPE_TEST(signed, "int");
    TYPE_TEST(signed int, "int");
    TYPE_TEST(unsigned, "unsigned int");
    TYPE_TEST(unsigned int);
    TYPE_TEST(long, "long int");
    TYPE_TEST(long int);
    TYPE_TEST(signed long, "long int");
    TYPE_TEST(signed long int, "long int");
    TYPE_TEST(unsigned long, "unsigned long int");
    TYPE_TEST(unsigned long int, "unsigned long int");
    TYPE_TEST(long long, "long long int");
    TYPE_TEST(long long int);
    TYPE_TEST(signed long long, "long long int");
    TYPE_TEST(signed long long int, "long long int");
    TYPE_TEST(unsigned long long, "unsigned long long int");
    TYPE_TEST(unsigned long long int);
    TYPE_TEST(float);
    TYPE_TEST(double);
    TYPE_TEST(long double);
    TYPE_TEST(char16_t);
    TYPE_TEST(char32_t);
    TYPE_TEST(wchar_t);

    ASSERT_FALSE(Michka::Type<bool>::isClass);
    ASSERT_FALSE(Michka::Type<bool>::isUnion);
    ASSERT_FALSE(Michka::Type<bool>::isEnum);
    ASSERT_TRUE(Michka::Type<MichkaTestClass>::isClass);
    ASSERT_TRUE(Michka::Type<MichkaTestUnion>::isUnion);
    ASSERT_TRUE(Michka::Type<MichkaTestEnum>::isEnum);
}

TEST(TypeTest, RemovePointerAndReference)
{
    ASSERT_TRUE(Michka::Type<typename Michka::Type<int>::RemovedPointerType>::is<int>());
    ASSERT_TRUE(Michka::Type<typename Michka::Type<int*>::RemovedPointerType>::is<int>());

    ASSERT_TRUE(Michka::Type<typename Michka::Type<int>::RemovedReferenceType>::is<int>());
    ASSERT_TRUE(Michka::Type<typename Michka::Type<int&>::RemovedReferenceType>::is<int>());
    ASSERT_TRUE(Michka::Type<typename Michka::Type<int&&>::RemovedReferenceType>::is<int>());
}
