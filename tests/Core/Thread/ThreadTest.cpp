
#include <gtest/gtest.h>
#include <utility>
#include "Core/Container/Vector.h"
#include "Core/Thread/Thread.h"
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
    thread1.join();
    thread2.join();

    // If mutex working first 1 add to var then multiplies 2 which result is (0 + 1) * 2 = 2
    // If mutex not working then first var multiplies 2 then 1 add to var which result is (0 * 2) + 1 = 1
    ASSERT_EQ(testVar, 2);
}
