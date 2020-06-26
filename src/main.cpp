#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Michka.h"
#include <Windows.h>
using namespace Michka;

std::ostream& operator << (std::ostream& _ostream, String _str)
{
    _ostream << _str.toUtf8().cstr();
    return _ostream;
}

template<typename T>
std::ostream& operator << (std::ostream& _ostream, Vector<T> _array)
{
    for (auto element: _array)
    {
        _ostream << element << ",";
    }
    _ostream << "\n";
    return _ostream;
}

template<typename T>
std::ostream& operator << (std::ostream& _ostream, List<T> _array)
{
    for (auto element: _array)
    {
        _ostream << element << ",";
    }
    _ostream << "\n";
    return _ostream;
}

class Person
{
public:
    Person()
    {
    }

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

    void runSomething(int i)
    {
        printf("Very long started %d (%llu)\n", i, Thread::id());
        for (int j = 0; j < 300; j++)
        {
            Sleep(10);
        }
        printf("Very long ended %d (%llu)\n", i, Thread::id());
    }

    static void runSomethingStatic(Person* p)
    {
        (p->runSomething)(14);
    }
protected:
	Michka::String mName;
};

void sayHello(int i)
{
    printf("Very long started %d (%llu)\n", i, Thread::id());
    for (int i = 0; i < 300; i++)
    {
        Sleep(10);
    }
    printf("Very long ended %d (%llu)\n", i, Thread::id());
}

class CustomThread : public Thread
{
protected:
    void run() override
    {
        printf("Very long started (%llu)\n", id());
        for (int i = 0; i < 300; i++)
        {
            Sleep(10);
        }
        printf("Very long ended (%llu)\n", id());
    }
};

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    // std::cout << ThreadBase::id() << std::endl;

    // Vector<Thread<void(int)>> a;
    // Vector<Person> persons = {
    //     Person("a"),
    //     Person("b"),
    //     Person("c"),
    //     Person("d"),
    //     Person("e"),
    // };

    // for (int i = 0; i < 5; i++)
    // {
    //     a.pushBack(Thread<void(int)>(std::bind(&Person::runSomething, persons[i], std::placeholders::_1)));
    //     a[i].start(i);
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     a[i].join();
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     a[i].join();
    // }

    Vector<CustomThread> a;
    a.resize(20);

    for (int i = 0; i < 10; i++)
    {
        a.pushBack(CustomThread());
        a[i].start();
    }
    for (int i = 0; i < 10; i++)
    {
        a[i].join();
    }

    system("PAUSE");
    return 0;
}
