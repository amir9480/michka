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

#include "OpenGLShader.h"

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

    bool OpenGLShader::compile()
    {
        char* tempStr = nullptr;
        int success = 0;
        char errorsBuffer[2048];
        Map<Shader::Type, u32> shaders;
        Map<Shader::Type, String8> shaderSources;
        for (auto shaderSource : mShadersSources)
        {
            shaderSources[shaderSource.key()] = shaderSource.value().toUtf8();
        }

        if (shaderSources.hasKey(Shader::Type::vertex))
        {
            u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
            tempStr = (char *)(shaderSources[Shader::Type::vertex].cstr());
            glShaderSource(vertexShader, 1, &tempStr, 0);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (! success)
            {
                glGetShaderInfoLog(vertexShader, 2048, 0, errorsBuffer);
                mErrors += String("Vertex shader error: ") + errorsBuffer + "\n";
            }
            shaders[Shader::Type::vertex] = vertexShader;
        }

        if (shaderSources.hasKey(Shader::Type::pixel))
        {
            u32 pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
            tempStr = (char *)shaderSources[Shader::Type::pixel].cstr();
            glShaderSource(pixelShader, 1, &tempStr, 0);
            glCompileShader(pixelShader);
            glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
            if (! success)
            {
                glGetShaderInfoLog(pixelShader, 2048, 0, errorsBuffer);
                mErrors += String("Pixel shader error: ") + errorsBuffer + "\n";
            }
            shaders[Shader::Type::pixel] = pixelShader;
        }

        if (mErrors.isNotEmpty())
        {
            for (auto shader : shaders)
            {
                glDeleteShader(shader.value());
            }
            return false;
        }

        mProgram = glCreateProgram();
        for (auto shader : shaders)
        {
            glAttachShader(mProgram, shader.value());
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
            glDeleteShader(shader.value());
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

    void OpenGLShader::setPixelShader(const String& _source)
    {
        mShadersSources[Shader::Type::pixel] = _source;
    }

    void OpenGLShader::setVertexShader(const String& _source)
    {
        mShadersSources[Shader::Type::vertex] = _source;
    }
}
