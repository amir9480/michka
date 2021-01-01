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
    class MICHKA_API OpenGLDevice : public Device
    {
    public:
        OpenGLDevice();
        virtual ~OpenGLDevice();

        virtual void clear(const bool& _backBuffer = true, const bool& _depthBuffer = true, const bool& _stencil = true, const Vector4& _backBufferValue = Vector4(0.0f, 0.0f, 0.0f, 0.0f), const f32& _depthValue = 0.0f, const u8& _stencilValue = 0) override;

        virtual IndexBuffer* createIndexBuffer(const bool& _static = true) override;

        virtual Shader* createShader(const String& _vertexShader = "", const String& _pixelShader = "") override;

        virtual Texture* createTexture(const u32& _width, const u32& _height, const TextureFormat& _format, const bool& _renderTarget = false);

        virtual VertexBuffer* createVertexBuffer(VertexDeclaration* _vertexDeclaration, const bool& _static = true) override;

        virtual void draw() override;

        virtual void drawOnScreen(const Texture* _texture) override;

        virtual void drawQuad(const Texture* _texture, const u32& _x = 0, const u32& _y = 0, const u32& _width = 0, const u32& _height = 0) override;

        virtual bool setDepthBuffer(const Texture* _depthBuffer = nullptr) override;

        virtual void setIndexBuffer(IndexBuffer* _indexBuffer = nullptr) override;

        virtual bool setRenderTarget(const u8& _index, const Texture* _renderTarget = nullptr) override;

        virtual void setShader(Shader* _shader) override;

        virtual void setVertexBuffer(VertexBuffer* _vertexBuffer = nullptr) override;

    private:
#       if (MICHKA_PLATFORM == MICHKA_PLATFORM_WIN32)
            HWND mHwnd = 0;
            HDC mHdc = 0;
            HGLRC mOGLRenderContext = 0;
#       endif

	    u32 mVertexArray = 0;
        u32 mFrameBuffer = 0;
        Map<u8, const Texture*> mRenderTargets;
        const Texture* mDepthBuffer = nullptr;
        Shader* mQuadShader = nullptr;
        VertexBuffer* mQuadVertexBuffer = nullptr;
        IndexBuffer* mQuadIndexBuffer = nullptr;
    };
}

#endif // __OPENGL_DEVICE_H__
