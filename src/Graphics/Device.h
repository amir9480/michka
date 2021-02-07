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

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Core/Defines.h"
#include "Core/Container/Color.h"
#include "GraphicDefines.h"
#include "Platform/Window.h"

namespace Michka
{
    class Image;
    class IndexBuffer;
    class Shader;
    class Texture;
    class VertexBuffer;
    class VertexDeclaration;

    class MICHKA_API Device
    {
    public:
        ~Device();

        /**
         * @brief Clear render target.
         *
         * @param _backBuffer
         * @param _depthBuffer
         * @param _stencil
         * @param _backBufferValue
         * @param _depthValue
         * @param _stencilValue
         */
        void clear(const bool& _backBuffer = true, const bool& _depthBuffer = true, const bool& _stencil = true, const Color& _backBufferValue = Color(0, 0, 0, 0), const f32& _depthValue = 0.0f, const u8& _stencilValue = 0);

        /**
         * @brief Create an Index Buffer.
         *
         * @param _static
         */
        IndexBuffer* createIndexBuffer(const bool& _static = true);

        /**
         * @brief Create a Shader from source code.
         *
         * @param _source
         */
        Shader* createShader(const String& _source = "");

        /**
         * @brief Create a texture.
         *
         * @param _width
         * @param _height
         * @param _format
         * @param _renderTarget  texture is a render target or not.
         */
        Texture* createTexture(const u32& _width, const u32& _height, const TextureFormat& _format, const bool& _renderTarget = false);

        /**
         * @brief Create a texture from image.
         *
         * @param _image
         */
        Texture* createTexture(const Image& _image);

        /**
         * @brief Create a Vertex Buffer.
         *
         * @param _vertexDeclaration
         * @param _static
         */
        VertexBuffer* createVertexBuffer(VertexDeclaration* _vertexDeclaration, const bool& _static = true);

        /**
         * @brief Draw on render target.
         */
        void draw();

        /**
         * @brief Show a texture on the screen.
         */
        void drawOnScreen(const Texture* _texture);

        /**
         * @brief Draw a simple texture.
         *
         * @param _texture
         * @param _x
         * @param _y
         * @param _width
         * @param _height
         */
        void drawQuad(const Texture* _texture, const u32& _x = 0, const u32& _y = 0, const u32& _width = 0, const u32& _height = 0);

        /**
         * @brief Get the Max Anisotropy value.
         */
        u32 getMaxAnisotropy();

        /**
         * @brief Get the output window.
         */
        Window* getWindow() const;

        /**
         * @brief Singleton instance getter.
         *
         * @param _driver
         */
        static Device* instance();

        /**
         * @brief Set the detph buffer.
         *
         * @param _renderTarget
         */
        bool setDepthBuffer(const Texture* _depthBuffer = nullptr);

        /**
         * @brief Set current index buffer.
         *
         * @param _indexBuffer
         */
        void setIndexBuffer(IndexBuffer* _indexBuffer = nullptr);

        /**
         * @brief Set the Render target of device.
         *
         * @param _index index of render target
         * @param _renderTarget should be a texture with render target attribute enabeld. pass nullptr to unset.
         * @return false is was not successful.
         */
        bool setRenderTarget(const u8& _index, const Texture* _renderTarget = nullptr);

        /**
         * @brief Set curren shader.
         *
         * @param _shader
         */
        void setShader(Shader* _shader);

        /**
         * @brief Set current vertex buffer.
         *
         * @param _vertexBuffer
         */
        void setVertexBuffer(VertexBuffer* _vertexBuffer = nullptr);

        /**
         * @brief Set the main window.
         *
         * @param _window
         */
        void setWindow(Window* _window);

    protected:
        Device();

    protected:
        Window*                 mWindow = nullptr;
        IndexBuffer*            mCurrentIndexBuffer = nullptr;
        VertexBuffer*           mCurrentVertexBuffer = nullptr;
        Shader*                 mCurrentShader = nullptr;
        Map<u8, const Texture*> mRenderTargets;
        const Texture*          mDepthBuffer = nullptr;
        VertexBuffer*           mQuadVertexBuffer = nullptr;
        IndexBuffer*            mQuadIndexBuffer = nullptr;
        Shader*                 mQuadShader = nullptr;
        u32                     mMaxAnisotropy = 0xffffffff;

#       if MICHKA_GRAPHICS == MICHKA_OPENGL
            u32 mVertexArray = 0;
            u32 mFrameBuffer = 0;
#       endif
    };
}

#endif // __DEVICE_H__
