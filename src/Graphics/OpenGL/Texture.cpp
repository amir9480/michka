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

#include "Graphics/Texture.h"
#include "OpenGLHeaders.h"

namespace Michka
{
    void Texture::destroy()
    {
        if (mTexture)
        {
	        glDeleteTextures(1, &mTexture);
            mTexture = 0;
        }
    }

    Image Texture::get() const
    {
        Image out;
        Image::Format imageFormat = Image::Format::unknown;

        switch (mFormat)
        {
        case TextureFormat::r8g8b8:
            imageFormat = Image::Format::r8g8b8;
            break;
        case TextureFormat::r8g8b8a8:
            imageFormat = Image::Format::r8g8b8a8;
            break;
        }

        if (imageFormat != Image::Format::unknown)
        {
            i32 glFormat = textureFormatToGLFormat(mFormat);
            u8* data = new u8[mWidth * mHeight * Image::bytesPerPixel(imageFormat)];
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mTexture);
            glGetTexImage(GL_TEXTURE_2D, 0, glFormat, GL_UNSIGNED_BYTE, data);
            glBindTexture(GL_TEXTURE_2D, 0);
            out.set(mWidth, mHeight, imageFormat, data);
            out.flip();
        }

        return out;
    }

    Texture* Texture::set(const void* _data, const u32& _size)
    {
        if (mTexture)
        {
            i32 format = textureFormatToGLFormat(mFormat);
            GLint currentTextureId;
            glGetIntegerv(GL_TEXTURE_2D, &currentTextureId);

            glBindTexture(GL_TEXTURE_2D, mTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format == GL_DEPTH_COMPONENT32F ? GL_DEPTH_COMPONENT : format, GL_UNSIGNED_BYTE, _data);

            if (_data != nullptr)
            {
                glGenerateMipmap(GL_TEXTURE_2D);
            }

            setFilter(mFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

            glBindTexture(GL_TEXTURE_2D, currentTextureId);
        }

        return this;
    }

    Texture* Texture::set(const Image& _image)
    {
        mWidth = _image.getWidth();
        mHeight = _image.getHeight();
        mFormat = (TextureFormat)_image.getFormat();
        set(_image.getFlipped().getData(), _image.getSize());

        return this;
    }

    Texture* Texture::setFilter(const Texture::Filter& _filter)
    {
        mFilter = _filter;
        if (mTexture != 0)
        {
            GLint currentTextureId;
            glGetIntegerv(GL_TEXTURE_2D, &currentTextureId);
            glBindTexture(GL_TEXTURE_2D, mTexture);

            switch(_filter)
            {
            case Texture::Filter::default:
                setFilter(defaultFilter);
                mFilter = _filter; // Prevent change mFilter value from default
                break;
            case Texture::Filter::none:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
                break;
            case Texture::Filter::linear:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
                break;
            case Texture::Filter::trilinear:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
                break;
            case Texture::Filter::anisotropic2:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
                break;
            case Texture::Filter::anisotropic4:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
                break;
            case Texture::Filter::anisotropic8:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);
                break;
            case Texture::Filter::anisotropic16:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
                break;
            };

            if (_filter == Filter::none)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            else if (_filter != Filter::default)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }

            glBindTexture(GL_TEXTURE_2D, currentTextureId);
        }

        return this;
    }

    i32 Texture::textureFormatToGLFormat(const TextureFormat& _format)
    {
        i32 format = 0;
        switch (_format)
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
        }

        return format;
    }
}
