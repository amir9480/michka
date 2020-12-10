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

#ifndef __OPENGL_TEXTURE_H__
#define __OPENGL_TEXTURE_H__

#include "Core/Defines.h"
#include "Graphics/Texture.h"
#include "OpenGLHeaders.h"

namespace Michka
{
    class MICHKA_API OpenGLTexture : public Texture
    {
        friend class OpenGLDevice;
    public:
        OpenGLTexture();
        virtual ~OpenGLTexture();

        virtual void destroy() override;

        virtual Image::Format getFormat() const override;

        virtual u32 getHeight() const override;

        virtual u32 getWidth() const override;

        virtual void set(const void* _data, const u32& _size);

        virtual void set(const Image& _image);

    protected:
        OpenGLDevice* mDevice = nullptr;
        Image::Format mFormat = Image::Format::unknown;
        u32           mTexture = 0;
        u32           mWidth = 0;
        u32           mHeight = 0;
    };
}

#endif // __OPENGL_TEXTURE_H__
