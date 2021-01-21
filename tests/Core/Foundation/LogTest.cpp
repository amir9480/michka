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

TEST(LogTest, Abort)
{
    ASSERT_ANY_THROW({MICHKA_ABORT("This is abort.");});
    ASSERT_ANY_THROW({MICHKA_ABORT(Michka::String("This is abort."));});
    ASSERT_ANY_THROW({MICHKA_ASSERT(false, "This is assert.");});
    MICHKA_ASSERT(true, "This is not assert.");
}

TEST(LogTest, Log)
{
    MICHKA_LOG("This is debug.");
    MICHKA_INFO("This is info.");
    MICHKA_WARNING("This is warning.");
    MICHKA_ERROR("This is error.");
    MICHKA_CRITICAL("This is critical.");
    Michka::Log::debug("Log without file and line.");
    Michka::Log::instance().raw("Raw message.");

    MICHKA_LOG(Michka::String("This is debug [String Class]."));
    MICHKA_INFO(Michka::String("This is info [String Class]."));
    MICHKA_WARNING(Michka::String("This is warning [String Class]."));
    MICHKA_ERROR(Michka::String("This is error [String Class]."));
    MICHKA_CRITICAL(Michka::String("This is critical [String Class]."));
    Michka::Log::debug(Michka::String("Log without file and line [String Class]."));
    Michka::Log::instance().raw(Michka::String("Raw message [String Class]."));

    Michka::String logContent = Michka::File::getContents("michka.log");

    ASSERT_TRUE(logContent.find("This is debug.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is info.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is warning.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is error.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is critical.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("Log without file and line.") != logContent.notFound);
    ASSERT_TRUE(logContent.find("Raw message.") != logContent.notFound);

    ASSERT_TRUE(logContent.find("This is debug [String Class].") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is info [String Class].") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is warning [String Class].") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is error [String Class].") != logContent.notFound);
    ASSERT_TRUE(logContent.find("This is critical [String Class].") != logContent.notFound);
    ASSERT_TRUE(logContent.find("Log without file and line [String Class].") != logContent.notFound);
    ASSERT_TRUE(logContent.find("Raw message [String Class].") != logContent.notFound);
}
