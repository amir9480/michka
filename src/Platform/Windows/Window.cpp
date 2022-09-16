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

#include "Michka/Platform/Windows/Window.h"
#include "Michka/Core/Foundation/Log.h"
#include "Michka/Core/Helpers.h"
#include "Michka/Platform/Windows/OpenGLSupport.h"

namespace Michka
{
    Mutex windowMutex;
    Map<Window*, HWND> windowInstances;
    Map<Window*, WindowLoopThread*> windowThreads;

    LRESULT CALLBACK michkaMainWindowProc(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam);

    void michkaCallOnStart()
    {
        WNDCLASSW michkaWndClass{};
        michkaWndClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
        michkaWndClass.hCursor       = LoadCursor(0, IDC_ARROW);
        michkaWndClass.hInstance     = GetModuleHandleW(0);
        michkaWndClass.lpfnWndProc   = &WindowLoopThread::windowProc;
        michkaWndClass.lpszClassName = L"MichkaMainWindow";
        michkaWndClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        RegisterClassW(&michkaWndClass);

        loadOpenGLWindowsExtensions();
    }

    void michkaCallOnEnd()
    {
        unloadOpenGLWindowsExtensions();

        UnregisterClassW(L"MichkaMainWindow", GetModuleHandleW(0));
    }

    /* --------------------------- Window Loop Thread --------------------------- */

    WindowLoopThread::WindowLoopThread(Window* _window): mWindow(_window)
    {
        //
    }

    WindowLoopThread::~WindowLoopThread()
    {
        //
    }

    bool WindowLoopThread::onEvent(const Event* _event)
    {
        if (mHwnd)
        {
            MutexLock lock(windowMutex);
            if (_event->getName() == "show")
            {
                ShowWindow(mHwnd, SW_SHOW);
                UpdateWindow(mHwnd);
                return true;
            }
            else if (_event->getName() == "changeTitle" && _event->getParameter("title").isString())
            {
                SetWindowTextW(mHwnd, _event->getParameter("title").toString().cstr());
                return true;
            }
            else if (_event->getName() == "changeSize")
            {
                RECT windowRect;
                GetWindowRect(mHwnd, &windowRect);
                windowRect.right = windowRect.left + mWindow->getWidth();
                windowRect.bottom = windowRect.top + mWindow->getHeight();
                i32 windowStyle = GetWindowLongW(mHwnd, GWL_STYLE);
                AdjustWindowRect(&windowRect, windowStyle, 0);
                SetWindowPos(mHwnd, 0, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0);
                return true;
            }
        }

        return false; // @NOCOVERAGE
    }

    void WindowLoopThread::draw()
    {
        if (mHdc && mOGLRenderContext)
        {
            SwapBuffers(mHdc);
            InvalidateRect(mHwnd, 0, 1);
        }
    }

    void WindowLoopThread::run()
    {
        i32 windowStyle = WS_CAPTION|WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX;
        RECT windowRect = {0, 0, i32(mWindow->getWidth()), i32(mWindow->getHeight())};
        AdjustWindowRect(&windowRect, windowStyle, 0);
        mHwnd = CreateWindowExW(
            (DWORD)0,
            L"MichkaMainWindow",
            (Michka::String(MICHKA_NAME) + " " + MICHKA_VERSION).cstr(),
            windowStyle,
            0,
            0,
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top,
            nullptr,
            nullptr,
            GetModuleHandleA(0),
            nullptr
        );
        windowMutex.lock();
        windowInstances[mWindow] = mHwnd;
        windowMutex.unlock();

        MSG msg;
        do
        {
            //! TODO: add sleep to use less CPU
            if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            else
            {
                mWindow->callQueueListeners();
                Thread::sleep(10);
            }
        } while(mWindow->isDestroyed() == false);

        destroyOpenGLRenderContext(mHwnd, mHdc, mOGLRenderContext);
        DestroyWindow(mHwnd);
        mHwnd = 0;
    }

    void WindowLoopThread::setForOpenGL()
    {
        if (mWindow->isDestroyed())
        {
            return; // @NOCOVERAGE
        }

        if (mHdc == NULL || mOGLRenderContext == NULL)
        {
            initOpenGLRenderContext(mHwnd, mHdc, mOGLRenderContext);
        }

        wglMakeCurrent(NULL, NULL);
        if (!wglMakeCurrent(mHdc, mOGLRenderContext))
        {
            MICHKA_ABORT("wglMakeCurrent() failed."); // @NOCOVERAGE
        }
    }

    LRESULT CALLBACK WindowLoopThread::windowProc(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam)
    {
        u32 removeIndex = 0;
        switch(_msg)
        {
        case WM_ERASEBKGND:
            return 0;
        case WM_DESTROY:
        case WM_CLOSE:
            windowMutex.lock();
            if ((removeIndex = windowInstances.indexOfValue(_hwnd)) != windowInstances.notFound)
            {
                windowInstances.at(removeIndex).first->destroy();
                windowInstances.removeAt(removeIndex);
            }
            windowMutex.unlock();
            break;
        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO m = (LPMINMAXINFO)_lParam;
                m->ptMinTrackSize.x = 640;
                m->ptMinTrackSize.y = 480;
            }
            break;
        }

        return DefWindowProcW(_hwnd, _msg, _wParam, _lParam);
    }

    /* --------------------------------- Window --------------------------------- */

    Window::Window(const u32& _width, const u32& _height) :
        mWidth(_width),
        mHeight(_height)
    {
        MutexLock lock(windowMutex);
        WindowLoopThread* windowThread = new WindowLoopThread(this);
        windowThreads.insert(this, windowThread);
        windowThread->start();
        mWindowData = (void*)windowThread;
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

    void Window::draw()
    {
        if (mDestroyed == false)
        {
            WindowLoopThread* windowThread = static_cast<WindowLoopThread*>(mWindowData);
            windowThread->draw();
        }
    }

    u32 Window::getHeight() const
    {
        return mHeight;
    }

    u32 Window::getWidth() const
    {
        return mWidth;
    }

    bool Window::isDestroyed() const
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

    void Window::setRenderDevice(const Device* _device)
    {
        if (mDestroyed)
        {
            return; // @NOCOVERAGE
        }

        while (1)
        {
            //! TODO: Improve sleep time
            Thread::sleep(100);
            MutexLock lock(windowMutex);
            if (windowThreads.hasKey(this))
            {
                break;
            }
        }
        windowThreads[this]->setForOpenGL();
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

    void Window::show()
    {
        emit("show");
    }

    bool Window::onEvent(const Event* _event)
    {
        return windowThreads[this]->onEvent(_event);
    }
}
