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

#ifndef __OPENGL_SHADER_H__
#define __OPENGL_SHADER_H__

#include "Core/Defines.h"
#include "Graphics/Shader.h"
#include "OpenGLHeaders.h"
#include "Core/Container/Map.h"

namespace Michka
{
    class MICHKA_API OpenGLShader : public Shader
    {
        friend class OpenGLDevice;
    public:
        virtual ~OpenGLShader();

        virtual bool compile() override;

        virtual void destroy() override;

        virtual bool set(const String& _name, const bool& _value) override;
        virtual bool set(const String& _name, const int& _value) override;
        virtual bool set(const String& _name, const f32& _value) override;
        virtual bool set(const String& _name, const f32& _valueX, const f32& _valueY) override;
        virtual bool set(const String& _name, const Vector2& _value) override;
        virtual bool set(const String& _name, const f32& _valueX, const f32& _valueY, const f32& _valueZ) override;
        virtual bool set(const String& _name, const Vector3& _value) override;
        virtual bool set(const String& _name, const f32& _valueX, const f32& _valueY, const f32& _valueZ, const f32& _valueW) override;
        virtual bool set(const String& _name, const Vector4& _value) override;
        virtual bool set(const String& _name, const Matrix3& _value) override;
        virtual bool set(const String& _name, const Matrix& _value) override;
        virtual bool set(const String& _name, const Texture* _value) override;

        virtual void setPixelShader(const String& _source) override;

        virtual void setVertexShader(const String& _source) override;
    protected:
        OpenGLShader();
        FORCE_INLINE int getUniformLocation(const String& _name) const;

    protected:
        OpenGLDevice*               mDevice = nullptr;
        u32                         mProgram = 0;
        Map<String, const Texture*> mTextures;
    };
}

#endif // __OPENGL_SHADER_H__
