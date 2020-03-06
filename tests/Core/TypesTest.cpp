#include "gtest/gtest.h"
#include "Core/Types.h"
#include "Core/Helpers.h"
#include <limits>
#include <cstring>
#include <type_traits>

#define TYPE_NAME_TEST(TYPE, TYPENAME) ASSERT_TRUE(strcmp(Mishka::Type<TYPE>::name, TYPENAME) == 0)
#define TYPE_MIN_TEST(TYPE) ASSERT_EQ(Mishka::Type<TYPE>::min, std::numeric_limits<TYPE>::min())
#define TYPE_MAX_TEST(TYPE) ASSERT_EQ(Mishka::Type<TYPE>::max, std::numeric_limits<TYPE>::max())
#define TYPE_IS_INTEGRAL(TYPE) ASSERT_EQ(Mishka::Type<TYPE>::isIntegral, std::is_integral<TYPE>::value)
#define TYPE_IS_FLOAT(TYPE) ASSERT_EQ(Mishka::Type<TYPE>::isFloat, std::is_floating_point<TYPE>::value)
#define TYPE_IS_SIGNED(TYPE) ASSERT_EQ(Mishka::Type<TYPE>::isSigned, std::is_signed<TYPE>::value)
#define TYPE_IS_UNSIGNED(TYPE) ASSERT_EQ(Mishka::Type<TYPE>::isUnsigned, std::is_unsigned<TYPE>::value)

#define TYPE_TEST(...) MISHKA_OVERLOADED_MACRO(_TYPE_TEST_, __VA_ARGS__)

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

class MishkaTestClass {};
union MishkaTestUnion {};
enum MishkaTestEnum {};

TEST(TypesTest, TypesRangeTest)
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

    ASSERT_TRUE(Mishka::Type<MishkaTestClass>::isClass);
    ASSERT_TRUE(Mishka::Type<MishkaTestUnion>::isUnion);
    ASSERT_TRUE(Mishka::Type<MishkaTestEnum>::isEnum);
}
