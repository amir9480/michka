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

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Core/Defines.h"
#include "GraphicDefines.h"
#include "Image.h"

namespace Michka
{
    class MICHKA_API Texture
    {
    public:
        enum class Filter: u8
        {
            default,
            none,
            linear,
            trilinear,
            anisotropic2,
            anisotropic4,
            anisotropic8,
            anisotropic16,
        };
    private:
        friend class Device;
    public:
        ~Texture();

        /**
         * @brief Destroy texture.
         */
        void destroy();

        /**
         * @brief Get content of image.
         */
        Image get() const;

        /**
         * @brief Get texture current filter.
         */
        Filter getFilter() const;

        /**
         * @brief Get texture format.
         */
        TextureFormat getFormat() const;

        /**
         * @brief Get texture height.
         */
        u32 getHeight() const;

        /**
         * @brief Get texture width.
         */
        u32 getWidth() const;

        /**
         * @brief Is texture a render target or not.
         */
        bool isRenderTarget() const;

        /**
         * @brief Set texture buffer.
         *
         * @param _data
         * @param _size
         * @return Self
         */
        Texture* set(const void* _data, const u32& _size);

        /**
         * @brief Set texture buffer.
         *
         * @param _image
         * @return Self
         */
        Texture* set(const Image& _image);

        /**
         * @brief Set the texture filter.
         *
         * @param _filter
         * @return Self
         */
        Texture* setFilter(const Filter& _filter = Filter::default);

    protected:
        Texture();

#       if MICHKA_GRAPHICS == MICHKA_OPENGL
            static i32 textureFormatToGLFormat(const TextureFormat& _format);
#       endif
    protected:
        TextureFormat mFormat = TextureFormat::unknown;
        u32           mWidth = 0;
        u32           mHeight = 0;
        bool          mRenderTarget = false;
        Filter        mFilter = Filter::default;

#       if MICHKA_GRAPHICS == MICHKA_OPENGL
            u32           mTexture = 0;
#       endif
    public:
        static Filter defaultFilter;
    };
}

#endif // __TEXTURE_H__
