#include <iostream>
#include <string>
#include <fstream>
#include "Mishka.h"
using namespace Mishka;

template<typename T>
void printType()
{
    std::wcout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::wcout << Type<T>::size << " | " << Type<T>::name << " | " << Type<T>::typeName << " | " << Type<T>::min << " | " << Type<T>::max<< " | " << (Type<T>::isUnsigned ? "Unsigned" : "Signed") << " | " << (Type<T>::isClass ? "Class" : Type<T>::isEnum ? "Enum" : "Native") << " | " << Type<T>::rawName << " | " << Type<T>::typeName << " | " << Type<T>::hash << " | " << std::endl;
}


enum testEnum
{
    a, b, c
};

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";


    printType<short>();
    printType<short int>();
    printType<signed short>();
    printType<signed short int>();
    printType<unsigned short>();
    printType<unsigned short int>();
    printType<int>();
    printType<signed>();
    printType<signed int>();
    printType<unsigned>();
    printType<unsigned int>();
    printType<long>();
    printType<long int>();
    printType<signed long>();
    printType<signed long int>();
    printType<unsigned long>();
    printType<unsigned long int>();
    printType<long long>();
    printType<long long int>();
    printType<signed long long>();
    printType<signed long long int>();
    printType<unsigned long long>();
    printType<unsigned long long int>();

    printType<float>();
    printType<double>();
    printType<long double>();
    printType<String>();
    printType<testEnum>();
    printType<char16_t>();
    printType<char32_t>();
    printType<wchar_t>();
    system("PAUSE");
    return 0;
}
