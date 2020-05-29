#ifndef __PERSON_H__
#define __PERSON_H__

#include "Core/String.h"

// A class just for testing
class Person
{
public:
	Person(const Michka::String& _name)
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

	Michka::String getName() const
	{
		return mName;
	}

	bool operator == (const Michka::String& _name) const
	{
		return mName == _name;
	}

	bool operator == (const Person& _other) const
	{
		return mName == _other.mName;
	}
protected:
	Michka::String mName;
};

#endif // __PERSON_H__
