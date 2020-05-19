#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Michka.h"
#include <Windows.h>
using namespace Michka;


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
        for (int i = 0; i < 10; i++) {
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

void sayHello()
{
    // std::cout << "Very long started (" << ThreadBase::id() << ")" << std::endl;
    // for (int i = 0; i < 300; i++) {
    //     Sleep(10);
    // }
    // std::cout << "Very long ended (" << ThreadBase::id() << ")" << std::endl;
}

int main()
{
    // typedef void * (*THREADFUNCPTR)(void *);
    // std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    // std::cout << Thread<>::id() << std::endl;
    // Person a("amir");
    // pthread_t t;
    // pthread_create(&t, NULL, (THREADFUNCPTR)&Person::runSomethingStatic, &a);
    // Sleep(500);
    // pthread_cancel(t);
    // pthread_kill(t, 0);

    // Vector<Thread<void()>> a;

    // for (int i = 0; i < 5; i++)
    // {
    //     a.pushBack(Thread<void()>(sayHello));
    //     a[i].start();
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     a[i].join();
    // }

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
    Michka::String8 test = "سلام";
    std::cout << test.getSize() << " - " << test.getLength() << std::endl;
    system("PAUSE");
    return 0;
}
