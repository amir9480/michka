
#include <gtest/gtest.h>
#include <utility>
#include "Core/String.h"
#include "Core/Helpers.h"

TEST(HelpersTest, SwapTest)
{
	int a = 10, b = 20;
	Michka::swap(a, b);
	ASSERT_EQ(a, 20);
	ASSERT_EQ(b, 10);

	Michka::String astr = "Hello", bstr = "Bye";
	Michka::swap(astr, bstr);
	ASSERT_TRUE(astr == "Bye");
	ASSERT_TRUE(bstr == "Hello");
}

TEST(HelpersTest, MinAndMaxTest)
{
	int a = 10, b = 20;
	ASSERT_EQ(Michka::min(a, b), 10);
	ASSERT_EQ(Michka::max(a, b), 20);

	ASSERT_EQ(Michka::min(10, 20), 10);
	ASSERT_EQ(Michka::max(10, 20), 20);
}
