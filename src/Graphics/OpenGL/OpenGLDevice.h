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

#ifndef __OPENGL_DEVICE_H__
#define __OPENGL_DEVICE_H__

#include "Core/Defines.h"
#include "Graphics/Device.h"
#include "OpenGLHeaders.h"

namespace Michka
{
    class OpenGLDevice : public Device
    {
    public:
        OpenGLDevice();
        virtual ~OpenGLDevice();

        virtual void clear(const bool& _backBuffer = true, const bool& _depthBuffer = true, const bool& _stencil = true, const Vector4& _backBufferValue = Vector4(0.0f, 0.0f, 0.0f, 0.0f), const f32& _depthValue = 0.0f, const u8& _stencilValue = 0) override;

        virtual IndexBuffer* createIndexBuffer(const bool& _static = true);

        virtual VertexBuffer* createVertexBuffer(VertexDeclaration* _vertexDeclaration, const bool& _static = true) override;

        virtual void setVertexBuffer(VertexBuffer* _vertexBuffer = nullptr) override;

        virtual void setIndexBuffer(IndexBuffer* _indexBuffer = nullptr) override;

    private:
#       if (MICHKA_PLATFORM == MICHKA_PLATFORM_WIN32)
            HWND mHwnd = 0;
            HDC mHdc = 0;
            HGLRC mOGLRenderContext = 0;
#       endif
    };
}

#endif // __OPENGL_DEVICE_H__
