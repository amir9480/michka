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

#include <gtest/gtest.h>
#include <memory>
#include "MichkaTests.h"
#include "Michka/Core/Foundation/File.h"
#include "Michka/Core/Math/Vector3.h"
#include "Michka/Graphics/Graphics.h"

TEST(GraphicsTest, HelloTriangle)
{
    Michka::String filesPath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/";

    std::shared_ptr<Michka::Window> window(new Michka::Window);
    Michka::Device* device = Michka::Device::instance();
    device->setWindow(window.get());
    Michka::VertexDeclaration vbd = Michka::VertexDeclaration::begin()
        .float32(3, Michka::VertexAttribute::Name::position)
        .float32(3, Michka::VertexAttribute::Name::color0)
    .end();
    Michka::Vector3 vertices[] = {
        Michka::Vector3(1.0f, -1.0f, 0.5f),  Michka::Vector3(1.0f, 0.0f, 0.0f),
        Michka::Vector3(0.0f, 1.0f, 0.5f),   Michka::Vector3(0.0f, 1.0f, 0.0f),
        Michka::Vector3(-1.0f, -1.0f, 0.5f), Michka::Vector3(0.0f, 0.0f, 1.0f)
    };
    u32 indices[] = {0, 1, 2};
    std::shared_ptr<Michka::VertexBuffer> vb(device->createVertexBuffer(&vbd)->set(&vertices, sizeof(vertices)));
    std::shared_ptr<Michka::IndexBuffer> ib(device->createIndexBuffer(&vbd)->set(indices, sizeof(indices)/sizeof(indices[0])));
    std::shared_ptr<Michka::Texture> db(device->createTexture(640, 480, Michka::TextureFormat::depth32, true));
    std::shared_ptr<Michka::Texture> rt(device->createTexture(640, 480, Michka::TextureFormat::r8g8b8, true));
    std::shared_ptr<Michka::Shader> shader(device->createShader(Michka::File::getContents(filesPath + "Shaders/HelloTriangle.glsl")));

    ASSERT_FALSE(shader->hasErrors()) << shader->getErrors().toUtf8().cstr();

    device->setRenderTarget(0, rt.get());
    device->setDepthBuffer(db.get());
    device->clear(true, true, true, Michka::Color::black);
    device->setIndexBuffer(ib.get());
    device->setVertexBuffer(vb.get());
    device->setShader(shader.get());
    device->draw();

    ASSERT_EQ(device->getWindow(), window.get());
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/hello_triangle.jpg"));
}
