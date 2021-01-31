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

#include "Core/Thread/Thread.h"
#include "Core/Thread/Mutex.h"
#include "Core/Foundation/File.h"
#include "Core/Foundation/Log.h"
#include "Graphics/Device.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexBuffer.h"
#include "OpenGLHeaders.h"

namespace Michka
{
    const char quadShaderSource[] =
        "#if COMPILING_VERTEX_SHADER\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "	 TexCoord = aTexCoord;\n"
        "}\n"
        "#endif // COMPILING_VERTEX_SHADER\n"
        "\n"
        "#if COMPILING_FRAGMENT_SHADER\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D image;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture(image, TexCoord);\n"
        "}\n"
        "#endif // COMPILING_FRAGMENT_SHADER\n";

    Device::Device()
    {
        if (!gladLoadGL())
        {
            MICHKA_ABORT("Failed to load GLAD.");
        }

        glGenVertexArrays(1, &mVertexArray);
        glBindVertexArray(mVertexArray);
        glGenFramebuffers(1, &mFrameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);

        static auto quadVertexDecl = VertexDeclaration::begin()
            .float32(3, VertexAttribute::Name::position)
            .float32(2, VertexAttribute::Name::texcoord0)
        .end();

        f32 quadVertices[] = {
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };
        u32 quadIndices[] = {0, 1, 2, 2, 1, 3};

        mQuadVertexBuffer = this->createVertexBuffer(&quadVertexDecl);
        mQuadVertexBuffer->set(quadVertices, sizeof(quadVertices));
        mQuadIndexBuffer = this->createIndexBuffer();
        mQuadIndexBuffer->set(quadIndices, sizeof(quadIndices) / sizeof(quadIndices[0]));
        mQuadShader = this->createShader(quadShaderSource);
        if (mQuadShader->hasErrors())
        {
            MICHKA_ABORT(mQuadShader->getErrors().toUtf8().cstr());
        }
    }

    Device::~Device()
    {
        delete mQuadShader;
        delete mQuadVertexBuffer;
        delete mQuadIndexBuffer;
        glDeleteVertexArrays(1, &mVertexArray);
        glDeleteFramebuffers(1, &mFrameBuffer);
    }

    void Device::clear(const bool& _backBuffer, const bool& _depthBuffer, const bool& _stencil, const Color& _backBufferValue, const f32& _depthValue, const u8& _stencilValue)
    {
        glClearColor(_backBufferValue.r/255.0f, _backBufferValue.g/255.0f, _backBufferValue.b/255.0f, _backBufferValue.a/255.0f);
        glClearDepth(_depthValue);
        glClearStencil(_stencilValue);
        glClear(
            (_backBuffer ? GL_COLOR_BUFFER_BIT : 0) |
            (_depthBuffer ? GL_DEPTH_BUFFER_BIT : 0) |
            (_stencil ? GL_STENCIL_BUFFER_BIT : 0)
        );
    }

    IndexBuffer* Device::createIndexBuffer(const bool& _static)
    {
        IndexBuffer* out = new IndexBuffer;
        out->mStatic = _static;
        return out;
    }

    Shader* Device::createShader(const String& _source)
    {
        Shader* out = new Shader;
        if (_source.isNotEmpty())
        {
            out->compile(_source);
        }

        return out;
    }

    Texture* Device::createTexture(const u32& _width, const u32& _height, const TextureFormat& _format, const bool& _renderTarget)
    {
        Texture* output = new Texture();
        output->mWidth = _width;
        output->mHeight = _height;
        output->mFormat = _format;
        output->mRenderTarget = _renderTarget;
        glGenTextures(1, &output->mTexture);
        if (_renderTarget)
        {
            output->set(nullptr, 0);
        }

        return output;
    }

    VertexBuffer* Device::createVertexBuffer(VertexDeclaration* _vertexDeclaration, const bool& _static)
    {
        VertexBuffer* out = new VertexBuffer;
        out->mStatic = _static;
        out->mVertexDeclaration = _vertexDeclaration;
        return out;
    }

    void Device::draw()
    {
        if (mCurrentIndexBuffer && mCurrentShader)
        {
            Shader* shader = dynamic_cast<Shader*>(mCurrentShader);
            IndexBuffer* indexBuffer = dynamic_cast<IndexBuffer*>(mCurrentIndexBuffer);

            for (u32 i = 0; i < shader->mTextures.getSize(); i++)
            {
                const Texture* texture = dynamic_cast<const Texture*>(shader->mTextures.at(i).second);
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, texture->mTexture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            glActiveTexture(GL_TEXTURE0);
            u32 attachments[32];
            u8 renderTargetCount = mRenderTargets.getSize() < 32 ? mRenderTargets.getSize() : 32;
            for (u8 i = 0; i < renderTargetCount; i++)
            {
                attachments[i] = GL_COLOR_ATTACHMENT0 + i;
            }
            glDrawBuffers(renderTargetCount, attachments);

            GLenum errorCode;
            if ((errorCode = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
            {
                static Map<GLenum, String> errorMessages =
                {
                    {GL_FRAMEBUFFER_UNDEFINED,                     "GL_FRAMEBUFFER_UNDEFINED"},
                    {GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,         "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"},
                    {GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"},
                    {GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,        "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"},
                    {GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,        "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"},
                    {GL_FRAMEBUFFER_UNSUPPORTED,                   "GL_FRAMEBUFFER_UNSUPPORTED"},
                    {GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,        "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"},
                    {GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,        "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"},
                    {GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,      "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"},
                };
                String errorMessage = "Framebuffer is not completed.";
                if (errorMessages.hasKey(errorCode))
                {
                    errorMessage += errorMessages[errorCode];
                }
                MICHKA_ERROR(errorMessage.toUtf8().cstr());
                return;
            }

            if (renderTargetCount > 0)
            {
	            glViewport(0, 0, mRenderTargets[0]->getWidth(), mRenderTargets[0]->getHeight());
            }
            glDrawElements(GL_TRIANGLES, indexBuffer->mCount, GL_UNSIGNED_INT, 0);
        }
    }

    void Device::drawOnScreen(const Texture* _texture)
    {
        if (mWindow)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            drawQuad(_texture, 0, 0, mWindow->getWidth(), mWindow->getHeight());
            glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
            mWindow->draw();
        }
    }

    void Device::drawQuad(const Texture* _texture, const u32& _x, const u32& _y, const u32& _width, const u32& _height)
    {
        mQuadShader->set("image", _texture);
        setShader(mQuadShader);
        setVertexBuffer(mQuadVertexBuffer);
        setIndexBuffer(mQuadIndexBuffer);
        IndexBuffer* indexBuffer = dynamic_cast<IndexBuffer*>(mCurrentIndexBuffer);
        Shader* shader = dynamic_cast<Shader*>(mCurrentShader);
        for (u32 i = 0; i < shader->mTextures.getSize(); i++)
        {
            const Texture* texture = dynamic_cast<const Texture*>(shader->mTextures.at(i).second);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, texture->mTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        u32 width = _width > 0 ? _width : _texture->getWidth();
        u32 height = _height > 0 ? _height : _texture->getHeight();
        glViewport(_x, _y, width, height);
        clear(true, true, true, Color(0, 0, 0, 255));
        glDrawElements(GL_TRIANGLES, indexBuffer->mCount, GL_UNSIGNED_INT, 0);
        setShader(nullptr);
        setVertexBuffer(nullptr);
        setIndexBuffer(nullptr);
    }

    bool Device::setDepthBuffer(const Texture* _depthBuffer)
    {
        if (_depthBuffer == nullptr)
        {
            mDepthBuffer = nullptr;
        }
        else
        {
            if (_depthBuffer->isRenderTarget() == false)
            {
                MICHKA_ERROR("Depth buffer texture is not a render target.");
                return false;
            }
            if (_depthBuffer->getFormat() != TextureFormat::depth32)
            {
                MICHKA_ERROR("Depth buffer texture format is not a depth format.");
                return false;
            }
            mDepthBuffer = _depthBuffer;
            const Texture* depthBuffer = dynamic_cast<const Texture*>(_depthBuffer);
            GLint currentTextureId;
            glGetIntegerv(GL_TEXTURE_2D, &currentTextureId);

			glBindTexture(GL_TEXTURE_2D, depthBuffer->mTexture);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->mTexture, 0);

            glBindTexture(GL_TEXTURE_2D, currentTextureId);
        }

        return true;
    }

    void Device::setIndexBuffer(IndexBuffer* _indexBuffer)
    {
        if (_indexBuffer)
        {
            IndexBuffer* indexBuffer = dynamic_cast<IndexBuffer*>(_indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->mIndexBuffer);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        mCurrentIndexBuffer = _indexBuffer;
    }

    bool Device::setRenderTarget(const u8& _index, const Texture* _renderTarget)
    {
        if (_renderTarget == nullptr && mRenderTargets.hasKey(_index))
        {
            mRenderTargets.remove(_index);
        }
        else
        {
            if (_renderTarget->isRenderTarget() == false)
            {
                MICHKA_ERROR("Texture is not a render target.");
                return false;
            }
            const Texture* renderTarget = dynamic_cast<const Texture*>(_renderTarget);
            mRenderTargets[_index] = _renderTarget;
            GLint currentTextureId;
            glGetIntegerv(GL_TEXTURE_2D, &currentTextureId);

			glBindTexture(GL_TEXTURE_2D, renderTarget->mTexture);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _index, GL_TEXTURE_2D, renderTarget->mTexture, 0);

            glBindTexture(GL_TEXTURE_2D, currentTextureId);
        }

        return true;
    }

    void Device::setShader(Shader* _shader)
    {
        if (_shader)
        {
            Shader* shader = dynamic_cast<Shader*>(_shader);
            glUseProgram(shader->mProgram);
        }
        else
        {
            glUseProgram(0);
        }
        mCurrentShader = _shader;
    }

    void Device::setVertexBuffer(VertexBuffer* _vertexBuffer)
    {
        if (_vertexBuffer)
        {
            VertexBuffer* vertexBuffer = dynamic_cast<VertexBuffer*>(_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->mVertexBuffer);
            auto vertexAttributes = vertexBuffer->mVertexDeclaration->getAttributes();
            u64 offset = 0;
            int glTypes[] = {GL_FLOAT, GL_SHORT, GL_INT};
            for (u32 i = 0; i < vertexAttributes.getSize(); i++)
            {
                auto vertexAttribute = vertexAttributes[i];
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, vertexAttribute.elements, glTypes[(u32)vertexAttribute.type], GL_FALSE, vertexBuffer->mVertexDeclaration->getStride(), (void*)offset);
                offset += vertexAttribute.getSize();
            }
            glEnableVertexAttribArray(0);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        mCurrentVertexBuffer = _vertexBuffer;
    }
}
