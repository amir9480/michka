// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2021 amir alizadeh.                                          //
//                                                                                 //
// Permission is hereby granted, free of charge, to any person obtaining a copy    //
// of this software and associated documentation files (the "Software"), to deal   //
// in the Software without restriction, including without limitation the rights    //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       //
// copies of the Software, and to permit persons to whom the Software is           //
// furnished to do so, subject to the following conditions:                        //
//                                                                                 //
// The above copyright notice and this permission notice shall be included in all  //
// copies or substantial portions of the Software.                                 //
//                                                                                 //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
// SOFTWARE.                                                                       //
// ------------------------------------------------------------------------------- //

#include <gtest/gtest.h>
#include "Platform/Utility.h"
#define HAVE_STRUCT_TIMESPEC
#include <Windows.h>

TEST(WindowsUtilityTest, PossibleResolutions)
{
    Michka::Vector<Michka::Size> resolutions = Michka::Platform::getPossibleResolutions();
    ASSERT_TRUE(resolutions.getSize() > 0);
}

TEST(WindowsUtilityTest, SetConsoleColor)
{
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::black, Michka::Platform::ConsoleColor::black);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::blue, Michka::Platform::ConsoleColor::blue);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::cyan, Michka::Platform::ConsoleColor::cyan);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::green, Michka::Platform::ConsoleColor::green);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::magenta, Michka::Platform::ConsoleColor::magenta);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::red, Michka::Platform::ConsoleColor::red);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::white, Michka::Platform::ConsoleColor::white);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::yellow, Michka::Platform::ConsoleColor::yellow);
    Michka::Platform::setConsoleColor(Michka::Platform::ConsoleColor::white);
    ASSERT_TRUE(true);
}
