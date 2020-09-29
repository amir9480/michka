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

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Core/Defines.h"

namespace Michka
{
    class MICHKA_API Image
    {
    public:
        enum class Format
        {
            unknown,
            r8g8b8,
            r8g8b8a8,
            float32,
        };
    public:
        Image(const String& _path);
        Image(const u32& _width, const u32& _height, const Format& _format, u8* _data = nullptr);
        virtual ~Image();

        /**
         * @brief Destroy image data.
         */
        void destroy();

        /**
         * @brief Get access to raw data.
         */
        u8* getData() const;

        /**
         * @brief Get image format.
         */
        Format getFormat() const;

        /**
         * @brief Get image height.
         */
        u32 getHeight() const;

        /**
         * @brief Get image width.
         */
        u32 getWidth() const;

    protected:
        u8* mData = nullptr;
        Format mFormat;
        u32 mWidth = 0;
        u32 mHeight = 0;
    };
}

#endif // __IMAGE_H__
