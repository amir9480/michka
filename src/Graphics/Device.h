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
#include "Platform/Window.h"

namespace Michka
{
    class VertexBuffer;

    class MICHKA_API Device
    {
    public:
        enum class Driver
        {
#           if MICHKA_OPEN_GL_SUPPORT
                OpenGL,
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
         * @brief Create a Vertex Buffer.
         */
        virtual VertexBuffer* createVertexBuffer() = 0;

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
    protected:
        Window* mWindow;
    };
}

#endif // __DEVICE_H__
