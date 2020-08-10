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
#include "Core/Foundation/Event.h"
#include "Core/Foundation/EventManager.h"
#include "../../Classes/MichkaObject.h"

TEST(EventTest, Clear)
{
    MichkaObject test;
    int testVar = 0;
    auto eventCallback = [&testVar] (const Michka::Event* _event) {
        testVar++;
    };
    for (u32 i = 0; i < 5; i++)
    {
        test.on("testEvent", eventCallback);
        test.on("testEvent2", eventCallback);
    }
    ASSERT_EQ(testVar, 0);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 5);
    test.emit("testEvent2");
    ASSERT_EQ(testVar, 10);

    test.clearEvents();
    ASSERT_EQ(testVar, 10);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 10);
    test.emit("testEvent2");
    ASSERT_EQ(testVar, 10);
}

TEST(EventTest, On)
{
    MichkaObject test;
    int testVar = 0;
    test.on("testEvent", [&testVar] (const Michka::Event* _event) {
        ASSERT_EQ(_event->getName(), "testEvent");
        testVar++;
    });
    test.emit("nonTestEvent");
    ASSERT_EQ(testVar, 0);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 1);

    u64 handlerId = test.on("testEvent", [&testVar] (const Michka::Event* _event) {
        testVar += 10;
    });
    test.on("testEvent2", [&testVar] (const Michka::Event* _event) {
        testVar--;
    });
    test.emit("nonTestEvent");
    ASSERT_EQ(testVar, 1);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 12);
    test.emit("testEvent2");
    ASSERT_EQ(testVar, 11);

    test.off("testEvent", handlerId);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 12);

    test.off("testEvent");
    test.emit("testEvent");
    ASSERT_EQ(testVar, 12);
    test.emit("testEvent2");
    ASSERT_EQ(testVar, 11);

    test.on("testEvent", [&testVar] (const Michka::Event* _event) {
        ASSERT_EQ(_event->getParameter("test").getType(), Michka::Variant::Type::typeInt);
        ASSERT_EQ(_event->getParameter("non_exist").getType(), Michka::Variant::Type::typeNull);
        ASSERT_EQ(_event->getParameters().getSize(), 1);
        testVar += _event->getParameter("test").to<int>();
    });
    test.emit("testEvent", {{"test", 5}});
    ASSERT_EQ(testVar, 16);
    test.emit("testEvent", {{"test", 2}});
    ASSERT_EQ(testVar, 18);
}

TEST(EventTest, Once)
{
    MichkaObject test;
    int testVar = 0;
    auto eventCallback = [&testVar] (const Michka::Event* _event) {
        testVar++;
    };
    test.on("testEvent", eventCallback);
    for (u32 i = 0; i < 9; i++)
    {
        test.once("testEvent", eventCallback);
    }
    ASSERT_EQ(testVar, 0);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 10);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 11);
    test.emit("testEvent");
    ASSERT_EQ(testVar, 12);
}
