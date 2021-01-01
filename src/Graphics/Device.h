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

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Core/Defines.h"
#include "Core/Math/Vector4.h"
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
        enum class Driver
        {
#           if MICHKA_OPEN_GL_SUPPORT
                openGL,
#           endif
        };
    public:
        virtual ~Device();

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
        virtual void clear(const bool& _backBuffer = true, const bool& _depthBuffer = true, const bool& _stencil = true, const Vector4& _backBufferValue = Vector4(0.0f, 0.0f, 0.0f, 0.0f), const f32& _depthValue = 0.0f, const u8& _stencilValue = 0) = 0;

        /**
         * @brief Create an Index Buffer.
         *
         * @param _static
         */
        virtual IndexBuffer* createIndexBuffer(const bool& _static = true) = 0;

        /**
         * @brief Create a Shader.
         *
         * @param _vertexShader
         * @param _pixelShader
         */
        virtual Shader* createShader(const String& _vertexShader = "", const String& _pixelShader = "") = 0;

        /**
         * @brief Create a texture.
         *
         * @param _width
         * @param _height
         * @param _format
         * @param _renderTarget  texture is a render target or not.
         */
        virtual Texture* createTexture(const u32& _width, const u32& _height, const TextureFormat& _format, const bool& _renderTarget = false) = 0;

        /**
         * @brief Create a texture from image.
         *
         * @param _image
         */
        virtual Texture* createTexture(const Image& _image);

        /**
         * @brief Create a Vertex Buffer.
         *
         * @param _vertexDeclaration
         * @param _static
         */
        virtual VertexBuffer* createVertexBuffer(VertexDeclaration* _vertexDeclaration, const bool& _static = true) = 0;

        /**
         * @brief Draw on render target.
         */
        virtual void draw() = 0;

        /**
         * @brief Show a texture on the screen.
         */
        virtual void drawOnScreen(const Texture* _texture) = 0;

        /**
         * @brief Draw a simple texture.
         *
         * @param _texture
         * @param _x
         * @param _y
         * @param _width
         * @param _height
         */
        virtual void drawQuad(const Texture* _texture, const u32& _x = 0, const u32& _y = 0, const u32& _width = 0, const u32& _height = 0) = 0;

        /**
         * @brief Get the output window.
         */
        virtual Window* getWindow() const;

        /**
         * @brief Singleton instance getter.
         *
         * @param _driver
         */
        static Device* instance(const Driver& _driver);

        /**
         * @brief Set the detph buffer.
         *
         * @param _renderTarget
         */
        virtual bool setDepthBuffer(const Texture* _depthBuffer = nullptr) = 0;

        /**
         * @brief Set current index buffer.
         *
         * @param _indexBuffer
         */
        virtual void setIndexBuffer(IndexBuffer* _indexBuffer = nullptr) = 0;

        /**
         * @brief Set the Render target of device.
         *
         * @param _index index of render target
         * @param _renderTarget should be a texture with render target attribute enabeld. pass nullptr to unset.
         * @return false is was not successful.
         */
        virtual bool setRenderTarget(const u8& _index, const Texture* _renderTarget = nullptr) = 0;

        /**
         * @brief Set curren shader.
         *
         * @param _shader
         */
        virtual void setShader(Shader* _shader) = 0;

        /**
         * @brief Set current vertex buffer.
         *
         * @param _vertexBuffer
         */
        virtual void setVertexBuffer(VertexBuffer* _vertexBuffer = nullptr) = 0;

    protected:
        Window*         mWindow = nullptr;
        IndexBuffer*    mCurrentIndexBuffer = nullptr;
        VertexBuffer*   mCurrentVertexBuffer = nullptr;
        Shader*         mCurrentShader = nullptr;
    };
}

#endif // __DEVICE_H__
