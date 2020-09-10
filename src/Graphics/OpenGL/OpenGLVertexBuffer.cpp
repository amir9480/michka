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

#include "OpenGLVertexBuffer.h"
#include "Graphics/VertexDeclaration.h"

namespace Michka
{
    OpenGLVertexBuffer::OpenGLVertexBuffer()
    {
        //
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        destroy();
    }

    void OpenGLVertexBuffer::destroy()
    {
        if (mSize > 0)
        {
            glDeleteVertexArrays(1, &mVAO);
            glDeleteBuffers(1, &mVBO);
            mSize = 0;
            mVAO = 0;
            mVBO = 0;
        }
    }

    void OpenGLVertexBuffer::set(const void* _vertices, const u32& _size)
    {
        destroy();
        mSize = _size;

        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);

	    glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mSize, _vertices, mStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
	    glBindVertexArray(0);
    }
}
