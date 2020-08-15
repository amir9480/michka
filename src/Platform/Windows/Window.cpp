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
    Map<Window*, WindowLoopThread*> windowThreads;

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
                windowInstances.at(removeIndex).first->destroy();
                windowInstances.removeAt(removeIndex);
            }
            windowMutex.unlock();
            break;
        case WM_CLOSE:
            DestroyWindow(_hwnd);
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

    class MICHKA_API WindowLoopThread : public Thread
    {
        friend class Window;
    public:
        WindowLoopThread(Window* _window): mWindow(_window)
        {
            //
        }
        virtual ~WindowLoopThread()
        {
            //
        }
        bool onEvent(const Event* _event)
        {
            if (windowInstances.hasKey(mWindow))
            {
                MutexLock lock(windowMutex);
                if (_event->getName() == "changeTitle" && _event->getParameter("title").isString())
                {
                    SetWindowTextW(windowInstances[mWindow], _event->getParameter("title").toString().cstr());
                    return true;
                }
                if (_event->getName() == "changeSize")
                {
                    RECT windowRect;
                    GetWindowRect(windowInstances[mWindow], &windowRect);
                    SetWindowPos(windowInstances[mWindow], 0, windowRect.left, windowRect.top, mWindow->getWidth(), mWindow->getHeight(), 0);
                    return true;
                }
            }

            return false;
        }

    protected:
        virtual void run()
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
            windowInstances[mWindow] = hwnd;
            windowMutex.unlock();

            MSG msg;
            do
            {
                if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
                else
                {
                    mWindow->callQueueListeners();
                }
            } while(mWindow->isDestroyed() == false);

            DestroyWindow(hwnd);
        }
    protected:
        Window* mWindow;
    };

    Window::Window(const u32& _width, const u32& _height) :
        mWidth(_width),
        mHeight(_height)
    {
        MutexLock lock(windowMutex);
        WindowLoopThread* windowThread = new WindowLoopThread(this);
        windowThreads.insert(this, windowThread);
        windowThread->start();
    }

    Window::~Window()
    {
        destroy();
        windowThreads[this]->join();
        MutexLock lock(windowMutex);
        delete windowThreads[this];
        windowThreads.remove(this);
    }

    void Window::destroy()
    {
        mDestroyed = true;
    }

    u32 Window::getHeight() const
    {
        return mHeight;
    }

    u32 Window::getWidth() const
    {
        return mWidth;
    }

    bool Window::isDestroyed()
    {
        return mDestroyed;
    }

    void Window::resize(const u32& _width, const u32& _height)
    {
        mWidth = _width;
        mHeight = _height;
        emit("changeSize");
    }

    void Window::setHeight(const u32& _height)
    {
        mHeight = _height;
        emit("changeSize");
    }

    void Window::setTitle(const String& _title)
    {
        emit("changeTitle", {{"title", _title}});
    }

    void Window::setWidth(const u32& _width)
    {
        mWidth = _width;
        emit("changeSize");
    }

    bool Window::onEvent(const Event* _event)
    {
        return windowThreads[this]->onEvent(_event);
    }
}
