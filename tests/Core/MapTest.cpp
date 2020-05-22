
#include <gtest/gtest.h>
#include <utility>
#include "Core/Map.h"
#include "Core/String.h"
#include "../Classes/Person.h"

TEST(MapTest, CreateDefaultMapTest)
{
	Michka::Map<Michka::String, Michka::String> test;
	ASSERT_EQ(test.getSize(), 0);
}
