
#include <gtest/gtest.h>
#include <utility>
#include "Core/Map.h"
#include "Core/String.h"
#include "../Classes/Person.h"

TEST(MapTest, CreateDefaultTest)
{
	Michka::Map<Michka::String, Michka::String> test;
	ASSERT_EQ(test.getSize(), 0);
}

#include <map>

TEST(MapTest, KeyValueTest)
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
}

TEST(MapTest, atTest)
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

TEST(MapTest, IteratorTest)
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
