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
#include "MichkaTests.h"
#include "Core/Foundation/Log.h"

TEST(LogTest, Log)
{
    MICHKA_LOG("This is debug.");
    MICHKA_INFO("This is info.");
    MICHKA_WARNING("This is warning.");
    MICHKA_ERROR("This is error.");
    MICHKA_CRITICAL("This is critical.");

    Michka::String logContent = Michka::File::getContents("michka.log");
    ASSERT_TRUE(logContent.find("This is debug.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is info.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is warning.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is error.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is critical.") != logContent.notFound);
}
