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
#include "Core/Container/List.h"
#include "Core/Foundation/Types.h"
#include "Core/Helpers.h"
#include "Core/Reflection/Type.h"
#include "../../Classes/Person.h"

TEST(ListTest, ClearList)
{
    Michka::List<int> a = {1, 2};
    ASSERT_EQ(a.getSize(), 2);
    a.clear();
    ASSERT_EQ(a.getSize(), 0);
}

TEST(ListTest, Compare)
{
    Michka::List<int> a = {1, 2, 3};
    Michka::List<int> b = {1, 2, 3};
    Michka::List<int> c = {3, 2, 1};
    Michka::List<int> d = {1, 2, 3, 4};

    ASSERT_EQ(a, b);
    ASSERT_NE(a, c);
    ASSERT_NE(a, d);
}

TEST(ListTest, ConstantList)
{
    const Michka::List<int> a = {1, 2};
    ASSERT_EQ(a.getSize(), 2);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[1], 2);
    ASSERT_EQ(a.first(), 1);
    ASSERT_EQ(a.last(), 2);
}

TEST(ListTest, Empty)
{
    Michka::List<int> a;
    Michka::List<int> b = {1, 2};

    ASSERT_TRUE(a.isEmpty());
    ASSERT_TRUE(b.isNotEmpty());
}

TEST(ListTest, Filter)
{
    auto filterFunction = [] (const int& _item)
    {
        return _item % 2 == 0;
    };
    Michka::List<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Michka::List<int> b = a.getFiltered(filterFunction);

    ASSERT_EQ(a.getSize(), 10);
    ASSERT_EQ(b.getSize(), 5);
    ASSERT_EQ(b[0], 2);
    ASSERT_EQ(b[1], 4);
    ASSERT_EQ(b[2], 6);
    ASSERT_EQ(b[3], 8);
    ASSERT_EQ(b[4], 10);

    a.filter(filterFunction);
    ASSERT_EQ(a[0], 2);
    ASSERT_EQ(a[1], 4);
    ASSERT_EQ(a[2], 6);
    ASSERT_EQ(a[3], 8);
    ASSERT_EQ(a[4], 10);
}

TEST(ListTest, Implode)
{
    {
        Michka::List<int> a = {1, 2, 4};
        ASSERT_EQ(a.implode(), "1,2,4");
        ASSERT_EQ(a.implode("|"), "1|2|4");
    }
    {
        Michka::List<Michka::String> a = {"a", "b", "c"};
        ASSERT_EQ(a.implode(), "a,b,c");
        ASSERT_EQ(a.implode("|"), "a|b|c");
    }
    {
        Michka::List<Person> a = {Person("a"), Person("b"), Person("c")};
        ASSERT_EQ(a.implode(), "Person(a),Person(b),Person(c)");
        ASSERT_EQ(a.implode("|"), "Person(a)|Person(b)|Person(c)");
    }
    {
        Michka::List<Person*> a = {new Person("a"), new Person("b"), new Person("c")};
        ASSERT_EQ(a.implode(), "Person(a),Person(b),Person(c)");
        ASSERT_EQ(a.implode("|"), "Person(a)|Person(b)|Person(c)");
        for (auto i : a)
        {
            delete i;
        }
    }
}

TEST(ListTest, Insert)
{
    Michka::List<int> a = {1, 2};
    Michka::List<Person> b = {Person("A"), Person("B")};

    int testInsert = 40;
    Person testInsertMove("GG");
    a.insert(0, 10);
    a.insert(2, {20, 200});
    a.insert(0, testInsert);
    a.insert(6, 30);
    a.insert(6, 50);
    b.insert(0, Person("AA"));
    b.insert(2, {Person("BB"), Person("BBB")});
    b.insert(0, Person("DD"));
    b.insert(6, Person("CC"));
    b.insert(6, std::move(testInsertMove));

    ASSERT_EQ(a.getSize(), 8);
    ASSERT_EQ(b.getSize(), 8);
    ASSERT_TRUE(a[0] == 40);
    ASSERT_TRUE(b[0] == Person("DD"));
    ASSERT_TRUE(a[1] == 10);
    ASSERT_TRUE(b[1] == Person("AA"));
    ASSERT_TRUE(a[2] == 1);
    ASSERT_TRUE(b[2] == Person("A"));
    ASSERT_TRUE(a[3] == 20);
    ASSERT_TRUE(b[3] == Person("BB"));
    ASSERT_TRUE(a[4] == 200);
    ASSERT_TRUE(b[4] == Person("BBB"));
    ASSERT_TRUE(a[5] == 2);
    ASSERT_TRUE(b[5] == Person("B"));
    ASSERT_TRUE(a[6] == 50);
    ASSERT_TRUE(b[6] == Person("GG"));
    ASSERT_TRUE(a[7] == 30);
    ASSERT_TRUE(b[7] == Person("CC"));

    for (u32 i=0; i < 100; i++)
    {
        a.pushBack(i);
    }
    for (u32 i=0; i < 100; i++)
    {
        a.pushBack(2 * i);
    }
    ASSERT_EQ(a.getSize(), 208);

    Michka::List<int> c;
    c.insert(0, a);
    ASSERT_EQ(c.getSize(), 208);
    ASSERT_TRUE(c[0] == 40);
    ASSERT_TRUE(c[1] == 10);
    ASSERT_TRUE(c[2] == 1);
}

TEST(ListTest, Iterator)
{
    Michka::List<int> a = {1, 2, 3};
    const Michka::List<int> b = {4, 6, 8, 10};
    u32 count = 0;
    u32 sum = 0;
    for (auto i: a)
    {
        count++;
        sum += i;
    }
    ASSERT_EQ(count, 3);
    ASSERT_EQ(sum, 6);

    count = 0;
    sum = 0;
    for (auto i: b)
    {
        count++;
        sum += i;
    }
    ASSERT_EQ(count, 4);
    ASSERT_EQ(sum, 28);
}

TEST(ListTest, OperatorAdd)
{
    Michka::List<int> a = {1, 2, 3, 4, 5};
    Michka::List<int> b = {5, 6, 7, 8, 9, 10};
    Michka::List<int> ab = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10};

    ASSERT_EQ(a + b, ab);

    a += b;
    ASSERT_EQ(a, ab);
}

TEST(ListTest, Push)
{
    Michka::List<int> a = {1};
    Michka::List<Person> b = {Person("A")};

    a.pushBack(2);
    b.pushBack(Person("B"));

    ASSERT_EQ(a.getSize(), 2);
    ASSERT_EQ(b.getSize(), 2);
    ASSERT_TRUE(a[0] == 1);
    ASSERT_TRUE(b[0] == Person("A"));
    ASSERT_TRUE(a[1] == 2);
    ASSERT_TRUE(b[1] == Person("B"));

    a.pushFront(50);
    b.pushFront(Person("Hello"));
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(b.getSize(), 3);
    ASSERT_TRUE(a[0] == 50);
    ASSERT_TRUE(b[0] == Person("Hello"));
    ASSERT_TRUE(a[1] == 1);
    ASSERT_TRUE(b[1] == Person("A"));
    ASSERT_TRUE(a[2] == 2);
    ASSERT_TRUE(b[2] == Person("B"));

    a << 500 << 5000;
    b << Person("Hi") << Person("Hi Again");
    ASSERT_EQ(a.getSize(), 5);
    ASSERT_EQ(b.getSize(), 5);
    ASSERT_TRUE(a[0] == 50);
    ASSERT_TRUE(b[0] == Person("Hello"));
    ASSERT_TRUE(a[1] == 1);
    ASSERT_TRUE(b[1] == Person("A"));
    ASSERT_TRUE(a[2] == 2);
    ASSERT_TRUE(b[2] == Person("B"));
    ASSERT_TRUE(a[3] == 500);
    ASSERT_TRUE(b[3] == Person("Hi"));
    ASSERT_TRUE(a[4] == 5000);
    ASSERT_TRUE(b[4] == Person("Hi Again"));
}

TEST(ListTest, Remove)
{
    Michka::List<int> a = {2, 4, 6, 8, 10, 2};
    a.remove(1);
    ASSERT_EQ(a.getSize(), 5);
    ASSERT_EQ(a[1], 6);
    ASSERT_EQ(a[4], 2);

    a.remove(1, 2);
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(a[1], 10);
    ASSERT_EQ(a[2], 2);

    a.remove(3); // remove out of range
    a.remove(5);
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(a[1], 10);
    ASSERT_EQ(a[2], 2);

    a.remove(1, Michka::u32Info::max);
    ASSERT_EQ(a.getSize(), 1);
    ASSERT_EQ(a[0], 2);

    a.remove(0);
    ASSERT_EQ(a.getSize(), 0);
}

TEST(ListTest, Reverse)
{
    Michka::List<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Michka::List<int> aReversed = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Michka::List<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Michka::List<int> bReversed = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    ASSERT_EQ(a.getReversed(), aReversed);
    ASSERT_EQ(b.getReversed(), bReversed);
}

TEST(ListTest, Search)
{
    Michka::List<int> a = {2, 4, 6, 8, 10, 2};
    ASSERT_EQ(a.indexOf(3), a.notFound);
    ASSERT_EQ(a.indexOf(2), 0);
    ASSERT_EQ(a.indexOf(2, 1), 5);
    ASSERT_EQ(a.indexOf(4, 1), 1);
    ASSERT_EQ(a.indexOf(4, 2), a.notFound);
    ASSERT_EQ(a.lastIndexOf(2), 5);
    ASSERT_EQ(a.lastIndexOf(2, 4), 0);
    ASSERT_EQ(a.lastIndexOf(4), 1);
    ASSERT_EQ(a.lastIndexOf(4, 0), a.notFound);


    Michka::List<Person> b = {Person("michka")};
    ASSERT_EQ(b.indexOf(Person("michka")), 0);
    ASSERT_EQ(b.indexOf(Person("sparrow")), b.notFound);

    auto compareCallback = [] (const Person& _a, const Michka::String& _b)
    {
        return _a.getName() == _b;
    };

    auto compareCallback2a = [] (const Person& _a)
    {
        return _a.getName() == "michka";
    };

    auto compareCallback2b = [] (const Person& _a)
    {
        return _a.getName() == "test";
    };

    ASSERT_EQ(b.indexOf<Michka::String>(compareCallback, Michka::String("michka")), 0);
    ASSERT_EQ(b.indexOf<Michka::String>(compareCallback, Michka::String("test")), b.notFound);

    ASSERT_EQ(b.indexOf(compareCallback2a), 0);
    ASSERT_EQ(b.indexOf(compareCallback2b), b.notFound);

    ASSERT_EQ(b.lastIndexOf<Michka::String>(compareCallback, Michka::String("michka")), 0);
    ASSERT_EQ(b.lastIndexOf<Michka::String>(compareCallback, Michka::String("test")), b.notFound);

    ASSERT_EQ(b.lastIndexOf(compareCallback2a), 0);
    ASSERT_EQ(b.lastIndexOf(compareCallback2b), b.notFound);
}

TEST(ListTest, Set)
{
    Michka::List<int> a = {1};
    Michka::List<Person> b = {Person("A")};
    Michka::List<int> c;
    ASSERT_EQ(a.getSize(), 1);
    ASSERT_EQ(b.getSize(), 1);
    ASSERT_TRUE(a[0] == 1);
    ASSERT_TRUE(b[0] == Person("A"));
    ASSERT_TRUE(a.first() == 1);
    ASSERT_TRUE(b.first() == Person("A"));
    ASSERT_TRUE(a.last() == 1);
    ASSERT_TRUE(b.last() == Person("A"));

    a = {10, 20, 30};
    b = {Person("AA"), Person("BB"), Person("CC")};
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(b.getSize(), 3);
    ASSERT_TRUE(a[0] == 10);
    ASSERT_TRUE(b[0] == Person("AA"));
    ASSERT_TRUE(a[1] == 20);
    ASSERT_TRUE(b[1] == Person("BB"));
    ASSERT_TRUE(a[2] == 30);
    ASSERT_TRUE(b[2] == Person("CC"));
    ASSERT_TRUE(a.first() == 10);
    ASSERT_TRUE(b.first() == Person("AA"));
    ASSERT_TRUE(a.last() == 30);
    ASSERT_TRUE(b.last() == Person("CC"));

    a = Michka::List<int>({1, 2, 3});
    b = Michka::List<Person>({Person("A"), Person("B"), Person("C")});
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(b.getSize(), 3);
    ASSERT_TRUE(a[0] == 1);
    ASSERT_TRUE(b[0] == Person("A"));
    ASSERT_TRUE(a[1] == 2);
    ASSERT_TRUE(b[1] == Person("B"));
    ASSERT_TRUE(a[2] == 3);
    ASSERT_TRUE(b[2] == Person("C"));
    ASSERT_TRUE(a.first() == 1);
    ASSERT_TRUE(b.first() == Person("A"));
    ASSERT_TRUE(a.last() == 3);
    ASSERT_TRUE(b.last() == Person("C"));

    c = a;
    ASSERT_EQ(c.getSize(), 3);
    ASSERT_TRUE(c[0] == 1);
    ASSERT_TRUE(c[1] == 2);
    ASSERT_TRUE(c[2] == 3);
    ASSERT_TRUE(c.first() == 1);
    ASSERT_TRUE(c.last() == 3);

    c = {};
    ASSERT_EQ(c.getSize(), 0);
    c = std::move(a);
    ASSERT_EQ(c.getSize(), 3);
    ASSERT_TRUE(c[0] == 1);
    ASSERT_TRUE(c[1] == 2);
    ASSERT_TRUE(c[2] == 3);
    ASSERT_TRUE(c.first() == 1);
    ASSERT_TRUE(c.last() == 3);
    ASSERT_EQ(a.getSize(), 0);
}

TEST(ListTest, Sort)
{
    {
        Michka::List<int> a = {4, 7, 1779, 832, 4349, 2476, 3176, 3894, 1219, 1537, 910, 2699, 1207, 2858, 3850, 2871, 4937, 4954, 2759, 2254, 3414, 1860, 3686, 8, 5};
        Michka::List<int> aSorted = {4, 5, 7, 8, 832, 910, 1207, 1219, 1537, 1779, 1860, 2254, 2476, 2699, 2759, 2858, 2871, 3176, 3414, 3686, 3850, 3894, 4349, 4937, 4954};

        ASSERT_EQ(a.getSorted(), aSorted);
        ASSERT_EQ(a.getSorted(Michka::SortDirection::descending), aSorted.getReversed());
    }
    {
        Michka::List<Michka::String> a = {"Hello", "Hi", "World", "This is awesome", "Michka"};
        Michka::List<Michka::String> aSorted = {"Hi", "World", "Hello", "Michka", "This is awesome"};
        Michka::List<Michka::String> b;

        b = a.getSorted([] (const Michka::String& a, const Michka::String& b)
        {
            return a.getLength() < b.getLength();
        });
        ASSERT_TRUE(b == aSorted);

        b = a.getSorted([] (const Michka::String& a, const Michka::String& b)
        {
            return a.getLength() > b.getLength();
        });
        ASSERT_TRUE(b == aSorted.getReversed());
    }
}

TEST(ListTest, Swap)
{
    Michka::List<int> a = {1, 2, 3, 4, 5};
    Michka::List<int> b = {5, 6, 7, 8, 9, 10};
    Michka::List<int> c = a;
    Michka::List<int> d = b;

    a.swap(b);

    ASSERT_EQ(b, c);
    ASSERT_EQ(a, d);

    a.swap(0, 4);

    ASSERT_EQ(a[0], 9);
    ASSERT_EQ(a[4], 5);
}

TEST(ListTest, TakeAndPop)
{
    Michka::List<int> a = {1, 2, 4, 9, 10};

    ASSERT_EQ(a.popBack(), 10);
    ASSERT_EQ(a.getSize(), 4);
    ASSERT_EQ(a[3], 9);

    ASSERT_EQ(a.popFront(), 1);
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(a[0], 2);
    ASSERT_EQ(a[1], 4);
    ASSERT_EQ(a[2], 9);

    ASSERT_EQ(a.take(1), 4);
    ASSERT_EQ(a.getSize(), 2);
    ASSERT_EQ(a[0], 2);
    ASSERT_EQ(a[1], 9);

    ASSERT_EQ(a.popFront(), 2);
    ASSERT_EQ(a.popBack(), 9);
}
