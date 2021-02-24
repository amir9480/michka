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

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Core/Defines.h"
#include "Core/Container/Color.h"
#include "Core/Reflection/ReflectionClass.h"

namespace Michka
{
    class MICHKA_API Image
    {
        MICHKA_CLASS(Image);
    public:
        enum class Format : u32
        {
            unknown,
            r8g8b8,
            r8g8b8a8,
        };
    public:
        Image();
        Image(const String& _path);
        Image(const u32& _width, const u32& _height, const Format& _format, u8* _data = nullptr);
        Image(const Image& _other);
        Image(Image&& _other);
        ~Image();

        /**
         * @brief Memory used per pixel based on format.
         *
         * @param _format
         */
        static u8 bytesPerPixel(const Format& _format);

        /**
         * @brief Destroy image data.
         */
        void destroy();

        /**
         * @brief Flip image.
         *
         * @param _horizontal
         * @param _vertical
         * @return false if was not successful.
         */
        bool flip(const bool& _horizontal = false, const bool& _vertical = true);

        /**
         * @brief Memory used per pixel based on format.
         *
         * @param _format
         */
        u8 getBytesPerPixel() const;

        /**
         * @brief Get access to raw data.
         */
        u8* getData() const;

        /**
         * @brief Get the flipped copy of this image.
         *
         * @param _horizontal
         * @param _vertical
         */
        Image getFlipped(const bool& _horizontal = false, const bool& _vertical = true) const;

        /**
         * @brief Get image format.
         */
        Format getFormat() const;

        /**
         * @brief Get image height.
         */
        u32 getHeight() const;

        /**
         * @brief Get the pixel value at specific position.
         *
         * @param _x
         * @param _y
         */
        Color getPixel(const u32& _x, const u32& _y) const;

        /**
         * @brief Get the buffer size in bytes.
         */
        u32 getSize() const;

        /**
         * @brief Get image width.
         */
        u32 getWidth() const;

        /**
         * @brief Save image as file. supported formats: jpg, png, bmp
         * @param _path
         * @param _quality a number between 1 and 100 to set quality of image for jpg only.
         *
         * @return false if was not successful.
         */
        bool save(const String& _path, const u8& _quality = 100) const;

        /**
         * @brief Set content of image directly.
         *
         * @param _width
         * @param _height
         * @param _format
         * @param _data   should be in heap not stack and will be free automatically.
         */
        void set(const u32& _width, const u32& _height, const Format& _format, u8* _data = nullptr);

        /**
         * @brief Change a pixel color.
         *
         * @param _x
         * @param _y
         * @param _color
         * @return false if was not successful.
         */
        bool setPixel(const u32& _x, const u32& _y, const Color& _color);

        Image& operator = (const Image& _other);
        Image& operator = (Image&& _other);

        bool operator == (const Image& _other) const;
        bool operator != (const Image& _other) const;

    protected:
        u8* mData = nullptr;
        Format mFormat;
        u32 mWidth = 0;
        u32 mHeight = 0;
    };
}

#endif // __IMAGE_H__
