
#include "gtest/gtest.h"
#include <utility>
#include "Core/String.h"

TEST(StringTest, CreateDefaultStringTest) {
	Mishka::String test;
	ASSERT_EQ(test.getSize(), 0);
}

TEST(StringTest, StringSizeTest) {
	Mishka::String test = L"Hello";
	ASSERT_EQ(test.getSize(), 5);
	test = L"Hello WORLD";
	ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, CreateStringTest) {
	Mishka::String test8 = "TEST CHAR";
	ASSERT_TRUE(test8 == "TEST CHAR");
	test8 = L"TEST WCHAR";
	ASSERT_TRUE(test8 == "TEST WCHAR");
	test8 = U"TEST CHAR32_T";
	ASSERT_TRUE(test8 == "TEST CHAR32_T");

	Mishka::String test16 = "TEST CHAR";
	ASSERT_TRUE(test16 == L"TEST CHAR");
	test16 = L"TEST WCHAR";
	ASSERT_TRUE(test16 == L"TEST WCHAR");
	test16 = U"TEST CHAR32_T";
	ASSERT_TRUE(test16 == L"TEST CHAR32_T");

	Mishka::String test32 = "TEST CHAR";
	ASSERT_TRUE(test32 == U"TEST CHAR");
	test32 = L"TEST WCHAR";
	ASSERT_TRUE(test32 == U"TEST WCHAR");
	test32 = U"TEST CHAR32_T";
	ASSERT_TRUE(test32 == U"TEST CHAR32_T");
}

TEST(StringTest, StringEqualTest) {
	Mishka::String test = L"MISHKA TEST";
	ASSERT_TRUE(test == L"MISHKA TEST");
	ASSERT_FALSE(test == L"MISHKA_TEST");
	ASSERT_FALSE(test == L"MISHKA TEST DIFFRENT SIZE");
}

TEST(StringTest, StringNotEqualTest) {
	Mishka::String test = L"MISHKA TEST";
	ASSERT_FALSE(test != L"MISHKA TEST");
	ASSERT_TRUE(test != L"MISHKA_TEST");
	ASSERT_TRUE(test != L"MISHKA TEST DIFFRENT SIZE");
}

TEST(StringTest, StringAssignToAnotherStringTest) {
	Mishka::String test = L"MISHKA TEST";
	Mishka::String test2 = test;
	ASSERT_TRUE(test == L"MISHKA TEST");
	test2 = L"Hello World";
	ASSERT_TRUE(test == L"MISHKA TEST");
	ASSERT_TRUE(test2 == L"Hello World");
	test = test2;
	ASSERT_TRUE(test == L"Hello World");
	ASSERT_TRUE(test2 == L"Hello World");
}

TEST(StringTest, StringMoveConstructorTest) {
	Mishka::String test = L"MISHKA TEST";
	ASSERT_TRUE(test == L"MISHKA TEST");

	Mishka::String test2 = std::move(test);
	ASSERT_TRUE(test2 == L"MISHKA TEST");
	ASSERT_TRUE(test.isEmpty());
}

TEST(StringTest, ClearStringTest) {
	Mishka::String test = L"MISHKA TEST";
	ASSERT_TRUE(test == L"MISHKA TEST");
	test.clear();
	ASSERT_TRUE(test == Mishka::String::empty);
	ASSERT_TRUE(test.isEmpty());
}

TEST(StringTest, NumberToStringTest) {
	ASSERT_TRUE(Mishka::String::number(1) == L"1");
	ASSERT_TRUE(Mishka::String::number(12) == L"12");
	ASSERT_TRUE(Mishka::String::number(123) == L"123");
	ASSERT_TRUE(Mishka::String::number(2147483647) == L"2147483647");
	ASSERT_TRUE(Mishka::String::number(-1) == L"-1");
	ASSERT_TRUE(Mishka::String::number(-12) == L"-12");
	ASSERT_TRUE(Mishka::String::number(-123) == L"-123");
	ASSERT_TRUE(Mishka::String::number(-2147483647) == L"-2147483647");
	ASSERT_TRUE(Mishka::String::number(0xf, 16) == L"f");
	ASSERT_TRUE(Mishka::String::number(-0xf, 16) == L"-f");
	ASSERT_TRUE(Mishka::String::number(0b1010101, 2) == L"1010101");
	ASSERT_TRUE(Mishka::String::number(float(3.14f)) == L"3.14");
	ASSERT_TRUE(Mishka::String::number(double(3.14159265)) == L"3.14159");
	ASSERT_TRUE(Mishka::String::number(long double(3.14159265359)) == L"3.14159");
	ASSERT_TRUE(Mishka::String::number(float(-3.14f)) == L"-3.14");
	ASSERT_TRUE(Mishka::String::number(double(-3.14159265)) == L"-3.14159");
	ASSERT_TRUE(Mishka::String::number(long double(-3.14159265359)) == L"-3.14159");
}

TEST(StringTest, StringToNumberTest) {
	Mishka::String test = L"12345";
	ASSERT_EQ(test.toNumber<i16>(), 12345);
	ASSERT_EQ(test.toNumber<u16>(), 12345);
	ASSERT_EQ(test.toNumber<i32>(), 12345);
	ASSERT_EQ(test.toNumber<u32>(), 12345);
	ASSERT_EQ(test.toNumber<i64>(), 12345);
	ASSERT_EQ(test.toNumber<u64>(), 12345);
	test = L"+12345";
	ASSERT_EQ(test.toNumber<i16>(), 12345);
	ASSERT_EQ(test.toNumber<u16>(), 12345);
	ASSERT_EQ(test.toNumber<i32>(), 12345);
	ASSERT_EQ(test.toNumber<u32>(), 12345);
	ASSERT_EQ(test.toNumber<i64>(), 12345);
	ASSERT_EQ(test.toNumber<u64>(), 12345);

	test = L"-12345";
	ASSERT_EQ(test.toNumber<i16>(), -12345);
	ASSERT_EQ(test.toNumber<i32>(), -12345);
	ASSERT_EQ(test.toNumber<i64>(), -12345);

	test = Mishka::String::empty;
	ASSERT_EQ(test.toNumber<i64>(), 0);

	test = "NON NUMBER";
	ASSERT_EQ(test.toNumber<i64>(), 0);

	test = "3.1415";
	ASSERT_EQ(test.toNumber<float>(), float(3.1415f));
	ASSERT_EQ(test.toNumber<double>(), double(3.1415f));
	ASSERT_EQ(test.toNumber<float>(), long double(3.1415f));


}

TEST(StringTest, StringReverseTest) {
	Mishka::String test;
	test.reverse();
	ASSERT_TRUE(test == Mishka::String::empty);
	test = "Hello World";
	test.reverse();
	ASSERT_TRUE(test == "dlroW olleH");
	test = "123";
	test.reverse();
	ASSERT_TRUE(test == "321");
	test = "1234";
	ASSERT_TRUE(test.getReversed() == "4321");
	ASSERT_TRUE(test == "1234");
}

TEST(StringTest, StringGetCharacterTest) {
	Mishka::String test = L"Hello World";
	ASSERT_EQ(test[0], L'H');
	ASSERT_EQ(test[4], L'o');
	ASSERT_EQ(test[10], L'd');
}

TEST(StringTest, StringFindCharacterTest) {
	Mishka::String test = L"Hello World";
	ASSERT_EQ(test.find(L'H'), 0);
	ASSERT_EQ(test.find(L'e'), 1);
	ASSERT_EQ(test.find(L'l'), 2);
	ASSERT_EQ(test.find(L'o'), 4);
	ASSERT_EQ(test.find(L'd'), 10);
	ASSERT_EQ(test.find(L'T'), Mishka::String::notFound);
}

