// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
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
#include <utility>
#include "Core/Container/String.h"
#include "Core/Helpers.h"

TEST(HelpersTest, MinAndMax)
{
    int a = 10, b = 20;
    ASSERT_EQ(Michka::min(a, b), 10);
    ASSERT_EQ(Michka::max(a, b), 20);

    ASSERT_EQ(Michka::min(10, 20), 10);
    ASSERT_EQ(Michka::max(10, 20), 20);
}

TEST(HelpersTest, Swap)
{
    int a = 10, b = 20;
    Michka::swap(a, b);
    ASSERT_EQ(a, 20);
    ASSERT_EQ(b, 10);

    Michka::String astr = "Hello", bstr = "Bye";
    Michka::swap(astr, bstr);
    ASSERT_TRUE(astr == "Bye");
    ASSERT_TRUE(bstr == "Hello");
}
