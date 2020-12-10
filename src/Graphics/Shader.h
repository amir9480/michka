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
    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix3;
    class Matrix;
    class Texture;

    class MICHKA_API Shader
    {
    public:
        enum class Type : u8
        {
            vertex,
            pixel
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
         * @brief Set boolean uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const bool& _value) = 0;

        /**
         * @brief Set int uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const int& _value) = 0;

        /**
         * @brief Set float uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const f32& _value) = 0;

        /**
         * @brief Set float 2D uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const f32& _valueX, const f32& _valueY) = 0;

        /**
         * @brief Set vector2D uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const Vector2& _value) = 0;

        /**
         * @brief Set float 3D uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const f32& _valueX, const f32& _valueY, const f32& _valueZ) = 0;

        /**
         * @brief Set vector3D uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const Vector3& _value) = 0;

        /**
         * @brief Set float 4D uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const f32& _valueX, const f32& _valueY, const f32& _valueZ, const f32& _valueW) = 0;

        /**
         * @brief Set vector4D uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const Vector4& _value) = 0;

        /**
         * @brief Set Matrix 3x3 uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const Matrix3& _value) = 0;

        /**
         * @brief Set Matrix 4x4 uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const Matrix& _value) = 0;

        /**
         * @brief Set Texture uniform parameter value.
         *
         * @param _name
         * @param _value
         * @return false if uniform doesn't exists
         */
        virtual bool set(const String& _name, const Texture*& _value) = 0;

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
