#include <iostream>
#include <string>
#include "Mishka.h"
using namespace Mishka;

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    String test = "Hello World";
    std::wcout << test.find(L"Hello") << std::endl;
    system("PAUSE");
    return 0;
}
