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
#include "Core/Container/Map.h"
#include "Core/Container/String.h"
#include "Core/Foundation/Types.h"
#include "../../Classes/Person.h"

TEST(MapTest, At)
{
    Michka::Map<Michka::String, int> test = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    ASSERT_EQ(test.at(0).key(), "a");
    ASSERT_EQ(test.at(1).key(), "b");
    ASSERT_EQ(test.at(2).key(), "c");

    ASSERT_EQ(test.at(0).value(), 1);
    ASSERT_EQ(test.at(1).value(), 2);
    ASSERT_EQ(test.at(2).value(), 3);
}

TEST(MapTest, Compare)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    Michka::Map<Michka::String, int> b = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    Michka::Map<Michka::String, int> c = {
        {"a", 1},
        {"b", 2},
        {"c", 4}
    };
    Michka::Map<Michka::String, int> d = {
        {"w", 4},
        {"x", 6},
        {"y", 8},
        {"z", 10},
    };

    ASSERT_TRUE(a == b);
    ASSERT_TRUE(a != c);
    ASSERT_TRUE(a != d);
}

TEST(MapTest, CreateDefault)
{
    Michka::Map<Michka::String, Michka::String> test;
    ASSERT_EQ(test.getSize(), 0);
}

TEST(MapTest, Filter)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3},
        {"d", 4},
        {"e", 5},
        {"f", 6},
        {"g", 7},
        {"h", 8},
        {"i", 9},
    };

    Michka::Map<Michka::String, int> aFiltered = a.getFiltered([] (auto element)
    {
        return element.value() % 2 == 0;
    });

    ASSERT_EQ(aFiltered.getSize(), 4);
    ASSERT_EQ(aFiltered["b"], 2);

    aFiltered.filter([] (auto element)
    {
        return element.key() == "b";
    });

    ASSERT_EQ(aFiltered.getSize(), 1);
    ASSERT_EQ(aFiltered["b"], 2);
}

TEST(MapTest, GetValue)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
    };

    ASSERT_EQ(a.getValue("a", 10), 1);
    ASSERT_EQ(a.getValue("b", 20), 2);
    ASSERT_EQ(a.getValue("c", 30), 30);
}

TEST(MapTest, HasKey)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };

    ASSERT_TRUE(a.hasKey("a"));
    ASSERT_TRUE(a.hasKey("b"));
    ASSERT_TRUE(a.hasKey("c"));
    ASSERT_FALSE(a.hasKey("d"));
    ASSERT_FALSE(a.hasKey("abc"));
}

TEST(MapTest, HasValue)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };

    ASSERT_TRUE(a.hasValue(1));
    ASSERT_TRUE(a.hasValue(2));
    ASSERT_TRUE(a.hasValue(3));
    ASSERT_FALSE(a.hasValue(4));
}

TEST(MapTest, IsEmpty)
{
    Michka::Map<Michka::String, Person> a;
    Michka::Map<Michka::String, Person> b = {
        {"y", Person("person y")},
    };

    ASSERT_TRUE(a.isEmpty());
    ASSERT_TRUE(b.isNotEmpty());
}

TEST(MapTest, Iterator)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    Michka::Map<Michka::String, int> b = {
        {"w", 4},
        {"x", 6},
        {"y", 8},
        {"z", 10},
    };
    u32 count = 0;
    u32 sum = 0;
    for (auto i: a)
    {
        count++;
        sum += i.value();
    }
    ASSERT_EQ(count, 3);
    ASSERT_EQ(sum, 6);

    count = 0;
    sum = 0;
    for (auto i: b)
    {
        count++;
        sum += i.value();
    }
    ASSERT_EQ(count, 4);
    ASSERT_EQ(sum, 28);
}

TEST(MapTest, KeyValue)
{
    const Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    Michka::Map<Michka::String, Person> b = {
        {"y", Person("person y")},
        {"w", Person("person w")},
        {"x", Person("person x")},
        {"y", Person("person Duplicate")},
        {"z", Person("person z")},
    };
    Michka::Map<Michka::String, int> c;

    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(b.getSize(), 4);

    b.insert("v", Person("Inserted"));
    ASSERT_EQ(b.getSize(), 5);

    ASSERT_EQ(a["a"], 1);
    ASSERT_EQ(a["b"], 2);
    ASSERT_EQ(a["c"], 3);

    ASSERT_EQ(b["w"], Person("person w"));
    ASSERT_EQ(b["y"], Person("person y"));
    ASSERT_EQ(b["z"], Person("person z"));
    ASSERT_EQ(b["v"], Person("Inserted"));

    EXPECT_THROW({
        try
        {
            int testNumber = a["undefined"];
        }
        catch (Michka::Exception exception)
        {
            ASSERT_STREQ("Map::operator[] : Key not found.", exception.getMessage());
            throw;
        }
    }, Michka::Exception);

    EXPECT_THROW({
        try
        {
            Person testPerson = b["undefined"];
        }
        catch (Michka::Exception exception)
        {
            ASSERT_STREQ("Map::operator[] : Your type is not assaignable.", exception.getMessage());
            throw;
        }
    }, Michka::Exception);

    EXPECT_NO_THROW({
        int testInt = c["undefined"];
    });
}

TEST(MapTest, Remove)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    Michka::Map<Michka::String, int> b = {
        {"a", 1},
        {"c", 3}
    };

    a.remove("b");
    ASSERT_EQ(a.getSize(), 2);
    ASSERT_TRUE(a.hasKey("a"));
    ASSERT_FALSE(a.hasKey("b"));
    ASSERT_TRUE(a.hasKey("c"));
}

TEST(MapTest, Swap)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
    };
    Michka::Map<Michka::String, int> b = {
        {"c", 3},
        {"d", 4},
        {"e", 5},
    };
    Michka::Map<Michka::String, int> c = a;
    Michka::Map<Michka::String, int> d = b;

    a.swap(b);

    ASSERT_EQ(b, c);
    ASSERT_EQ(a, d);

    a.swap("c", "d");

    ASSERT_EQ(a["c"], 4);
    ASSERT_EQ(a["d"], 3);
}

TEST(MapTest, Take)
{
    Michka::Map<Michka::String, int> a = {
        {"a", 1},
        {"b", 2},
    };

    ASSERT_EQ(a.take("a"), 1);
    ASSERT_EQ(a.getSize(), 1);
    ASSERT_EQ(a.take("b"), 2);
}
