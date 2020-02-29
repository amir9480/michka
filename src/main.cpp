#include <iostream>
#include <string>
#include "Mishka.h"
using namespace Mishka;

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    String test = "Hello";
    std::wcout << String::number(long double(3.14)).toNumber<float>() << std::endl;
    std::string t= "Test";
    std::cout << t.size() << " - " << t.length() << std::endl;
    system("PAUSE");
    return 0;
}
