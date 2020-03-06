#include <iostream>
#include <string>
#include <fstream>
#include "Mishka.h"
using namespace Mishka;


class Person
{
public:
    Person(const std::string& _name)
    {
        name = _name;
    }

    Person(const Person& _other)
    {
        std::cout << "COPY!\n";
        name = _other.name;
    }

    Person(Person&& _other)
    {
        std::cout << "Move!\n";
        name = std::move(_other.name);
    }

    virtual std::string getName() const
    {
        return name;
    }
protected:
    std::string name;
};


int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    Mishka::String m;
    for (auto i : m)
    {
        std::cout << int (i) << std::endl;
    }

    // Vector<Person> a;
    // a.resize(10);
    // a.pushBack(Person("amir"));
    // a.pushBack(Person("ali"));
    // a.pushBack(Person("reza"));
    // a.pushBack(Person("mohammad"));
    // a.insert(0, Person("First"));
    // a.insert(1, Person("Second"));
    // a.insert(2, {Person("Hello"), Person("World")});

    // a = {Person("A"), Person("B"), Person("C")};

    // for (int i = 0; i < a.getSize(); i++)
    // {
    //     std::cout << a[i].getName() << std::endl;
    // }
    // std::cout << "\n\n\n";

    // Vector<int> b;
    // b.pushBack(1);
    // b.pushBack(5);
    // b.pushBack(9);
    // for (int i = 0; i < b.getSize(); i++)
    // {
    //     std::cout << b[i] << std::endl;
    // }

    system("PAUSE");
    return 0;
}
