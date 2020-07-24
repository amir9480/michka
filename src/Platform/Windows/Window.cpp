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

#include "Platform/Window.h"
#include "Core/Container/Map.h"
#include "Core/Container/String.h"
#include "Core/Thread/Thread.h"
#include "Core/Helpers.h"
#include <Windows.h>

namespace Michka
{
    class WindowLoopThread;

    Mutex windowMutex;
    Map<Window*, HWND> windowInstances;

    LRESULT CALLBACK michkaMainWindowProc(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam);

    void michkaCallOnStart()
    {
        WNDCLASSW michkaWndClass{};
        michkaWndClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
        michkaWndClass.hCursor = LoadCursor(0, IDC_ARROW);
        michkaWndClass.hInstance = GetModuleHandleW(0);
        michkaWndClass.lpfnWndProc = michkaMainWindowProc;
        michkaWndClass.lpszClassName = L"MichkaMainWindow";
        michkaWndClass.style = CS_HREDRAW | CS_VREDRAW;
        RegisterClassW(&michkaWndClass);
    }

    void michkaCallOnEnd()
    {
        UnregisterClassW(L"MichkaMainWindow",GetModuleHandleW(0));
    }

    LRESULT CALLBACK michkaMainWindowProc(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam)
    {
        u32 removeIndex = 0;
        switch(_msg)
        {
        case WM_ERASEBKGND:
            return 0;
        case WM_DESTROY:
            windowMutex.lock();
            if ((removeIndex = windowInstances.indexOfValue(_hwnd)) != windowInstances.notFound)
            {
                windowInstances.removeAt(removeIndex);
            }
            windowMutex.unlock();
            removeIndex = windowInstances.getSize();
            if (windowInstances.getSize() < 1)
            {
                PostQuitMessage(0);
            }
            break;
        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO m = (LPMINMAXINFO) _lParam;
                m->ptMinTrackSize.x = 640;
                m->ptMinTrackSize.y = 480;
                break;
            }
        }

        return DefWindowProcW(_hwnd, _msg, _wParam, _lParam);
    }

    class WindowLoopThread : public Thread
    {
        friend class Window;
    public:
        WindowLoopThread(Window* _window): Thread(), mWindow(_window), mDestroyed(false)
        {
        }
        virtual ~WindowLoopThread()
        {
        }
    protected:
        virtual void run()
        {
        }
    protected:
        Window* mWindow;
        bool mDestroyed;
    };

    Window::Window(const u32& _width, const u32& _height) :
        mWidth(_width),
        mHeight(_height)
    {
        HWND hwnd = CreateWindowExW(
            (DWORD)0,
            L"MichkaMainWindow",
            (Michka::String(MICHKA_NAME)+" "+MICHKA_VERSION).cstr(),
            WS_VISIBLE|WS_CAPTION|WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
            0,
            0,
            640,
            480,
            nullptr,
            nullptr,
            GetModuleHandleA(0),
            nullptr
        );
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
        windowMutex.lock();
        windowInstances[this] = hwnd;
        windowMutex.unlock();
    }

    Window::~Window()
    {
        destroy();
    }

    void Window::destroy()
    {
        if (windowInstances.hasKey(this))
        {
            DestroyWindow(windowInstances[this]);
        }
    }

    bool Window::proccess()
    {
        MSG msg;
        if (! windowInstances.hasKey(this))
        {
            return false;
        }
        while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        return true;
    }
}
