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

#include "OpenGLTexture.h"

namespace Michka
{
    OpenGLTexture::OpenGLTexture()
    {
        //
    }

    OpenGLTexture::~OpenGLTexture()
    {
        destroy();
    }

    void OpenGLTexture::destroy()
    {
        if (mTexture)
        {
	        glDeleteTextures(1, &mTexture);
            mTexture = 0;
        }
    }

    Image::Format OpenGLTexture::getFormat() const
    {
        return mFormat;
    }

    u32 OpenGLTexture::getHeight() const
    {
        return mHeight;
    }

    u32 OpenGLTexture::getWidth() const
    {
        return mWidth;
    }

    void OpenGLTexture::set(const void* _data, const u32& _size)
    {
        if (mTexture)
        {
            i32 format = 0;
            switch (mFormat)
            {
            case Image::Format::r8g8b8:
                format = GL_RGB;
                break;
            case Image::Format::r8g8b8a8:
                format = GL_RGBA;
                break;
            case Image::Format::float32:
                format = GL_DEPTH_COMPONENT32F;
                break;
            default:
                return;
            }
            GLint currentTextureId;
            glGetIntegerv(GL_TEXTURE_2D, &currentTextureId);

            glBindTexture(GL_TEXTURE_2D, mTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, _data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, currentTextureId);
        }
    }

    void OpenGLTexture::set(const Image& _image)
    {
        set(_image.getData(), _image.getSize());
    }
}
