#include <gtest/gtest.h>
#include <utility>
#include "Core/String.h"
#include "Core/Type.h"
#include "Core/Helpers.h"
#include "Core/Vector.h"
#include "../Classes/Person.h"

TEST(VectorTest, VectorSetTest)
{
	Michka::Vector<int> a = {1};
	Michka::Vector<Person> b = {Person("A")};
	Michka::Vector<int> c;
	ASSERT_EQ(a.getSize(), 1);
	ASSERT_EQ(b.getSize(), 1);
	ASSERT_TRUE(a[0] == 1);
	ASSERT_TRUE(b[0] == Person("A"));

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

	a = Michka::Vector<int>({1, 2, 3});
	b = Michka::Vector<Person>({Person("A"), Person("B"), Person("C")});
	ASSERT_EQ(a.getSize(), 3);
	ASSERT_EQ(b.getSize(), 3);
	ASSERT_TRUE(a[0] == 1);
	ASSERT_TRUE(b[0] == Person("A"));
	ASSERT_TRUE(a[1] == 2);
	ASSERT_TRUE(b[1] == Person("B"));
	ASSERT_TRUE(a[2] == 3);
	ASSERT_TRUE(b[2] == Person("C"));

	c = a;
	ASSERT_EQ(c.getSize(), 3);
	ASSERT_TRUE(c[0] == 1);
	ASSERT_TRUE(c[1] == 2);
	ASSERT_TRUE(c[2] == 3);

}

TEST(VectorTest, VectorPushTest)
{
	Michka::Vector<int> a = {1};
	Michka::Vector<Person> b = {Person("A")};

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
}

TEST(VectorTest, VectorInsertTest)
{
	Michka::Vector<int> a = {1, 2};
	Michka::Vector<Person> b = {Person("A"), Person("B")};

	a.insert(0, 10);
	a.insert(2, {20, 200});
	a.insert(5, 30);
	b.insert(0, Person("AA"));
	b.insert(2, {Person("BB"), Person("BBB")});
	b.insert(5, Person("CC"));

	ASSERT_EQ(a.getSize(), 6);
	ASSERT_EQ(b.getSize(), 6);
	ASSERT_TRUE(a[0] == 10);
	ASSERT_TRUE(b[0] == Person("AA"));
	ASSERT_TRUE(a[1] == 1);
	ASSERT_TRUE(b[1] == Person("A"));
	ASSERT_TRUE(a[2] == 20);
	ASSERT_TRUE(b[2] == Person("BB"));
	ASSERT_TRUE(a[3] == 200);
	ASSERT_TRUE(b[3] == Person("BBB"));
	ASSERT_TRUE(a[4] == 2);
	ASSERT_TRUE(b[4] == Person("B"));
	ASSERT_TRUE(a[5] == 30);
	ASSERT_TRUE(b[5] == Person("CC"));

	for (u32 i=0; i < 100; i++)
	{
		a.pushBack(i);
	}
	for (u32 i=0; i < 100; i++)
	{
		a.pushBack(2 * i);
	}
	ASSERT_EQ(a.getSize(), 206);

	Michka::Vector<int> c;
	c.insert(0, a);
	ASSERT_EQ(c.getSize(), 206);
	ASSERT_TRUE(c[0] == 10);
	ASSERT_TRUE(c[1] == 1);
	ASSERT_TRUE(c[2] == 20);
}

TEST(VectorTest, VectorResizeTest)
{
	Michka::Vector<int> a = {1, 2};
	ASSERT_EQ(a.getSize(), 2);
	ASSERT_EQ(a.getCapacity(), 8);
	a.resize(16);
	ASSERT_EQ(a.getSize(), 2);
	ASSERT_EQ(a.getCapacity(), 16);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[1], 2);
}

TEST(VectorTest, ConstantVectorTest)
{
	const Michka::Vector<int> a = {1, 2};
	ASSERT_EQ(a.getSize(), 2);
	ASSERT_EQ(a.getCapacity(), 8);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[1], 2);
}

TEST(VectorTest, ClearVectorTest)
{
	Michka::Vector<int> a = {1, 2};
	ASSERT_EQ(a.getSize(), 2);
	a.clear();
	ASSERT_EQ(a.getSize(), 0);
}

TEST(VectorTest, IteratorTest)
{
	Michka::Vector<int> a = {1, 2, 3};
	const Michka::Vector<int> b = {4, 6, 8, 10};
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

TEST(VectorTest, SearchTest)
{
	Michka::Vector<int> a = {2, 4, 6, 8, 10, 2};
	ASSERT_EQ(a.indexOf(3), a.notFound);
	ASSERT_EQ(a.indexOf(2), 0);
	ASSERT_EQ(a.indexOf(2, 1), 5);
	ASSERT_EQ(a.indexOf(4, 1), 1);
	ASSERT_EQ(a.indexOf(4, 2), a.notFound);
	ASSERT_EQ(a.lastIndexOf(2), 5);
	ASSERT_EQ(a.lastIndexOf(2, 4), 0);
	ASSERT_EQ(a.lastIndexOf(4), 1);
	ASSERT_EQ(a.lastIndexOf(4, 0), a.notFound);


	Michka::Vector<Person> b = {Person("michka")};
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

TEST(VectorTest, RemoveTest)
{
	Michka::Vector<int> a = {2, 4, 6, 8, 10, 2};
	a.remove(1);
	ASSERT_EQ(a.getSize(), 5);
	ASSERT_EQ(a[1], 6);
	ASSERT_EQ(a[4], 2);

	a.remove(1, 2);
	ASSERT_EQ(a.getSize(), 3);
	ASSERT_EQ(a[1], 10);
	ASSERT_EQ(a[2], 2);

	a.remove(1, Michka::u32Info::max);
	ASSERT_EQ(a.getSize(), 1);
	ASSERT_EQ(a[0], 2);

	a.remove(0);
	ASSERT_EQ(a.getSize(), 0);
}

TEST(VectorTest, FilterTest)
{
	auto filterFunction = [] (const int& _item)
	{
		return _item % 2 == 0;
	};
	Michka::Vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	Michka::Vector<int> b = a.getFiltered(filterFunction);

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
