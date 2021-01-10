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

#ifndef __WINDOWS_WINDOW_H__
#define __WINDOWS_WINDOW_H__

#include "Platform/Window.h"
#include "Core/Container/Map.h"
#include "Core/Container/String.h"
#include "Core/Thread/Thread.h"
#include <Windows.h>

namespace Michka
{
    class WindowLoopThread;

    extern Mutex windowMutex;
    extern Map<Window*, HWND> windowInstances;
    extern Map<Window*, WindowLoopThread*> windowThreads;

    class MICHKA_API WindowLoopThread : public Thread
    {
        friend class Window;
    public:
        explicit WindowLoopThread(Window* _window);

        virtual ~WindowLoopThread();

        bool onEvent(const Event* _event);

        static LRESULT CALLBACK windowProc(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam);

    protected:
        void draw();

        void run() override;

        void setForOpenGL();

    protected:
        Window* mWindow;
        HWND    mHwnd = 0;
        HDC     mHdc = 0;
        HGLRC   mOGLRenderContext = 0;
    };
}

#endif // __WINDOWS_WINDOW_H__
