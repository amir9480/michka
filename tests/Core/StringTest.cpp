
#include "gtest/gtest.h"
#include <utility>
#include "Core/String.h"

TEST(StringTest, CreateDefaultStringTest)
{
	Mishka::String test;
	ASSERT_EQ(test.getSize(), 0);
}

TEST(StringTest, StringSizeTest)
{
	Mishka::String test = L"Hello";
	ASSERT_EQ(test.getSize(), 5);
	test = L"Hello WORLD";
	ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, CreateStringTest)
{
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

TEST(StringTest, StringEqualTest)
{
	Mishka::String test = L"MISHKA TEST";
	ASSERT_TRUE(test == L"MISHKA TEST");
	ASSERT_FALSE(test == L"MISHKA_TEST");
	ASSERT_FALSE(test == L"MISHKA TEST DIFFRENT SIZE");
}

TEST(StringTest, StringNotEqualTest)
{
	Mishka::String test = L"MISHKA TEST";
	ASSERT_FALSE(test != L"MISHKA TEST");
	ASSERT_TRUE(test != L"MISHKA_TEST");
	ASSERT_TRUE(test != L"MISHKA TEST DIFFRENT SIZE");
}

TEST(StringTest, StringAssignToAnotherStringTest)
{
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

TEST(StringTest, StringMoveConstructorTest)
{
	Mishka::String test = L"MISHKA TEST";
	ASSERT_TRUE(test == L"MISHKA TEST");

	Mishka::String test2 = std::move(test);
	ASSERT_TRUE(test2 == L"MISHKA TEST");
	ASSERT_TRUE(test.isEmpty());
}

TEST(StringTest, ClearStringTest)
{
	Mishka::String test = L"MISHKA TEST";
	ASSERT_TRUE(test == L"MISHKA TEST");
	test.clear();
	ASSERT_TRUE(test == Mishka::String::empty);
	ASSERT_TRUE(test.isEmpty());
	ASSERT_FALSE(test.isNotEmpty());
}

TEST(StringTest, NumberToStringTest)
{
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

TEST(StringTest, StringToNumberTest)
{
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
	ASSERT_EQ(test.toNumber<double>(), double(3.1415));
	ASSERT_EQ(test.toNumber<long double>(), long double(3.1415));
}

TEST(StringTest, StringReverseTest)
{
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

TEST(StringTest, StringGetCharacterTest)
{
	Mishka::String test = L"Hello World";
	ASSERT_EQ(test[0], L'H');
	ASSERT_EQ(test[4], L'o');
	ASSERT_EQ(test[10], L'd');
}

TEST(StringTest, StringFindCharacterTest)
{
	Mishka::String test = L"Hello World";
	Mishka::String test2 = "Hello World Hello";
	ASSERT_EQ(test.find(L'H'), 0);
	ASSERT_EQ(test.find(L'e'), 1);
	ASSERT_EQ(test.find(L'l'), 2);
	ASSERT_EQ(test.find(L'o'), 4);
	ASSERT_EQ(test.find(L'l', 4), 9);
	ASSERT_EQ(test.find(L'd'), 10);
	ASSERT_EQ(test.find(L'T'), Mishka::String::notFound);

	ASSERT_EQ(test.findLast(L'H'), 0);
	ASSERT_EQ(test.findLast(L'e'), 1);
	ASSERT_EQ(test.findLast(L'l'), 9);
	ASSERT_EQ(test.findLast(L'o'), 7);
	ASSERT_EQ(test.findLast(L'l', 4), 3);
	ASSERT_EQ(test.findLast(L'l', 3), 3);
	ASSERT_EQ(test.findLast(L'l', 2), 2);
	ASSERT_EQ(test.findLast(L'd'), 10);
	ASSERT_EQ(test.findLast(L'T'), Mishka::String::notFound);

	ASSERT_EQ(test.find(L"Hello"), 0);
	ASSERT_EQ(test.find(L"ello"), 1);
	ASSERT_EQ(test.find(L"Hello", 1), Mishka::String::notFound);
	ASSERT_EQ(test2.find(L"Hello", 1), 12);
	ASSERT_EQ(test.find(L"World"), 6);
	ASSERT_EQ(test.find(L"World", 6), 6);
	ASSERT_EQ(test.find(L"RandomStuff"), Mishka::String::notFound);
	ASSERT_EQ(Mishka::String().find(L"RandomStuff"), Mishka::String::notFound);
	ASSERT_EQ(Mishka::String().find(Mishka::String()), Mishka::String::notFound);
	ASSERT_EQ(test.find(Mishka::String()), Mishka::String::notFound);

	ASSERT_EQ(test2.findLast(L"Hello"), 12);
	ASSERT_EQ(test2.findLast(L"ello"), 13);
	ASSERT_EQ(test2.findLast(L"World", 10), Mishka::String::notFound);
	ASSERT_EQ(test2.findLast(L"Hello", 16), 0);
	ASSERT_EQ(test2.findLast(L"World"), 6);
	ASSERT_EQ(test2.findLast(L"World", 12), 6);
	ASSERT_EQ(test2.findLast(L"World", 11), 6);
	ASSERT_EQ(test2.findLast(L"RandomStuff"), Mishka::String::notFound);
	ASSERT_EQ(Mishka::String().findLast(L"RandomStuff"), Mishka::String::notFound);
	ASSERT_EQ(Mishka::String().findLast(Mishka::String()), Mishka::String::notFound);
	ASSERT_EQ(test2.findLast(Mishka::String()), Mishka::String::notFound);
}

TEST(StringTest, StringAppendTest)
{
	Mishka::String test = "Hello";
	ASSERT_EQ(test + " World", "Hello World");
	ASSERT_EQ((test + " World").getSize(), 11);
	ASSERT_EQ("World " + test, "World Hello");
	ASSERT_EQ(("World " + test).getSize(), 11);

	test += " World";
	ASSERT_EQ(test, "Hello World");
	ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, StringPrependTest)
{
	Mishka::String test = "World";
	test.prepend("Hello ");
	ASSERT_EQ(test, "Hello World");
	ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, StringRemoveTest)
{
	ASSERT_EQ(Mishka::String("Hello World").remove(0), "");
	ASSERT_EQ(Mishka::String("Hello World").remove(1), "H");
	ASSERT_EQ(Mishka::String("Hello World").remove(2), "He");
	ASSERT_EQ(Mishka::String("Hello World").remove(2, 2), "Heo World");
	ASSERT_EQ(Mishka::String("Hello World").remove(0, 6), "World");
	ASSERT_EQ(Mishka::String("Hello World").remove(5, 6), "Hello");
}

TEST(StringTest, StringSubStringTest)
{
	Mishka::String test = "Hello World";
	ASSERT_EQ(test.subString(0), "Hello World");
	ASSERT_EQ(test.subString(1), "ello World");
	ASSERT_EQ(test.subString(2), "llo World");
	ASSERT_EQ(test.subString(0, 5), "Hello");
	ASSERT_EQ(test.subString(6, 5), "World");
}

TEST(StringTest, StringUnicodeTest)
{
	Mishka::String8 test8;
	Mishka::String test16;
	Mishka::String32 test32;
	Mishka::String test = Mishka::String::fromUtf8("سلام دنیا - 🌍");
	test8 = test.toUtf8();
	ASSERT_TRUE(strcmp(test8.cstr(), "سلام دنیا - 🌍") == 0);
}

TEST(StringTest, StringInsertTest)
{
	ASSERT_EQ(Mishka::String("Hello").insert(" World!", 5), "Hello World!");
	ASSERT_EQ(Mishka::String("Hello").insert("World!", 0), "World!Hello");
	ASSERT_EQ(Mishka::String("Hello").insert("World!", 6), "Hello World!");
}

TEST(StringTest, StringRepaceTest)
{
	ASSERT_EQ(Mishka::String("Hello World!").replace("test"), "Hello World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("Hello"), " World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("World"), "Hello !");
	ASSERT_EQ(Mishka::String("Hello World!").replace("Hello", "", 1), "Hello World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("World", "", 0, 5), "Hello World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("Hello", "Test"), "Test World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("Hello", "World"), "World World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("Hello", "Welcome to"), "Welcome to World!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("World", "Test"), "Hello Test!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("World", "Hello"), "Hello Hello!");
	ASSERT_EQ(Mishka::String("Hello World!").replace("World", "Mishka the bird!"), "Hello Mishka the bird!!");

	ASSERT_EQ(Mishka::String("Hello World").replace("World", "Test"), "Hello Test");
	ASSERT_EQ(Mishka::String("Hello World").replace("World", "Hello"), "Hello Hello");
	ASSERT_EQ(Mishka::String("Hello World").replace("World", "Mishka the bird!"), "Hello Mishka the bird!");
}

TEST(StringTest, StringToLowerTest)
{
	ASSERT_EQ(Mishka::String("Hello World!").toLower(), "hello world!");
}

TEST(StringTest, StringToUpperTest)
{
	ASSERT_EQ(Mishka::String("Hello World!").toUpper(), "HELLO WORLD!");
}
