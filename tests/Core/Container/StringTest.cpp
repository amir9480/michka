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
#include <utility>
#include "Core/Container/String.h"
#include "Core/Foundation/Types.h"

TEST(StringTest, Append)
{
    Michka::String test = "Hello";
    ASSERT_EQ(test + " World", "Hello World");
    ASSERT_EQ((test + " World").getSize(), 11);
    ASSERT_EQ("World " + test, "World Hello");
    ASSERT_EQ(("World " + test).getSize(), 11);

    test += " World";
    ASSERT_EQ(test, "Hello World");
    ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, AssignToAnotherString)
{
    {
        Michka::String test = L"MICHKA TEST";
        Michka::String test2 = test;
        ASSERT_TRUE(test == L"MICHKA TEST");
        test2 = L"Hello World";
        ASSERT_TRUE(test == L"MICHKA TEST");
        ASSERT_TRUE(test2 == L"Hello World");
        test = test2;
        ASSERT_TRUE(test == L"Hello World");
        ASSERT_TRUE(test2 == L"Hello World");
        test = (wchar_t*)nullptr;
        ASSERT_TRUE(test == L"");
    }
    {
        Michka::String8 test = (char*)nullptr;
        ASSERT_TRUE(test == L"");
        test = (wchar_t*)nullptr;
        ASSERT_TRUE(test == L"");
    }
    {
        Michka::String32 test = (char32_t*)nullptr;
        ASSERT_TRUE(test == U"");
        test = (wchar_t*)nullptr;
        ASSERT_TRUE(test == L"");
    }
}

TEST(StringTest, ClearString)
{
    Michka::String test = L"MICHKA TEST";
    ASSERT_TRUE(test == L"MICHKA TEST");
    test.clear();
    ASSERT_TRUE(test == Michka::String::empty);
    ASSERT_TRUE(test.isEmpty());
    ASSERT_FALSE(test.isNotEmpty());
}

TEST(StringTest, CreateDefaultString)
{
    Michka::String test;
    ASSERT_EQ(test.getSize(), 0);
}

TEST(StringTest, CreateString)
{
    {
        Michka::String test8 = "TEST CHAR";
        ASSERT_TRUE(test8 == "TEST CHAR");
        test8 = L"TEST WCHAR";
        ASSERT_TRUE(test8 == "TEST WCHAR");
        test8 = U"TEST CHAR32_T";
        ASSERT_TRUE(test8 == "TEST CHAR32_T");

        Michka::String test16 = "TEST CHAR";
        ASSERT_TRUE(test16 == L"TEST CHAR");
        test16 = L"TEST WCHAR";
        ASSERT_TRUE(test16 == L"TEST WCHAR");
        test16 = U"TEST CHAR32_T";
        ASSERT_TRUE(test16 == L"TEST CHAR32_T");

        Michka::String test32 = "TEST CHAR";
        ASSERT_TRUE(test32 == U"TEST CHAR");
        test32 = L"TEST WCHAR";
        ASSERT_TRUE(test32 == U"TEST WCHAR");
        test32 = U"TEST CHAR32_T";
        ASSERT_TRUE(test32 == U"TEST CHAR32_T");
    }

    {
        Michka::String8 test8 = "TEST CHAR";
        ASSERT_TRUE(test8 == "TEST CHAR");
        test8 = L"TEST WCHAR";
        ASSERT_TRUE(test8 == "TEST WCHAR");
        test8 = U"TEST CHAR32_T";
        ASSERT_TRUE(test8 == "TEST CHAR32_T");

        Michka::String8 test16 = "TEST CHAR";
        ASSERT_TRUE(test16 == L"TEST CHAR");
        test16 = L"TEST WCHAR";
        ASSERT_TRUE(test16 == L"TEST WCHAR");
        test16 = U"TEST CHAR32_T";
        ASSERT_TRUE(test16 == L"TEST CHAR32_T");

        Michka::String8 test32 = "TEST CHAR";
        ASSERT_TRUE(test32 == U"TEST CHAR");
        test32 = L"TEST WCHAR";
        ASSERT_TRUE(test32 == U"TEST WCHAR");
        test32 = U"TEST CHAR32_T";
        ASSERT_TRUE(test32 == U"TEST CHAR32_T");
    }

    {
        Michka::String32 test8 = "TEST CHAR";
        ASSERT_TRUE(test8 == "TEST CHAR");
        test8 = L"TEST WCHAR";
        ASSERT_TRUE(test8 == "TEST WCHAR");
        test8 = U"TEST CHAR32_T";
        ASSERT_TRUE(test8 == "TEST CHAR32_T");

        Michka::String32 test16 = "TEST CHAR";
        ASSERT_TRUE(test16 == L"TEST CHAR");
        test16 = L"TEST WCHAR";
        ASSERT_TRUE(test16 == L"TEST WCHAR");
        test16 = U"TEST CHAR32_T";
        ASSERT_TRUE(test16 == L"TEST CHAR32_T");

        Michka::String32 test32 = "TEST CHAR";
        ASSERT_TRUE(test32 == U"TEST CHAR");
        test32 = L"TEST WCHAR";
        ASSERT_TRUE(test32 == U"TEST WCHAR");
        test32 = U"TEST CHAR32_T";
        ASSERT_TRUE(test32 == U"TEST CHAR32_T");
    }
}

TEST(StringTest, Equal)
{
    {
        Michka::String test = L"MICHKA TEST";
        ASSERT_TRUE(test == L"MICHKA TEST");
        ASSERT_FALSE(test == "MICHKA_TEST");
        ASSERT_FALSE(test == L"MICHKA_TEST");
        ASSERT_FALSE(test == U"MICHKA_TEST");
        ASSERT_FALSE(test == "MICHKA TEST DIFFRENT SIZE");
        ASSERT_FALSE(test == L"MICHKA TEST DIFFRENT SIZE");
        ASSERT_FALSE(test == U"MICHKA TEST DIFFRENT SIZE");
        test = "";
        ASSERT_TRUE(test == L"");
    }
    {
        Michka::String8 test = "MICHKA TEST";
        ASSERT_TRUE(test == "MICHKA TEST");
        ASSERT_FALSE(test == "MICHKA_TEST");
        ASSERT_FALSE(test == L"MICHKA_TEST");
        ASSERT_FALSE(test == U"MICHKA_TEST");
        ASSERT_FALSE(test == "MICHKA TEST DIFFRENT SIZE");
        ASSERT_FALSE(test == L"MICHKA TEST DIFFRENT SIZE");
        ASSERT_FALSE(test == U"MICHKA TEST DIFFRENT SIZE");
        test = "";
        ASSERT_TRUE(test == "");
    }
    {
        Michka::String32 test = U"MICHKA TEST";
        ASSERT_TRUE(test == U"MICHKA TEST");
        ASSERT_FALSE(test == "MICHKA_TEST");
        ASSERT_FALSE(test == L"MICHKA_TEST");
        ASSERT_FALSE(test == U"MICHKA_TEST");
        ASSERT_FALSE(test == "MICHKA TEST DIFFRENT SIZE");
        ASSERT_FALSE(test == L"MICHKA TEST DIFFRENT SIZE");
        ASSERT_FALSE(test == U"MICHKA TEST DIFFRENT SIZE");
        test = "";
        ASSERT_TRUE(test == U"");
    }
}

TEST(StringTest, Find)
{
    Michka::String test = L"Hello World";
    Michka::String test2 = "Hello World Hello";

    ASSERT_EQ(test.find(L'H'), 0);
    ASSERT_EQ(test.find(L'e'), 1);
    ASSERT_EQ(test.find(L'l'), 2);
    ASSERT_EQ(test.find(L'o'), 4);
    ASSERT_EQ(test.find(L'l', 4), 9);
    ASSERT_EQ(test.find(L'd'), 10);
    ASSERT_EQ(test.find(L'T'), Michka::String::notFound);

    ASSERT_EQ(test.findLast(L'H'), 0);
    ASSERT_EQ(test.findLast(L'e'), 1);
    ASSERT_EQ(test.findLast(L'l'), 9);
    ASSERT_EQ(test.findLast(L'o'), 7);
    ASSERT_EQ(test.findLast(L'l', 4), 3);
    ASSERT_EQ(test.findLast(L'l', 3), 3);
    ASSERT_EQ(test.findLast(L'l', 2), 2);
    ASSERT_EQ(test.findLast(L'd'), 10);
    ASSERT_EQ(test.findLast(L'T'), Michka::String::notFound);

    ASSERT_EQ(test.find(L"Hello"), 0);
    ASSERT_EQ(test.find(L"ello"), 1);
    ASSERT_EQ(test.find(L"Hello", 1), Michka::String::notFound);
    ASSERT_EQ(test2.find(L"Hello", 1), 12);
    ASSERT_EQ(test.find(L"World"), 6);
    ASSERT_EQ(test.find(L"World", 6), 6);
    ASSERT_EQ(test.find(L"RandomStuff"), Michka::String::notFound);
    ASSERT_EQ(test.find(L"Hello Random"), Michka::String::notFound);
    ASSERT_EQ(test.find(L"Helloo"), Michka::String::notFound);
    ASSERT_EQ(Michka::String().find(L"RandomStuff"), Michka::String::notFound);
    ASSERT_EQ(Michka::String().find(Michka::String()), Michka::String::notFound);
    ASSERT_EQ(test.find(Michka::String()), Michka::String::notFound);

    ASSERT_EQ(test2.findLast(L"Hello"), 12);
    ASSERT_EQ(test2.findLast(L"ello"), 13);
    ASSERT_EQ(test2.findLast(L"World", 10), Michka::String::notFound);
    ASSERT_EQ(test2.findLast(L"Hello", 16), 0);
    ASSERT_EQ(test2.findLast(L"World"), 6);
    ASSERT_EQ(test2.findLast(L"World", 12), 6);
    ASSERT_EQ(test2.findLast(L"World", 11), 6);
    ASSERT_EQ(test2.findLast(L"RandomStuff"), Michka::String::notFound);
    ASSERT_EQ(test2.findLast(L"Helloo"), Michka::String::notFound);
    ASSERT_EQ(test2.findLast(L"Hello Random"), Michka::String::notFound);
    ASSERT_EQ(Michka::String().findLast(L"RandomStuff"), Michka::String::notFound);
    ASSERT_EQ(Michka::String().findLast(Michka::String()), Michka::String::notFound);
    ASSERT_EQ(test2.findLast(Michka::String()), Michka::String::notFound);
}

TEST(StringTest, GetCharacter)
{
    Michka::String test = L"Hello World";
    ASSERT_EQ(test[0], L'H');
    ASSERT_EQ(test[4], L'o');
    ASSERT_EQ(test[10], L'd');
}

TEST(StringTest, Insert)
{
    ASSERT_EQ(Michka::String("Hello").insert(" World!", 5), "Hello World!");
    ASSERT_EQ(Michka::String("Hello").insert("World!", 0), "World!Hello");
    ASSERT_EQ(Michka::String("Hello").insert("World!", 6), "Hello World!");
}

TEST(StringTest, MoveConstructor)
{
    Michka::String test = L"MICHKA TEST";
    ASSERT_TRUE(test == L"MICHKA TEST");

    Michka::String test2 = std::move(test);
    ASSERT_TRUE(test2 == L"MICHKA TEST");
    ASSERT_TRUE(test.isEmpty());
}

TEST(StringTest, NotEqual)
{
    Michka::String test = L"MICHKA TEST";
    ASSERT_FALSE(test != L"MICHKA TEST");
    ASSERT_TRUE(test != L"MICHKA_TEST");
    ASSERT_TRUE(test != L"MICHKA TEST DIFFRENT SIZE");
}

TEST(StringTest, NumberToString)
{
    ASSERT_TRUE(Michka::String::number(false) == L"false");
    ASSERT_TRUE(Michka::String::number(true) == L"true");
    ASSERT_TRUE(Michka::String::number(1) == L"1");
    ASSERT_TRUE(Michka::String::number(12) == L"12");
    ASSERT_TRUE(Michka::String::number(123) == L"123");
    ASSERT_TRUE(Michka::String::number(2147483647) == L"2147483647");
    ASSERT_TRUE(Michka::String::number(-1) == L"-1");
    ASSERT_TRUE(Michka::String::number(-12) == L"-12");
    ASSERT_TRUE(Michka::String::number(-123) == L"-123");
    ASSERT_TRUE(Michka::String::number(-2147483647) == L"-2147483647");
    ASSERT_TRUE(Michka::String::number(0xf, 16) == L"f");
    ASSERT_TRUE(Michka::String::number(-0xf, 16) == L"-f");
    ASSERT_TRUE(Michka::String::number(0b1010101, 2) == L"1010101");
    ASSERT_TRUE(Michka::String::number(float(3.14f)) == L"3.14");
    ASSERT_TRUE(Michka::String::number(double(3.14159265)) == L"3.14159");
    ASSERT_TRUE(Michka::String::number(long double(3.14159265359)) == L"3.14159");
    ASSERT_TRUE(Michka::String::number(float(-3.14f)) == L"-3.14");
    ASSERT_TRUE(Michka::String::number(double(-3.14159265)) == L"-3.14159");
    ASSERT_TRUE(Michka::String::number(long double(-3.14159265359)) == L"-3.14159");

    ASSERT_TRUE(Michka::String8::number(123) == "123");
    ASSERT_TRUE(Michka::String32::number(123) == U"123");

    EXPECT_THROW({
        Michka::String::number(0xf, 17);
    }, Michka::Exception);
    EXPECT_THROW({
        Michka::String::number(0xf, 1);
    }, Michka::Exception);
}

TEST(StringTest, Prepend)
{
    Michka::String test = "World";
    test.prepend("Hello ");
    ASSERT_EQ(test, "Hello World");
    ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, Remove)
{
    ASSERT_EQ(Michka::String("Hello World").remove(0), "");
    ASSERT_EQ(Michka::String("Hello World").remove(1), "H");
    ASSERT_EQ(Michka::String("Hello World").remove(2), "He");
    ASSERT_EQ(Michka::String("Hello World").remove(2, 2), "Heo World");
    ASSERT_EQ(Michka::String("Hello World").remove(0, 6), "World");
    ASSERT_EQ(Michka::String("Hello World").remove(5, 6), "Hello");
}

TEST(StringTest, Repace)
{
    ASSERT_EQ(Michka::String("Hello World!").replace("test"), "Hello World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("Hello"), " World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("World"), "Hello !");
    ASSERT_EQ(Michka::String("Hello World!").replace("Hello", "", 1), "Hello World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("World", "", 0, 5), "Hello World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("Hello", "Test"), "Test World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("Hello", "World"), "World World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("Hello", "Welcome to"), "Welcome to World!");
    ASSERT_EQ(Michka::String("Hello World!").replace("World", "Test"), "Hello Test!");
    ASSERT_EQ(Michka::String("Hello World!").replace("World", "Hello"), "Hello Hello!");
    ASSERT_EQ(Michka::String("Hello World!").replace("World", "MICHKA the bird!"), "Hello MICHKA the bird!!");

    ASSERT_EQ(Michka::String("Hello World").getReplaced("World", "Test"), "Hello Test");
    ASSERT_EQ(Michka::String("Hello World").getReplaced("World", "Hello"), "Hello Hello");
    ASSERT_EQ(Michka::String("Hello World").getReplaced("World", "MICHKA the bird!"), "Hello MICHKA the bird!");
}

TEST(StringTest, Reverse)
{
    Michka::String test;
    test.reverse();
    ASSERT_TRUE(test == Michka::String::empty);
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

TEST(StringTest, Size)
{
    Michka::String test = L"Hello";
    ASSERT_EQ(test.getSize(), 5);
    test = L"Hello WORLD";
    ASSERT_EQ(test.getSize(), 11);
}

TEST(StringTest, Split)
{
    Michka::String test = L"Hello|World|Welcome|Test";
    Michka::Vector<Michka::String> testResult = {"Hello", "World", "Welcome", "Test"};
    ASSERT_EQ(test.split('|'), testResult);
    ASSERT_EQ(test.split("|"), testResult);

    test = L"Hello,|,World,|Welcome,|,Test";
    testResult = {"Hello", "World,|Welcome", "Test"};
    ASSERT_EQ(test.split(",|,"), testResult);

    testResult = {"Hello,|,World,|Welcome,|,Test"};
    ASSERT_EQ(test.split('\\0'), testResult);
    ASSERT_EQ(test.split('&'), testResult);
    ASSERT_EQ(test.split("&&&"), testResult);

    testResult = {"H", "e", "l", "l", "o", ",", "|", ",", "W", "o", "r", "l", "d", ",", "|", "W", "e", "l", "c", "o", "m", "e", ",", "|", ",", "T", "e", "s", "t"};
    ASSERT_EQ(test.split(""), testResult);


    test = L"";
    testResult = {};
    ASSERT_EQ(test.split(','), testResult);
    ASSERT_EQ(test.split(""), testResult);
}

TEST(StringTest, SubString)
{
    Michka::String test = "Hello World";
    ASSERT_EQ(test.subString(0), "Hello World");
    ASSERT_EQ(test.subString(1), "ello World");
    ASSERT_EQ(test.subString(2), "llo World");
    ASSERT_EQ(test.subString(0, 5), "Hello");
    ASSERT_EQ(test.subString(6, 5), "World");
    ASSERT_EQ(test.subString(0, 0), "");
    test = "";
    ASSERT_EQ(test.subString(0, 1), "");
    ASSERT_EQ(Michka::String::empty.subString(0), "");
    ASSERT_EQ(Michka::String::empty.subString(0, 1), "");
}

TEST(StringTest, ToLower)
{
    ASSERT_EQ(Michka::String("Hello World!").toLower(), "hello world!");
}

TEST(StringTest, ToNumber)
{
    {
        Michka::String test = L"12345";
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

        test = Michka::String::empty;
        ASSERT_EQ(test.toNumber<i64>(), 0);

        test = "NON NUMBER";
        ASSERT_EQ(test.toNumber<i64>(), 0);

        test = "3.1415";
        ASSERT_EQ(test.toNumber<int>(), int(3));
        ASSERT_EQ(test.toNumber<float>(), float(3.1415f));
        ASSERT_EQ(test.toNumber<double>(), double(3.1415));
        ASSERT_EQ(test.toNumber<long double>(), long double(3.1415));

        EXPECT_THROW({
            test.toNumber<int>(17);
        }, Michka::Exception);
        EXPECT_THROW({
            test.toNumber<int>(1);
        }, Michka::Exception);
    }
    {
        Michka::String8 test = "12345";
        ASSERT_EQ(test.toNumber<i16>(), 12345);
        test = "+12345";
        ASSERT_EQ(test.toNumber<i16>(), 12345);
        test = "-12345";
        ASSERT_EQ(test.toNumber<i16>(), -12345);
        test = Michka::String8::empty;
        ASSERT_EQ(test.toNumber<i64>(), 0);
        test = "NON NUMBER";
        ASSERT_EQ(test.toNumber<i64>(), 0);
        test = "3.1415";
        ASSERT_EQ(test.toNumber<float>(), float(3.1415f));
        ASSERT_EQ(test.toNumber<double>(), double(3.1415));
        ASSERT_EQ(test.toNumber<long double>(), long double(3.1415));
    }
    {
        Michka::String32 test = U"12345";
        ASSERT_EQ(test.toNumber<i16>(), 12345);
        test = U"+12345";
        ASSERT_EQ(test.toNumber<i16>(), 12345);
        test = U"-12345";
        ASSERT_EQ(test.toNumber<i16>(), -12345);
        test = Michka::String32::empty;
        ASSERT_EQ(test.toNumber<i64>(), 0);
        test = U"NON NUMBER";
        ASSERT_EQ(test.toNumber<i64>(), 0);
        test = U"3.1415";
        ASSERT_EQ(test.toNumber<float>(), float(3.1415f));
        ASSERT_EQ(test.toNumber<double>(), double(3.1415));
        ASSERT_EQ(test.toNumber<long double>(), long double(3.1415));
    }
}

TEST(StringTest, ToUpper)
{
    ASSERT_EQ(Michka::String("Hello World!").toUpper(), "HELLO WORLD!");
}

TEST(StringTest, Trim)
{
    Michka::String test = "  Hello World   ";
    ASSERT_EQ(test.getLeftTrimed(), "Hello World   ");
    ASSERT_EQ(test.getRightTrimed(), "  Hello World");
    ASSERT_EQ(test.getTrimed(), "Hello World");
    ASSERT_EQ(test.getTrimed("-"), "  Hello World   ");

    test = "--Hello World";
    ASSERT_EQ(test.getLeftTrimed(), "--Hello World");
    ASSERT_EQ(test.getRightTrimed(), "--Hello World");
    ASSERT_EQ(test.getTrimed(), "--Hello World");
    ASSERT_EQ(test.getRightTrimed("-"), "--Hello World");
    ASSERT_EQ(test.getLeftTrimed("-"), "Hello World");
    ASSERT_EQ(test.getTrimed("-"), "Hello World");
    ASSERT_EQ(Michka::String::empty.getTrimed(), "");
}

TEST(StringTest, Unicode)
{
    const char* teststr = "سلام دنیا - 🌍 Hello World 你好，世界 - æ - © - ſ - ◌󠇓 - × - ~ - 𠀁";
    const wchar_t* teststr16 = L"\u0633\u0644\u0627\u0645 \u062F\u0646\u06CC\u0627 - \U0001f30d Hello World \u4F60\u597D\uFF0C\u4E16\u754C - \u00E6 - \u00A9 - \u017F - \u25CC\U000e01d3 - \u00D7 - ~ - \U00020001";
    const char32_t* teststr32 = U"\u0633\u0644\u0627\u0645 \u062F\u0646\u06CC\u0627 - \U0001f30d Hello World \u4F60\u597D\uFF0C\u4E16\u754C - \u00E6 - \u00A9 - \u017F - \u25CC\U000e01d3 - \u00D7 - ~ - \U00020001";

    // UTF 8
    {
        Michka::String test = Michka::String::fromUtf8(teststr);
        ASSERT_TRUE(strcmp(test.toUtf8().cstr(), teststr) == 0);
        ASSERT_TRUE(wcscmp(test.toUtf16().cstr(), teststr16) == 0);
        ASSERT_EQ(Michka::String::fromUtf8("").getLength(), 0);
    }
    {
        Michka::String8 test8 = Michka::String8::fromUtf8(teststr);
        ASSERT_TRUE(strcmp(test8.cstr(), teststr) == 0);
        ASSERT_TRUE(wcscmp(test8.toUtf16().cstr(), teststr16) == 0);
        ASSERT_EQ(Michka::String8::fromUtf8("").getLength(), 0);
    }
    {
        Michka::String32 test32 = Michka::String32::fromUtf8(teststr);
        ASSERT_TRUE(strcmp(test32.toUtf8().cstr(), teststr) == 0);
        ASSERT_TRUE(wcscmp(test32.toUtf16().cstr(), teststr16) == 0);
        ASSERT_EQ(Michka::String32::fromUtf8("").getLength(), 0);
    }

    // UTF 16
    {
        Michka::String test = Michka::String::fromUtf16(teststr16);
        ASSERT_TRUE(strcmp(test.toUtf8().cstr(), teststr) == 0);
        ASSERT_TRUE(wcscmp(test.toUtf16().cstr(), teststr16) == 0);
        ASSERT_EQ(Michka::String::fromUtf16(L"").getLength(), 0);
    }
    {
        Michka::String8 test8 = Michka::String8::fromUtf16(teststr16);
        ASSERT_TRUE(strcmp(test8.cstr(), teststr) == 0);
        ASSERT_TRUE(wcscmp(test8.toUtf16().cstr(), teststr16) == 0);
        ASSERT_EQ(Michka::String8::fromUtf16(L"").getLength(), 0);
    }
    {
        Michka::String32 test32 = Michka::String32::fromUtf16(teststr16);
        ASSERT_TRUE(strcmp(test32.toUtf8().cstr(), teststr) == 0);
        ASSERT_TRUE(wcscmp(test32.toUtf16().cstr(), teststr16) == 0);
        ASSERT_EQ(Michka::String32::fromUtf16(L"").getLength(), 0);
    }

    // UTF 32
    {
        Michka::String test = Michka::String::fromUtf32(teststr32);
        ASSERT_TRUE(strcmp(test.toUtf8().cstr(), teststr) == 0);
        ASSERT_TRUE(memcmp(test.toUtf32().cstr(), teststr32, test.toUtf32().getSize() * sizeof(char32_t)) == 0);
        ASSERT_EQ(Michka::String::fromUtf32(U"").getLength(), 0);
    }
    {
        Michka::String8 test8 = Michka::String8::fromUtf32(teststr32);
        ASSERT_TRUE(strcmp(test8.cstr(), teststr) == 0);
        ASSERT_TRUE(memcmp(test8.toUtf32().cstr(), teststr32, test8.toUtf32().getSize() * sizeof(char32_t)) == 0);
        ASSERT_EQ(Michka::String8::fromUtf32(U"").getLength(), 0);
    }
    {
        Michka::String32 test32 = Michka::String32::fromUtf32(teststr32);
        ASSERT_TRUE(strcmp(test32.toUtf8().cstr(), teststr) == 0);
        ASSERT_TRUE(memcmp(test32.toUtf32().cstr(), teststr32, test32.toUtf32().getSize() * sizeof(char32_t)) == 0);
        ASSERT_EQ(Michka::String32::fromUtf32(U"").getLength(), 0);
    }

    // No Convert Test
    {
        Michka::String test = teststr16;
        ASSERT_TRUE(wcscmp(test.toUtf16().cstr(), teststr16) == 0);
    }
    {
        Michka::String8 test8 = teststr;
        ASSERT_TRUE(strcmp(test8.toUtf8().cstr(), teststr) == 0);
    }
    {
        Michka::String32 test = teststr32;
        ASSERT_TRUE(memcmp((void*)test.toUtf32().cstr(), (void*)teststr32, test.getSize() * sizeof(char32_t)) == 0);
    }
}
