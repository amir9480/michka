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

    TextureFormat OpenGLTexture::getFormat() const
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

    bool OpenGLTexture::isRenderTarget() const
    {
        return mRenderTarget;
    }

    void OpenGLTexture::set(const void* _data, const u32& _size)
    {
        if (mTexture)
        {
            i32 format = 0;
            switch (mFormat)
            {
            case TextureFormat::r8g8b8:
                format = GL_RGB;
                break;
            case TextureFormat::r8g8b8a8:
                format = GL_RGBA;
                break;
            case TextureFormat::depth32:
                format = GL_DEPTH_COMPONENT32F;
                break;
            default:
                return;
            }
            GLint currentTextureId;
            glGetIntegerv(GL_TEXTURE_2D, &currentTextureId);

            glBindTexture(GL_TEXTURE_2D, mTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

            glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format == GL_DEPTH_COMPONENT32F ? GL_DEPTH_COMPONENT : format, GL_UNSIGNED_BYTE, _data);
            if (_data != nullptr)
            {
                glGenerateMipmap(GL_TEXTURE_2D);
            }

            glBindTexture(GL_TEXTURE_2D, currentTextureId);
        }
    }

    void OpenGLTexture::set(const Image& _image)
    {
        mWidth = _image.getWidth();
        mHeight = _image.getHeight();
        mFormat = (TextureFormat)_image.getFormat();
        set(_image.getFlipped().getData(), _image.getSize());
    }
}
