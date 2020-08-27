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
#include "Platform/Window.h"
#include "Core/Thread/Mutex.h"
#include "Core/Thread/Thread.h"
#include <Windows.h>

namespace Michka
{
    extern Mutex windowMutex;
    extern Map<Window*, HWND> windowInstances;
}

TEST(WindowTest, ChangeSize)
{
    Michka::Window window(640, 480);
    while (Michka::windowInstances.getSize() == 0)
    {
        Michka::Thread::sleep(50);
    }
    RECT rect;
    HWND hwnd = Michka::windowInstances[&window];

    if (! GetClientRect(hwnd, &rect))
    {
        ASSERT_FALSE(true);
    }
    ASSERT_EQ(rect.right - rect.left, 640);
    ASSERT_EQ(rect.bottom - rect.top, 480);

    window.setWidth(800);
    while (window.hasEventsOnQueue())
    {
        Michka::Thread::sleep(50);
    }
    if (! GetClientRect(hwnd, &rect))
    {
        ASSERT_FALSE(true);
    }
    ASSERT_EQ(rect.right - rect.left, 800);
    ASSERT_EQ(rect.bottom - rect.top, 480);

    window.setHeight(600);
    while (window.hasEventsOnQueue())
    {
        Michka::Thread::sleep(50);
    }
    if (! GetClientRect(hwnd, &rect))
    {
        ASSERT_FALSE(true);
    }
    ASSERT_EQ(rect.right - rect.left, 800);
    ASSERT_EQ(rect.bottom - rect.top, 600);

    window.resize(640, 480);
    while (window.hasEventsOnQueue())
    {
        Michka::Thread::sleep(50);
    }
    if (! GetClientRect(hwnd, &rect))
    {
        ASSERT_FALSE(true);
    }
    ASSERT_EQ(rect.right - rect.left, 640);
    ASSERT_EQ(rect.bottom - rect.top, 480);
}

TEST(WindowTest, CreateWindow)
{
    Michka::Window* window = new Michka::Window;
    while (Michka::windowInstances.getSize() == 0)
    {
        Michka::Thread::sleep(50);
    }
    HWND hwnd = Michka::windowInstances[window];
    ASSERT_FALSE(IsWindowVisible(hwnd));
    window->show();
    while (window->hasEventsOnQueue())
    {
        Michka::Thread::sleep(50);
    }
    ASSERT_TRUE(IsWindowVisible(hwnd));
    delete window;
}

TEST(WindowTest, DestroyOnClose)
{
    Michka::Window window;
    while (Michka::windowInstances.getSize() == 0)
    {
        Michka::Thread::sleep(50);
    }
    HWND hwnd = Michka::windowInstances[&window];
    PostMessageW(hwnd, WM_CLOSE, 0, 0);
    Michka::Thread::sleep(50);
    for (u32 i = 0; i < 10 && window.isDestroyed() == false; i++)
    {
        Michka::Thread::sleep(50);
    }
    ASSERT_TRUE(window.isDestroyed());
}

TEST(WindowTest, SetTitle)
{
    Michka::Window window;
    while (Michka::windowInstances.getSize() == 0)
    {
        Michka::Thread::sleep(50);
    }
    HWND hwnd = Michka::windowInstances[&window];
    window.setTitle("Hello World!!!");
    while (window.hasEventsOnQueue())
    {
        Michka::Thread::sleep(50);
    }
    char* windowTitle = new char[100];
    GetWindowTextA(hwnd, windowTitle, 100);
    ASSERT_STREQ(windowTitle, "Hello World!!!");
    delete[] windowTitle;
}
