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
#include "Core/Container/Variant.h"
#include "../../Classes/Student.h"
#include "../../Classes/Animal.h"

TEST(VariantTest, Compare)
{
    {
        Michka::Variant a;
        ASSERT_EQ(a, nullptr);
        ASSERT_EQ(a, Michka::Variant());
        ASSERT_NE(a, "Hello World");
    }
    {
        Michka::Variant a = 4;
        ASSERT_EQ(a, 4);
        ASSERT_EQ(a, Michka::Variant(4));
        ASSERT_NE(a, 5);
    }
    {
        Michka::Variant a = true;
        ASSERT_EQ(a, true);
        ASSERT_EQ(a, Michka::Variant(true));
        ASSERT_NE(a, false);
        ASSERT_NE(a, 5);
    }
    {
        Michka::Variant a = 3.14;
        ASSERT_EQ(a, 3.14);
        ASSERT_EQ(a, Michka::Variant(3.14));
        ASSERT_NE(a, 6.8);
        ASSERT_NE(a, "hello");
    }
    {
        Michka::Variant a = "Hello World";
        ASSERT_EQ(a, "Hello World");
        ASSERT_EQ(a, Michka::Variant("Hello World"));
        ASSERT_NE(a, 47);
        ASSERT_NE(a, "hello");
    }
    {
        std::initializer_list<int> test = {1, 2, 4};
        std::initializer_list<int> test2 = {1, 2};
        Michka::Variant a = {1, 2, 4};
        ASSERT_EQ(a, test);
        ASSERT_EQ(a, Michka::List<Michka::Variant>({1, 2, 4}));
        ASSERT_EQ(a, Michka::Variant({1, 2, 4}));
        ASSERT_NE(a, test2);
        ASSERT_NE(a, "hello");
    }
    {
        Michka::Variant a = Student("test");
        ASSERT_EQ(a, Student("test"));
        Student test = a.to<Student>();
        ASSERT_NE(a, Student("test2"));
        ASSERT_NE(a, "test");
    }
    {
        auto test = Student("test");
        auto test2 = Student("test2");
        Michka::Variant a = &test;
        Michka::Variant b = &test;
        Michka::Variant c = &test2;

        ASSERT_TRUE(a == Michka::Variant(&test));
        ASSERT_EQ(a, b);
        ASSERT_NE(a, c);
    }
}

TEST(VariantTest, Create)
{
    {
        Michka::Variant a;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeNull);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 0);
        ASSERT_EQ(a.to<Michka::String>(), "null");
        ASSERT_EQ(a.toString(), "null");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        Michka::Variant b = a;
        ASSERT_EQ(b.getType(), Michka::Variant::Type::typeNull);
        ASSERT_TRUE(b.isConvertibleTo<int>());
        ASSERT_EQ(b.to<int>(), 0);
    }
    {
        Michka::Variant a(nullptr);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeNull);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 0);
        ASSERT_EQ(a.toString(), "null");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());
    }
    {
        Michka::Variant a(true);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeBool);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 1);
        ASSERT_TRUE(a.isConvertibleTo<bool>());
        ASSERT_EQ(a.to<bool>(), true);
        ASSERT_EQ(a.toString(), "true");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        a = false;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeBool);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 0);
        ASSERT_TRUE(a.isConvertibleTo<bool>());
        ASSERT_EQ(a.to<bool>(), 0);
        ASSERT_EQ(a.toString(), "false");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        a = nullptr;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeNull);
        ASSERT_TRUE(a.isConvertibleTo<bool>());
        ASSERT_EQ(a.to<bool>(), false);
        ASSERT_EQ(a.toString(), "null");
    }
    {
        Michka::Variant a(5);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 5.0f);
        ASSERT_TRUE(a.isConvertibleTo<bool>());
        ASSERT_EQ(a.to<bool>(), true);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "5");

        a = 8;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_EQ(a.to<int>(), 8);
        ASSERT_EQ(a.to<bool>(), true);
        ASSERT_EQ(a.toString(), "8");

        a = 3.14;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_EQ(a.to<bool>(), true);
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);
        ASSERT_EQ(a.toString(), "3.14");
    }
    {
        Michka::Variant a(unsigned int(5));
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<unsigned int>());
        ASSERT_EQ(a.to<unsigned int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 5.0f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        a = unsigned int (7);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<unsigned int>());
        ASSERT_EQ(a.to<unsigned int>(), 7);
    }
    {
        Michka::Variant a(short int(5));
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<short int>());
        ASSERT_EQ(a.to<short int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 5.0f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "5");

        a = short int (7);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<short int>());
        ASSERT_EQ(a.to<short int>(), 7);
    }
    {
        Michka::Variant a(unsigned short int(5));
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<unsigned short int>());
        ASSERT_EQ(a.to<unsigned short int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 5.0f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "5");

        a = unsigned short int (7);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<unsigned short int>());
        ASSERT_EQ(a.to<unsigned short int>(), 7);
    }
    {
        Michka::Variant a(long long int(5));
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<long long int>());
        ASSERT_EQ(a.to<long long int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 5.0f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "5");

        a = long long int (7);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<long long int>());
        ASSERT_EQ(a.to<long long int>(), 7);
    }
    {
        Michka::Variant a(unsigned long long int(5));
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<unsigned long long int>());
        ASSERT_EQ(a.to<unsigned long long int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 5.0f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "5");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "5");

        a = unsigned long long int (7);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_TRUE(a.isConvertibleTo<unsigned long long int>());
        ASSERT_EQ(a.to<unsigned long long int>(), 7);
    }
    {
        Michka::Variant a(char('w'));
        ASSERT_TRUE(a.isConvertibleTo<char>());
        ASSERT_EQ(a.to<char>(), char('w'));
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        a = char('e');
        ASSERT_TRUE(a.isConvertibleTo<char>());
        ASSERT_EQ(a.to<char>(), char('e'));
    }
    {
        Michka::Variant a(unsigned char('w'));
        ASSERT_TRUE(a.isConvertibleTo<unsigned char>());
        ASSERT_EQ(a.to<unsigned char>(), unsigned char('w'));
        ASSERT_FALSE(a.isConvertibleTo<Student>());

        a = unsigned char('e');
        ASSERT_TRUE(a.isConvertibleTo<unsigned char>());
        ASSERT_EQ(a.to<unsigned char>(), unsigned char('e'));
    }
    {
        Michka::Variant a(wchar_t(L'w'));
        ASSERT_TRUE(a.isConvertibleTo<wchar_t>());
        ASSERT_EQ(a.to<wchar_t>(), wchar_t(L'w'));
        ASSERT_FALSE(a.isConvertibleTo<Student>());

        a = wchar_t('e');
        ASSERT_TRUE(a.isConvertibleTo<wchar_t>());
        ASSERT_EQ(a.to<wchar_t>(), wchar_t('e'));
    }
    {
        Michka::Variant a(char16_t('w'));
        ASSERT_TRUE(a.isConvertibleTo<char16_t>());
        ASSERT_EQ(a.to<char16_t>(), char16_t('w'));
        ASSERT_FALSE(a.isConvertibleTo<Student>());

        a = char16_t('e');
        ASSERT_TRUE(a.isConvertibleTo<char16_t>());
        ASSERT_EQ(a.to<char16_t>(), char16_t('e'));
    }
    {
        Michka::Variant a(char32_t('w'));
        ASSERT_TRUE(a.isConvertibleTo<char32_t>());
        ASSERT_EQ(a.to<char32_t>(), char32_t('w'));
        ASSERT_FALSE(a.isConvertibleTo<Student>());

        a = char32_t('e');
        ASSERT_TRUE(a.isConvertibleTo<char32_t>());
        ASSERT_EQ(a.to<char32_t>(), char32_t('e'));
    }
    {
        Michka::Variant a(3.14f);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "3.14");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "3.14");

        a = 9.99f;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_EQ(a.to<int>(), 9);
        ASSERT_FLOAT_EQ(a.to<float>(), 9.99f);
        ASSERT_EQ(a.toString(), "9.99");
    }
    {
        Michka::Variant a(3.14);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "3.14");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.toString(), "3.14");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        a = 9.99;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_EQ(a.to<int>(), 9);
        ASSERT_FLOAT_EQ(a.to<float>(), 9.99f);
        ASSERT_EQ(a.toString(), "9.99");

        Michka::Variant b = a;
        ASSERT_EQ(b.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_FLOAT_EQ(b.to<float>(), 9.99f);
    }
    {
        Michka::Variant a("3.14");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_TRUE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_TRUE(a.isConvertibleTo<float>());
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);
        ASSERT_TRUE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Michka::String>(), "3.14");
        ASSERT_EQ(a.toString(), "3.14");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        a = "Hello World";
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello World");
        ASSERT_EQ(a.to<Michka::String8>(), "Hello World");
        ASSERT_EQ(a.to<Michka::String32>(), U"Hello World");
        ASSERT_EQ(a.toString(), "Hello World");
        ASSERT_TRUE(wcscmp(a.to<const wchar_t*>(), L"Hello World") == 0);

        Michka::Variant b = a;
        ASSERT_EQ(b.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(b.to<Michka::String>(), "Hello World");
    }
    {
        Michka::Variant a(L"Hello");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello");

        a = L"Hello World";
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello World");
    }
    {
        Michka::Variant a(U"Hello");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello");

        a = U"Hello World";
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello World");
    }
    {
        Michka::Variant a(Michka::String("Hello"));
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello");

        a = Michka::String("Hello World");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello World");
    }
    {
        Michka::Variant a = {1, 2, 4};
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeArray);
        ASSERT_TRUE(a.isConvertibleTo<Michka::List<Michka::Variant>>());
        ASSERT_EQ(a.to<Michka::List<Michka::Variant>>(), Michka::List({1, 2, 4}));
        ASSERT_FALSE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.toString(), "{1,2,4}");
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_EQ(a.to<Student>(), Student());

        Michka::Variant b = a;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeArray);
        ASSERT_TRUE(a.isConvertibleTo<Michka::List<Michka::Variant>>());
        ASSERT_EQ(a.to<Michka::List<Michka::Variant>>(), Michka::List({1, 2, 4}));
    }
    {
        Michka::Variant a = Student("test");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeCustom);
        ASSERT_TRUE(a.isConvertibleTo<Student>());
        ASSERT_TRUE(a.isConvertibleTo<Student*>());
        ASSERT_FALSE(a.isConvertibleTo<Michka::String>());
        ASSERT_EQ(a.to<Student>().getName(), "test");
        ASSERT_EQ(a.to<Student*>()->getName(), "test");
        ASSERT_EQ(a.toString(), "Unknown custom variant");
        ASSERT_FALSE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 0);

        a = Student("Hello World");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeCustom);
        ASSERT_EQ((Student)a, Student("Hello World"));
        ASSERT_EQ(a.to<Student>().getName(), "Hello World");

        a.to<Student*>()->setName("Changed");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeCustom);
        ASSERT_EQ(a.to<Student>().getName(), "Changed");

        a = Animal("Cat");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeCustom);
        ASSERT_EQ(a.to<Animal>().getName(), "Cat");
        ASSERT_EQ(a.toString(), "Animal(Cat)");

        Michka::Variant b = a;
        ASSERT_EQ(b.getType(), Michka::Variant::Type::typeCustom);
        ASSERT_EQ(a.to<Animal>().getName(), "Cat");
        ASSERT_EQ(a.toString(), "Animal(Cat)");
    }
    {
        Student test("Hello World");
        Michka::Variant a = &test;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeReference);
        ASSERT_TRUE(a.isConvertibleTo<Student>());
        ASSERT_TRUE(a.isConvertibleTo<Student*>());
        ASSERT_EQ(a.to<Student>().getName(), "Hello World");
        ASSERT_EQ(a.to<Student*>()->getName(), "Hello World");
        ASSERT_EQ(a.toString(), "Unknown reference variant");
        ASSERT_FALSE(a.isConvertibleTo<int>());
        ASSERT_EQ(a.to<int>(), 0);

        a.to<Student*>()->setName("Changed");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeReference);
        ASSERT_EQ(test.getName(), "Changed");
        ASSERT_EQ(a.to<Student*>()->getName(), "Changed");

        Animal test2("Fish");
        a = &test2;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeReference);
        ASSERT_FALSE(a.isConvertibleTo<Student>());
        ASSERT_FALSE(a.isConvertibleTo<Student*>());
        ASSERT_TRUE(a.isConvertibleTo<Animal>());
        ASSERT_TRUE(a.isConvertibleTo<Animal*>());
        ASSERT_EQ(a.to<Animal>().getName(), "Fish");
        ASSERT_EQ(a.to<Animal*>()->getName(), "Fish");
        ASSERT_EQ(a.toString(), "Animal(Fish)");

        Michka::Variant b = a;
        ASSERT_EQ(b.getType(), Michka::Variant::Type::typeReference);
        ASSERT_EQ(b.to<Animal>().getName(), "Fish");
        ASSERT_EQ(b.to<Animal*>()->getName(), "Fish");
        ASSERT_EQ(b.toString(), "Animal(Fish)");

        b.to<Animal*>()->setName("Changed");
        ASSERT_EQ(test2.getName(), "Changed");
        ASSERT_EQ(b.to<Animal>().getName(), "Changed");
        ASSERT_EQ(b.to<Animal*>()->getName(), "Changed");
        ASSERT_EQ(a.to<Animal>().getName(), "Changed");
        ASSERT_EQ(a.to<Animal*>()->getName(), "Changed");
    }
    {
        int test = 47;
        Michka::Variant a = &test;

        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeReference);
        ASSERT_EQ(a.to<int>(), 47);
        ASSERT_EQ(*(a.to<int*>()), 47);
        ASSERT_EQ(a.toString(), "47");

        *(a.to<int*>()) = 90;
        ASSERT_EQ(test, 90);
        ASSERT_EQ(a.to<int>(), 90);
        ASSERT_EQ(*(a.to<int*>()), 90);
        ASSERT_EQ(a.toString(), "90");
    }
}
