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

#ifndef __SHADER_H__
#define __SHADER_H__

#include "Core/Defines.h"
#include "Core/Container/Map.h"
#include "Core/Container/String.h"

namespace Michka
{
    class MICHKA_API Shader
    {
    public:
        enum class Type : u8
        {
            Vertex,
            Pixel
        };
    public:
        virtual ~Shader();

        /**
         * @brief Compile shader.
         *
         * @return true if compiled and linked successfully.
         */
        virtual bool compile() = 0;

        /**
         * @brief Get the Compile/Link Errors if \fn compile failed.
         */
        virtual String getErrors() const;

        /**
         * @brief Destroy vertex buffer.
         */
        virtual void destroy() = 0;

        /**
         * @brief Set the Pixel Shader source.
         *
         * @param _source
         */
        virtual void setPixelShader(const String& _source) = 0;

        /**
         * @brief Set the Vertex Shader source.
         *
         * @param _source
         */
        virtual void setVertexShader(const String& _source) = 0;

    protected:
        String mErrors;
        Map<Shader::Type, String> mShadersSources;
    };
}

#endif // __SHADER_H__
