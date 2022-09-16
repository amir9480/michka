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

#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#include "Core/Helpers.h"
#include "VertexDeclaration.h"

namespace Michka
{
    class MICHKA_API VertexBuffer
    {
        MICHKA_CLASS();
        friend class Device;
    public:
        ~VertexBuffer();

        /**
         * @brief Destroy vertex buffer.
         */
        void destroy();

        /**
         * @brief Set vertex buffer.
         *
         * @param _vertices
         * @param _size
         * @return Self
         */
        VertexBuffer* set(const void* _vertices, const u32& _size);

    protected:
        VertexBuffer();

    protected:
        VertexDeclaration*  mVertexDeclaration = nullptr;
        u32                 mSize = 0;
        bool                mStatic = false;

#       if MICHKA_GRAPHICS == MICHKA_OPENGL
            u32 mVertexBuffer = 0;
#       endif
    };
}

#endif // __VERTEX_BUFFER_H__
