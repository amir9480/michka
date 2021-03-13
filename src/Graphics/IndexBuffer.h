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

#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

#include "Core/Helpers.h"
#include "MichkaGenerated/Graphics/IndexBuffer.generated.h"

namespace Michka
{
    class MICHKA_API IndexBuffer
    {
        MICHKA_CLASS();
        friend class Device;
    public:
        ~IndexBuffer();

        /**
         * @brief Destroy index buffer.
         */
        void destroy();

        /**
         * @brief Set index buffer.
         *
         * @param _indices
         * @param _count
         * @return Self
         */
        IndexBuffer* set(const u32* _indices, const u32& _count);

    protected:
        IndexBuffer();

    protected:
        u32     mCount = 0;
        bool    mStatic = false;

#       if MICHKA_GRAPHICS == MICHKA_OPENGL
            u32	mIndexBuffer = 0;
#       endif
    };
}

#endif // __INDEX_BUFFER_H__
