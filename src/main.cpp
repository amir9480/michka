#include <iostream>
#include <string>
#include "Mishka.h"
#include <fstream>
using namespace Mishka;

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";
    String test = "Hello World";
    test = test.toUpper();
    std::wcout << test.cstr() << int('a' - 'A')<< std::endl<< std::endl;
    // std::cout << test.getSize() << "-" << test.getLength() << ":" << test.toUtf8().cstr() << std::endl;

    system("PAUSE");
    return 0;
}
