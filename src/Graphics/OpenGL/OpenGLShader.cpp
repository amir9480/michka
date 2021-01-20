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

#include "OpenGLShader.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"
#include "Core/Math/Matrix3.h"
#include "Core/Math/Matrix.h"

namespace Michka
{
    OpenGLShader::OpenGLShader()
    {
        //
    }

    OpenGLShader::~OpenGLShader()
    {
        destroy();
    }

    bool OpenGLShader::compile(const String& _source)
    {
        char* tempStr = nullptr;
        int success = 0;
        char errorsBuffer[2048];
        Vector<u32> shaders;
        String8 shaderSource;

        mSource = _source;

        u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
        shaderSource = ("#version 440 core\n#define COMPILING_VERTEX_SHADER 1\n#define COMPILING_FRAGMENT_SHADER 0\n" + mSource).toUtf8();
        tempStr = (char *)(shaderSource.cstr());
        glShaderSource(vertexShader, 1, &tempStr, 0);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (! success)
        {
            glGetShaderInfoLog(vertexShader, 2048, 0, errorsBuffer);
            mErrors += String("Vertex shader error: ") + errorsBuffer + "\n";
        }
        shaders.pushBack(vertexShader);

        u32 pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
        shaderSource = ("#version 440 core\n#define COMPILING_VERTEX_SHADER 0\n#define COMPILING_FRAGMENT_SHADER 1\n" + mSource).toUtf8();
        tempStr = (char *)(shaderSource.cstr());
        glShaderSource(pixelShader, 1, &tempStr, 0);
        glCompileShader(pixelShader);
        glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
        if (! success)
        {
            glGetShaderInfoLog(pixelShader, 2048, 0, errorsBuffer);
            mErrors += String("Pixel shader error: ") + errorsBuffer + "\n";
        }
        shaders.pushBack(pixelShader);

        if (mErrors.isNotEmpty())
        {
            for (auto shader : shaders)
            {
                glDeleteShader(shader);
            }

            return false;
        }

        mProgram = glCreateProgram();
        for (auto shader : shaders)
        {
            glAttachShader(mProgram, shader);
        }
        glLinkProgram(mProgram);

        glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
        if (! success)
        {
            glGetProgramInfoLog(mProgram, 2048, 0, errorsBuffer);
            mErrors += String("Shader link error: ") + errorsBuffer + "\n";
            glDeleteProgram(mProgram);
            mProgram = 0;
        }

        for (auto shader : shaders)
        {
            glDeleteShader(shader);
        }

        return mErrors.isEmpty();
    }

    void OpenGLShader::destroy()
    {
        if (mProgram)
        {
            glDeleteProgram(mProgram);
            mProgram = 0;
        }
    }

    bool OpenGLShader::set(const String& _name, const bool& _value)
    {
        return set(_name, int(_value));
    }

    bool OpenGLShader::set(const String& _name, const int& _value)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniform1i(mProgram, location, _value);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const f32& _value)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniform1f(mProgram, location, _value);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const f32& _valueX, const f32& _valueY)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniform2f(mProgram, location, _valueX, _valueY);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const Vector2& _value)
    {
        return set(_name, _value.x, _value.y);
    }

    bool OpenGLShader::set(const String& _name, const f32& _valueX, const f32& _valueY, const f32& _valueZ)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniform3f(mProgram, location, _valueX, _valueY, _valueZ);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const Vector3& _value)
    {
        return set(_name, _value.x, _value.y, _value.z);
    }

    bool OpenGLShader::set(const String& _name, const f32& _valueX, const f32& _valueY, const f32& _valueZ, const f32& _valueW)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniform4f(mProgram, location, _valueX, _valueY, _valueZ, _valueW);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const Vector4& _value)
    {
        return set(_name, _value.x, _value.y, _value.z, _value.w);
    }

    bool OpenGLShader::set(const String& _name, const Matrix3& _value)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniformMatrix3fv(mProgram, location, 1, false, (float*)&_value);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const Matrix& _value)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            glProgramUniformMatrix4fv(mProgram, location, 1, false, (float*)&_value);
            return true;
        }

        return false;
    }

    bool OpenGLShader::set(const String& _name, const Texture* _value)
    {
        int location = getUniformLocation(_name);
        if (location != -1)
        {
            if (_value != nullptr)
            {
                mTextures[_name] = _value;
		        return set(_name, int(mTextures.indexOfKey(_name)));
            }
            else
            {
                return set(_name, 0);
            }
        }

        return false;
    }

    FORCE_INLINE int OpenGLShader::getUniformLocation(const String& _name) const
    {
        if (mProgram)
        {
            String8 name = _name.toUtf8();
            return glGetUniformLocation(mProgram, name.cstr());
        }

        return -1;
    }
}
