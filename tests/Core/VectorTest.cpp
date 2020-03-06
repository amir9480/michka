#include "gtest/gtest.h"
#include <utility>
#include "Core/String.h"
#include "Core/Helpers.h"
#include "Core/Vector.h"

class Person
{
public:
	Person(const Mishka::String& _name)
	{
		mName = _name;
	}

	Person(const Person& _other)
	{
		mName = _other.mName;
	}

	Person(Person&& _other)
	{
		mName = std::move(_other.mName);
	}

	Mishka::String getName() const
	{
		return mName;
	}

	bool operator == (const Mishka::String& _name)
	{
		return mName == _name;
	}

	bool operator == (const Person& _other)
	{
		return mName == _other.mName;
	}
protected:
	Mishka::String mName;
};

TEST(VectorTest, VectorSetTest)
{
	Mishka::Vector<int> a = {1};
	Mishka::Vector<Person> b = {Person("A")};
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

	a = Mishka::Vector<int>({1, 2, 3});
	b = Mishka::Vector<Person>({Person("A"), Person("B"), Person("C")});
	ASSERT_EQ(a.getSize(), 3);
	ASSERT_EQ(b.getSize(), 3);
	ASSERT_TRUE(a[0] == 1);
	ASSERT_TRUE(b[0] == Person("A"));
	ASSERT_TRUE(a[1] == 2);
	ASSERT_TRUE(b[1] == Person("B"));
	ASSERT_TRUE(a[2] == 3);
	ASSERT_TRUE(b[2] == Person("C"));
}

TEST(VectorTest, VectorPushTest)
{
	Mishka::Vector<int> a = {1};
	Mishka::Vector<Person> b = {Person("A")};

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
	Mishka::Vector<int> a = {1, 2};
	Mishka::Vector<Person> b = {Person("A"), Person("B")};

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
}
