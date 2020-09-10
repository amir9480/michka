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

#include "OpenGLDevice.h"
#include "Core/Thread/Thread.h"
#include "Core/Thread/Mutex.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace Michka
{
#   if (MICHKA_PLATFORM == MICHKA_PLATFORM_WIN32)
        extern Mutex windowMutex;
        extern Map<Window*, HWND> windowInstances;
#   endif
    OpenGLDevice::OpenGLDevice()
    {
        mWindow = new Window;
#       if (MICHKA_PLATFORM == MICHKA_PLATFORM_WIN32)
            while (1)
            {
                //! TODO: Improve sleep time
                Thread::sleep(100);
                MutexLock lock(windowMutex);
                if (windowInstances.hasKey(mWindow))
                {
                    break;
                }
            }
            mHwnd = windowInstances[mWindow];
            mHdc = GetDC(mHwnd);

            HWND tempHwnd = CreateWindowW(
                L"MichkaMainWindow", L"Temp",
                WS_CAPTION|WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
                0, 0, 1, 1, 0, 0, GetModuleHandleA(0), 0
            );
            HDC tempDC = GetDC(tempHwnd);

            PIXELFORMATDESCRIPTOR fakePFD;
            ZeroMemory(&fakePFD, sizeof(fakePFD));
            fakePFD.nSize = sizeof(fakePFD);
            fakePFD.nVersion = 1;
            fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
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

            PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
            wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
            if (wglChoosePixelFormatARB == nullptr)
            {
                MICHKA_ERROR("wglGetProcAddress() failed.");
            }

            PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
            wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
            if (wglCreateContextAttribsARB == nullptr)
            {
                MICHKA_ERROR("wglGetProcAddress() failed.");
            }

            const int pixelAttribs[] =
            {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
                WGL_COLOR_BITS_ARB, 32,
                WGL_ALPHA_BITS_ARB, 8,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
                WGL_SAMPLES_ARB, 4,
                0
            };

            int pixelFormatID; u32 numFormats;
            const bool status = wglChoosePixelFormatARB(mHdc, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

            if (status == false || numFormats == 0)
            {
                MICHKA_ERROR("wglChoosePixelFormatARB() failed.");
            }

            PIXELFORMATDESCRIPTOR PFD;
            DescribePixelFormat(mHdc, pixelFormatID, sizeof(PFD), &PFD);
            SetPixelFormat(mHdc, pixelFormatID, &PFD);

            const int contextAttribs[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 4,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
            };

            mOGLRenderContext = wglCreateContextAttribsARB(mHdc, 0, contextAttribs);
            if (mOGLRenderContext == NULL)
            {
                MICHKA_ERROR("wglCreateContextAttribsARB() failed.");
            }

            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(fakeRC);
            ReleaseDC(tempHwnd, tempDC);
            DestroyWindow(tempHwnd);
            if (!wglMakeCurrent(mHdc, mOGLRenderContext))
            {
                MICHKA_ERROR("wglMakeCurrent() failed.");
            }

            if (!gladLoadGL())
            {
                MICHKA_ERROR("Failed to load GLAD.");
            }

#       endif

        mWindow->show();
    }

    OpenGLDevice::~OpenGLDevice()
    {
#       if (MICHKA_PLATFORM == MICHKA_PLATFORM_WIN32)
            wglDeleteContext(mOGLRenderContext);
            ReleaseDC(mHwnd, mHdc);
#       endif
        delete mWindow;
    }

    void OpenGLDevice::clear(const bool& _backBuffer, const bool& _depthBuffer, const bool& _stencil, const Vector4& _backBufferValue, const f32& _depthValue, const u8& _stencilValue)
    {
        u32 flags = 0;

        glClearColor(_backBufferValue.r, _backBufferValue.g, _backBufferValue.b, _backBufferValue.a);
        glClearDepth(_depthValue);
        glClearStencil(_stencilValue);
        glClear(
            (_backBuffer ? GL_COLOR_BUFFER_BIT : 0) |
            (_depthBuffer ? GL_DEPTH_BUFFER_BIT : 0) |
            (_stencil ? GL_STENCIL_BUFFER_BIT : 0)
        );

        SwapBuffers(mHdc);
        InvalidateRect(mHwnd, 0, 1);
    }

    IndexBuffer* OpenGLDevice::createIndexBuffer(const bool& _static)
    {
        OpenGLIndexBuffer* out = new OpenGLIndexBuffer;
        out->mDevice = this;
        out->mStatic = _static;
        return out;
    }

    VertexBuffer* OpenGLDevice::createVertexBuffer(VertexDeclaration* _vertexDeclaration, const bool& _static)
    {
        OpenGLVertexBuffer* out = new OpenGLVertexBuffer;
        out->mDevice = this;
        out->mStatic = _static;
        out->mVertexDeclaration = _vertexDeclaration;
        return out;
    }

    void OpenGLDevice::setVertexBuffer(VertexBuffer* _vertexBuffer)
    {
        if (_vertexBuffer)
        {
            OpenGLVertexBuffer* vertexBuffer = dynamic_cast<OpenGLVertexBuffer*>(_vertexBuffer);
            glBindVertexArray(vertexBuffer->mVAO);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->mVBO);
        }
        else
        {
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        mCurrentVertexBuffer = _vertexBuffer;
    }

    void OpenGLDevice::setIndexBuffer(IndexBuffer* _indexBuffer)
    {
        if (_indexBuffer)
        {
            OpenGLIndexBuffer* vertexBuffer = dynamic_cast<OpenGLIndexBuffer*>(_indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer->mEBO);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        mCurrentIndexBuffer = _indexBuffer;
    }
}
