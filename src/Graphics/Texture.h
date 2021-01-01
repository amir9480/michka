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
        virtual ~Texture();

        /**
         * @brief Destroy texture.
         */
        virtual void destroy() = 0;

        /**
         * @brief Get content of image.
         */
        virtual Image get() const = 0;

        /**
         * @brief Get texture format.
         */
        virtual TextureFormat getFormat() const = 0;

        /**
         * @brief Get texture height.
         */
        virtual u32 getHeight() const = 0;

        /**
         * @brief Get texture width.
         */
        virtual u32 getWidth() const = 0;

        /**
         * @brief Is texture a render target or not.
         */
        virtual bool isRenderTarget() const = 0;

        /**
         * @brief Set texture buffer.
         *
         * @param _data
         * @param _size
         */
        virtual void set(const void* _data, const u32& _size) = 0;

        /**
         * @brief Set texture buffer.
         *
         * @param _image
         */
        virtual void set(const Image& _image) = 0;
    };
}

#endif // __TEXTURE_H__
