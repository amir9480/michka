#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Michka.h"
#include <Windows.h>
using namespace Michka;

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
        printf("Very long started %d %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
        for (int j = 0; j < 300; j++)
        {
            Sleep(10);
        }
        printf("Very long ended %d %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
    }

    void runSomething2()
    {
        printf("Very long started %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
        for (int j = 0; j < 300; j++)
        {
            Sleep(10);
        }
        printf("Very long ended %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
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
    printf("Very long started %d - %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
    for (int i = 0; i < 300; i++)
    {
        Sleep(10);
    }
    printf("Very long ended %d - %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
}

Mutex mutex;

class CustomThread : public Thread
{
protected:
    void run() override
    {
        printf("Very long started %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
        for (int i = 0; i < 50; i++)
        {
            MutexLock ml(mutex);
            Sleep(10);
        }
        printf("Very long ended %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
    }
};

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";

    // std::cout << ThreadBase::id() << std::endl;

    // Vector<CallbackThread<void()>> a;
    // Vector<Person> persons = {
    //     Person("a"),
    //     Person("b"),
    //     Person("c"),
    //     Person("d"),
    //     Person("e"),
    //     Person("f"),
    //     Person("g"),
    //     Person("h"),
    //     Person("i"),
    //     Person("j"),
    //     Person("k"),
    //     Person("l"),
    // };

    // for (int i = 0; i < 10; i++)
    // {
    //     a.pushBack(CallbackThread<void()>(std::bind(&Person::runSomething2, persons[i])));
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     a[i].start();
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     a[i].join();
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     a[i].join();
    // }

    Device* device = Device::instance(Device::Driver::OpenGL);
    while (device->getWindow()->isDestroyed() == false)
    {
        device->clear(true, true, true, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
    }

    std::cout << "\nBYE\n";
    system("PAUSE");
    return 0;
}
