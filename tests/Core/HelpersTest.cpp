
#include "gtest/gtest.h"
#include <utility>
#include "Core/String.h"
#include "Core/Helpers.h"

TEST(HelpersTest, SwapTest)
{
	int a = 10, b = 20;
	Mishka::swap(a, b);
	ASSERT_EQ(a, 20);
	ASSERT_EQ(b, 10);

	Mishka::String astr = "Hello", bstr = "Bye";
	Mishka::swap(astr, bstr);
	ASSERT_TRUE(astr == "Bye");
	ASSERT_TRUE(bstr == "Hello");
}

TEST(HelpersTest, MinAndMaxTest)
{
	int a = 10, b = 20;
	ASSERT_EQ(Mishka::min(a, b), 10);
	ASSERT_EQ(Mishka::max(a, b), 20);

	ASSERT_EQ(Mishka::min(10, 20), 10);
	ASSERT_EQ(Mishka::max(10, 20), 20);
}
