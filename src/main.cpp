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

    void runSomething()
    {
        for (int i = 0; i < 10; i++)
        {
            Sleep(100);
            std::wcout << mName.cstr() << "\n";
        }
    }

    static void runSomethingStatic(Person* p)
    {
        (p->runSomething)();
    }
protected:
	Michka::String mName;
};

void sayHello(int i)
{
    printf("Very long started %d (%llu)\n", i, ThreadBase::id());
    for (int i = 0; i < 300; i++)
    {
        Sleep(10);
    }
    printf("Very long ended %d (%llu)\n", i, ThreadBase::id());
}

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    // std::cout << Thread<>::id() << std::endl;

    // Vector<Thread<void(int)>> a;

    // for (int i = 0; i < 5; i++)
    // {
    //     a.pushBack(Thread<void(int)>(sayHello));
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

    // Map<String, int>::Element g("Test", 4);
    // std::cout << sizeof (g) << std::endl;

    // Map<String, String> a = {
    //     {"a", "478"},
    //     {"777", "421"}
    // };

    // std::cout << g.first << std::endl;

    // std::cout << g.key.toUtf8().cstr() << " - " << g.value << std::endl;

    // for (auto i : a)
    // {
    //     std::cout << i.key() << " - " << i.value() << std::endl;
    // }


    // List<int> a = {4, 7, 1779,832,4349,2476,3176,3894,1219,1537,910,2699,1207,2858,3850,2871,4937,4954,2759,2254,3414,1860,3686, 8, 5};
    List<int> a;
    a.insert(0, {10, 20, 30});
    a += {1, 2, 3};
    std::cout << a << std::endl;


    // std::chrono::steady_clock::time_point begin, end;
    // begin = std::chrono::steady_clock::now();

    // // #pragma omp parallel for
    // for (size_t i = 0; i < 100000; i++) {
    //     Vector<Person> a;
    //     a.pushBack(Person("amir"));
    //     a.pushBack(Person("ali"));
    //     a.pushBack(Person("reza"));
    //     a.pushBack(Person("mohammad"));
    //     a.pushBack(Person("masoud"));
    //     a.pushBack(Person("jahangir"));
    //     a.pushBack(Person("naser"));
    //     a.pushBack(Person("hassan"));
    //     a.pushBack(Person("homayoon"));
    //     a.insert(0, Person("First"));
    //     a.insert(1, Person("Second"));
    //     a.insert(2, {Person("Hello"), Person("World")});

    //     for (u32 j = 0; j < a.getSize(); j++)
    //     {
    //         //std::cout << a[i].getName() << std::endl;
    //     }
    //     // std::cout << "\n\n\n";
    // }
    // end = std::chrono::steady_clock::now();
    // std::cout << "1:" << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << std::endl;

    // Vector<int> b;
    // b.pushBack(1);
    // b.pushBack(5);
    // b.pushBack(9);
    // for (u32 i = 0; i < b.getSize(); i++)
    // {
    //     std::cout << b[i] << std::endl;
    // }
    return 0;
}
