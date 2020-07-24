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
#include "Core/Container/Vector.h"
#include "Core/Thread/Thread.h"
#include "Core/Types.h"
#include "../../Classes/TestThread.h"

TEST(ThreadTest, CallbackThread)
{
    int testVar = 0;
    Michka::Vector<Michka::CallbackThread<void()>> threads;
    for (u32 i = 0; i < 5; i++)
    {
        threads.pushBack(Michka::CallbackThread<void()>([&]()
        {
            testVar++;
            ASSERT_EQ(Michka::Thread::getCurrentId(), Michka::Thread::getCurrent()->getId());
        }));
    }
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].start();
    }
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].join();
    }
    ASSERT_EQ(testVar, 5);
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].start();
    }
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].join();
    }
    ASSERT_EQ(testVar, 10);
}

TEST(ThreadTest, CustomClassThread)
{
    int testVar = 0;
    Michka::Vector<TestThread> threads;
    for (u32 i = 0; i < 10; i++)
    {
        threads.pushBack(TestThread(testVar));
    }
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].start();
    }
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].join();
    }
    ASSERT_EQ(testVar, 10);
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].start();
    }
    for (u32 i = 0; i < threads.getSize(); i++)
    {
        threads[i].join();
    }
    ASSERT_EQ(testVar, 20);
}

TEST(ThreadTest, Mutex)
{
    Michka::Mutex mutex;
    int testVar = 0;
    Michka::CallbackThread<void()> thread1([&]()
    {
        Michka::MutexLock lock(mutex);
        Michka::Thread::sleep(300);
        testVar++;
    });
    Michka::CallbackThread<void()> thread2([&]()
    {
        Michka::MutexLock lock(mutex);
        testVar *= 2;
    });
    thread1.start();
    Michka::Thread::sleep(100);
    thread2.start();
    ASSERT_TRUE(thread1.isRunning());
    thread1.join();
    thread2.join();

    // If mutex working first 1 add to var then multiplies 2 which result is (0 + 1) * 2 = 2
    // If mutex not working then first var multiplies 2 then 1 add to var which result is (0 * 2) + 1 = 1
    ASSERT_EQ(testVar, 2);
}
