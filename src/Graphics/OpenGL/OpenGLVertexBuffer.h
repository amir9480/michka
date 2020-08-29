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

#ifndef __OPENGL_VERTEX_BUFFER_H__
#define __OPENGL_VERTEX_BUFFER_H__

#include "Core/Defines.h"
#include "Graphics/VertexBuffer.h"
#include "OpenGLHeaders.h"

namespace Michka
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
        friend class OpenGLDevice;
    public:
        OpenGLVertexBuffer();
        virtual ~OpenGLVertexBuffer();

        virtual void destroy() override;

        virtual void set(const void* _vertices, const u32& _size) override;

    protected:
        OpenGLDevice* mDevice = nullptr;
        u32           mSize = 0;
	    u32	          mVAO = 0;
	    u32	          mVBO = 0;
        bool          mStatic = false;
    };
}

#endif // __OPENGL_VERTEX_BUFFER_H__
