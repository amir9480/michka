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

#include "OpenGLSupport.h"

namespace Michka
{
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    HWND michkaDefaultHwnd = 0;
    HDC michkaDefaultHdc = 0;
    HGLRC michkaDefaultOGLRenderContext = 0;

    void loadOpenGLWindowsExtensions()
    {
        RECT windowRect = {0, 0, 1920, 1080};
        michkaDefaultHwnd = CreateWindowExW(
            (DWORD)0,
            L"MichkaMainWindow",
            L"Michka Default Window",
            WS_CAPTION|WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
            0,
            0,
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top,
            nullptr,
            nullptr,
            GetModuleHandleA(0),
            nullptr
        );

        HWND tempHwnd = CreateWindowW(
            L"MichkaMainWindow", L"Temp",
            WS_CAPTION|WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
            0, 0, 1, 1, 0, 0, GetModuleHandleA(0), 0
        );
        HDC tempDC = GetDC(tempHwnd);

        PIXELFORMATDESCRIPTOR fakePFD = {};
        fakePFD.nSize      = sizeof(fakePFD);
        fakePFD.nVersion   = 1;
        fakePFD.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        fakePFD.iPixelType = PFD_TYPE_RGBA;
        fakePFD.cColorBits = 32;
        fakePFD.cAlphaBits = 8;
        fakePFD.cDepthBits = 24;

        const int fakePFDID = ChoosePixelFormat(tempDC, &fakePFD);
        if (fakePFDID == 0)
        {
            MICHKA_ERROR("ChoosePixelFormat() failed.");
        }

        if (SetPixelFormat(tempDC, fakePFDID, &fakePFD) == false)
        {
            MICHKA_ERROR("SetPixelFormat() failed.");
        }

        HGLRC fakeRC = wglCreateContext(tempDC);

        if (fakeRC == 0)
        {
            MICHKA_ERROR("wglCreateContext() failed.");
        }

        if (wglMakeCurrent(tempDC, fakeRC) == false)
        {
            MICHKA_ERROR("wglMakeCurrent() failed.");
        }

        wglChoosePixelFormatARB = nullptr;
        wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
        if (wglChoosePixelFormatARB == nullptr)
        {
            MICHKA_ERROR("wglGetProcAddress() failed.");
        }

        wglCreateContextAttribsARB = nullptr;
        wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
        if (wglCreateContextAttribsARB == nullptr)
        {
            MICHKA_ERROR("wglGetProcAddress() failed.");
        }

        wglDeleteContext(fakeRC);
        ReleaseDC(tempHwnd, tempDC);
        DestroyWindow(tempHwnd);

        initOpenGLRenderContext(michkaDefaultHwnd, michkaDefaultHdc, michkaDefaultOGLRenderContext);

        if (!wglMakeCurrent(michkaDefaultHdc, michkaDefaultOGLRenderContext))
        {
            MICHKA_ERROR("wglMakeCurrent() failed.");
        }
    }

    void unloadOpenGLWindowsExtensions()
    {
        wglDeleteContext(michkaDefaultOGLRenderContext);
        ReleaseDC(michkaDefaultHwnd, michkaDefaultHdc);
        DestroyWindow(michkaDefaultHwnd);
        wglMakeCurrent(NULL, NULL);
    }

    void initOpenGLRenderContext(HWND _hwnd, HDC& _hdc, HGLRC& _renderContext)
    {
        destroyOpenGLRenderContext(_hwnd, _hdc, _renderContext);

        _hdc = GetDC(_hwnd);

        const int pixelAttribs[] =
        {
            WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
            WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
            WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB,         32,
            WGL_ALPHA_BITS_ARB,         8,
            WGL_DEPTH_BITS_ARB,         24,
            WGL_STENCIL_BITS_ARB,       8,
            WGL_SAMPLE_BUFFERS_ARB,     GL_TRUE,
            WGL_SAMPLES_ARB,            4,
            0
        };

        int pixelFormatID;
        u32 numFormats;
        const bool status = wglChoosePixelFormatARB(_hdc, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

        if (status == false || numFormats == 0)
        {
            MICHKA_ERROR("wglChoosePixelFormatARB() failed.");
        }

        PIXELFORMATDESCRIPTOR PFD;
        DescribePixelFormat(_hdc, pixelFormatID, sizeof(PFD), &PFD);
        SetPixelFormat(_hdc, pixelFormatID, &PFD);

        const int contextAttribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 4,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        if (michkaDefaultOGLRenderContext == NULL)
        {
            michkaDefaultOGLRenderContext = wglCreateContextAttribsARB(_hdc, 0, contextAttribs);

            if (michkaDefaultOGLRenderContext == NULL)
            {
                MICHKA_ERROR("wglCreateContextAttribsARB() failed.");
            }
        }
        _renderContext = michkaDefaultOGLRenderContext;
    }

    void destroyOpenGLRenderContext(HWND _hwnd, HDC& _hdc, HGLRC& _renderContext)
    {
        _renderContext = 0;

        if (_hdc)
        {
            ReleaseDC(_hwnd, _hdc);
            _hdc = 0;
        }
    }
}
