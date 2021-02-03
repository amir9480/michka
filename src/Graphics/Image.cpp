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

#include "Image.h"
#include "Core/Container/String.h"
#include "Core/Foundation/File.h"
#include "Core/Foundation/Log.h"
#include "Core/Helpers.h"
 #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
 #define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace Michka
{
    Image::Image()
    {
        //
    }

    Image::Image(const String& _path)
    {
        int channels = 0;
        mData = stbi_load(_path.toUtf8().cstr(), (int*)&mWidth, (int*)&mHeight, &channels, 0);
        switch (channels)
        {
        case 3:
            mFormat = Format::r8g8b8;
            break;
        case 4:
            mFormat = Format::r8g8b8a8;
            break;
        default:
            MICHKA_WARNING("Unknown format."); // @NOCOVERAGE
        }
        if (mData == nullptr)
        {
            MICHKA_WARNING(("Image file \"" + _path + "\" does not exists.").toUtf8().cstr()); // @NOCOVERAGE
        }
    }

    Image::Image(const u32& _width, const u32& _height, const Format& _format, u8* _data) :
        mWidth(_width),
        mHeight(_height),
        mFormat(_format),
        mData(_data)
    {
        //
    }

    Image::Image(const Image& _other)
    {
        *this = _other;
    }

    Image::Image(Image&& _other)
    {
        *this = std::move(_other);
    }

    Image::~Image()
    {
        destroy();
    }

    u8 Image::bytesPerPixel(const Image::Format& _format)
    {
        switch (_format)
        {
        case Image::Format::r8g8b8:
            return 3;
        case Image::Format::r8g8b8a8:
            return 4;
        }

        return 0;
    }

    void Image::destroy()
    {
        if (mData)
        {
            delete[] mData;
            mData = nullptr;
        }
        mWidth = mHeight = 0;
        mFormat = Format::unknown;
    }

    bool Image::flip(const bool& _horizontal, const bool& _vertical)
    {
        if (mData && (_horizontal || _vertical))
        {
            u8 temp[4096];
            u32 imageBytesPerPixel = getBytesPerPixel();
            u32 imageBytesPerRow = imageBytesPerPixel * mWidth;
            u32 halfWidth = mWidth / 2;
            u32 halfHeight = mHeight / 2;

            if (_horizontal)
            {
                for (u32 i = 0; i < mHeight; i++)
                {
                    u8* pointer1 = mData + (i * imageBytesPerRow);
                    u8* pointer2 = pointer1 + imageBytesPerRow - imageBytesPerPixel;
                    for (u32 j = 0; j < halfWidth; j++)
                    {
                        memcpy(temp, pointer1, imageBytesPerPixel);
                        memcpy(pointer1, pointer2, imageBytesPerPixel);
                        memcpy(pointer2, temp, imageBytesPerPixel);
                        pointer1 += imageBytesPerPixel;
                        pointer2 -= imageBytesPerPixel;
                    }
                }
            }

            if (_vertical)
            {
                for (u32 i = 0; i < halfHeight; i++)
                {
                    u8* pointer1 = mData + (i * imageBytesPerRow);
                    u8* pointer2 = mData + ((mHeight - i - 1) * imageBytesPerRow);
                    u32 bytesToCopy = imageBytesPerRow;
                    while (bytesToCopy > 0)
                    {
                        u32 copySize = Michka::min(u32(bytesToCopy), u32(sizeof(temp)));
                        memcpy(temp, pointer1, copySize);
                        memcpy(pointer1, pointer2, copySize);
                        memcpy(pointer2, temp, copySize);
                        bytesToCopy -= copySize;
                        pointer1 += copySize;
                        pointer2 += copySize;
                    }
                }
            }

            return true;
        }

        return false;
    }

    u8 Image::getBytesPerPixel() const
    {
        return bytesPerPixel(mFormat);
    }

    u8* Image::getData() const
    {
        return mData;
    }

    Image Image::getFlipped(const bool& _horizontal, const bool& _vertical) const
    {
        Image temp = *this;
        temp.flip(_horizontal, _vertical);
        return temp;
    }

    Image::Format Image::getFormat() const
    {
        return mFormat;
    }

    u32 Image::getHeight() const
    {
        return mHeight;
    }

    Color Image::getPixel(const u32& _x, const u32& _y) const
    {
        if (mData == nullptr || _x >= mWidth || _y >= mHeight)
        {
            return Color::black;
        }

        u8 bpp = getBytesPerPixel();
        u8* dataAtPosition = &mData[(_y*mHeight + _x) * bpp];

        switch (mFormat)
        {
        case Image::Format::r8g8b8:
            return Color(dataAtPosition[0], dataAtPosition[1], dataAtPosition[2], 255);
        case Image::Format::r8g8b8a8:
            return Color(dataAtPosition[0], dataAtPosition[1], dataAtPosition[2], dataAtPosition[3]);
        }

        return Color::black;
    }

    u32 Image::getSize() const
    {
        return mWidth * mHeight * getBytesPerPixel();
    }

    u32 Image::getWidth() const
    {
        return mWidth;
    }

    bool Image::save(const String& _path, const u8& _quality) const
    {
        if (mData && mWidth > 0 && mHeight > 0 && _path.isNotEmpty())
        {
            String pathDirectory = File::directory(_path);
            if (File::exists(pathDirectory) == false)
            {
                if (File::createDirectory(pathDirectory) == false)
                {
                    return false; // @NOCOVERAGE
                }
            }
            if (File::exists(_path))
            {
                if (File::remove(_path) == false)
                {
                    return false; // @NOCOVERAGE
                }
            }
            String extension = _path.split('.').last().toLower();
            if (extension == "jpg" || extension == "jpeg")
            {
                return stbi_write_jpg(_path.toUtf8().cstr(), mWidth, mHeight, getBytesPerPixel(), mData, _quality) != 0;
            }
            else if (extension == "png")
            {
                return stbi_write_png(_path.toUtf8().cstr(), mWidth, mHeight, getBytesPerPixel(), mData, 0) != 0;
            }
            else if (extension == "bmp")
            {
                return stbi_write_bmp(_path.toUtf8().cstr(), mWidth, mHeight, getBytesPerPixel(), mData) != 0;
            }
        }

        return false; // @NOCOVERAGE
    }

    void Image::set(const u32& _width, const u32& _height, const Format& _format, u8* _data)
    {
        destroy();
        mWidth = _width;
        mHeight = _height;
        mFormat = _format;
        mData = _data;
    }

    bool Image::setPixel(const u32& _x, const u32& _y, const Color& _color)
    {
        switch (mFormat)
        {
        case Format::r8g8b8: case Format::r8g8b8a8:
            if (mData && _x < mWidth && _y < mHeight)
            {
                u32 imageBytesPerPixel = getBytesPerPixel();
                u32 imageBytesPerRow = mWidth * imageBytesPerPixel;
                u8* pointer = mData + (imageBytesPerRow * _y) + (imageBytesPerPixel * _x);
                pointer[0] = _color.r;
                pointer[1] = _color.g;
                pointer[2] = _color.b;
                if (mFormat == Format::r8g8b8a8)
                {
                    pointer[3] = _color.a;
                }
            }
        }
        return false;
    }

    Image& Image::operator = (const Image& _other)
    {
        destroy();
        u32 size = _other.getSize();
        mWidth = _other.mWidth;
        mHeight = _other.mHeight;
        mFormat = _other.mFormat;
        if (_other.mData)
        {
            mData = new u8[size];
            memcpy(mData, _other.mData, size);
        }

        return *this;
    }

    Image& Image::operator = (Image&& _other)
    {
        destroy();
        swap(mData, _other.mData);
        swap(mWidth, _other.mWidth);
        swap(mHeight, _other.mHeight);
        swap(mFormat, _other.mFormat);

        return *this;
    }

    bool Image::operator == (const Image& _other) const
    {
        if (mData == nullptr && _other.mData == nullptr)
        {
            return true;
        }
        if (mWidth == _other.mWidth && mHeight == _other.mHeight && mData && _other.mData)
        {
            for (u32 i = 0; i < mWidth; i++)
            {
                for (u32 j = 0; j < mHeight; j++)
                {
                    if (getPixel(i, j) != _other.getPixel(i, j))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        return false;
    }

    bool Image::operator != (const Image& _other) const
    {
        return !(*this == _other);
    }
}
