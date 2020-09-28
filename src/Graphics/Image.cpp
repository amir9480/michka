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

#include "Image.h"
#include "Core/Container/String.h"
#include "Core/Helpers.h"
 #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Michka
{
    Image::Image(const String& _path)
    {
        stbi_set_flip_vertically_on_load(true);
        int channels = 0;
        mData = stbi_load(_path.toUtf8().cstr(), (int*)&mWidth, (int*)&mHeight, &channels, 0);
        switch (channels)
        {
        case 3:
            mFormat = Format::rgb8;
            break;
        case 4:
            mFormat = Format::rgba8;
            break;
        default:
            MICHKA_ERROR("Unknown format.");
        }
        if (mData == nullptr)
        {
            MICHKA_ERROR(("Image file \"" + _path + "\" does not exists.").toUtf8().cstr());
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

    Image::~Image()
    {
        destroy();
    }

    void Image::destroy()
    {
        if (mData)
        {
            delete[] mData;
        }
        mWidth = mHeight = 0;
        mFormat = Format::unknown;
    }
}
