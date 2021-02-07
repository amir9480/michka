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
#include "Core/Foundation/File.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Graphics/Graphics.h"

TEST(TextureTest, Filter)
{
    Michka::String filesPath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/";

    std::shared_ptr<Michka::Window> window(new Michka::Window);
    Michka::Device* device = Michka::Device::instance();
    device->setWindow(window.get());
    Michka::VertexDeclaration vbd = Michka::VertexDeclaration::begin()
        .float32(3, Michka::VertexAttribute::Name::position)
        .float32(2, Michka::VertexAttribute::Name::texcoord0)
    .end();
    struct VertexStruct
    {
        Michka::Vector3 pos;
        Michka::Vector2 uv;
    };
    VertexStruct vertices[] = {
        {Michka::Vector3(-1.0f, 0.0f, 0.0f), Michka::Vector2(0.0f, 0.0f)},
        {Michka::Vector3( 1.0f, 0.0f, 0.0f), Michka::Vector2(0.0f, 1.0f)},
        {Michka::Vector3(-1.0f, 0.0f, 1.0f), Michka::Vector2(1.0f, 0.0f)},
        {Michka::Vector3( 1.0f, 0.0f, 1.0f), Michka::Vector2(1.0f, 1.0f)}
    };
    u32 indices[] = {0, 1, 2, 2, 1, 3};
    std::shared_ptr<Michka::VertexBuffer> vb(device->createVertexBuffer(&vbd)->set(&vertices, sizeof(vertices)));
    std::shared_ptr<Michka::IndexBuffer> ib(device->createIndexBuffer(&vbd)->set(indices, sizeof(indices)/sizeof(indices[0])));
    std::shared_ptr<Michka::Texture> db(device->createTexture(640, 480, Michka::TextureFormat::depth32, true));
    std::shared_ptr<Michka::Texture> rt(device->createTexture(640, 480, Michka::TextureFormat::r8g8b8, true));
    std::shared_ptr<Michka::Texture> texture(device->createTexture(Michka::Image(filesPath + "/Textures/grass.jpg")));
    std::shared_ptr<Michka::Shader> shader(device->createShader(Michka::File::getContents(filesPath + "Shaders/TextureFilter.glsl")));
    shader->set(
        "wvp",
        Michka::Matrix::createScaleMatrix(Michka::Vector3(5.0f, 1.0f, 5.0f)) * Michka::Matrix::createViewMatrix(Michka::Vector3(0.0f, 1.0f, -1.0f), Michka::Vector3::forward, Michka::Vector3::up) * Michka::Matrix::createPerspectiveProjection()
    );

    ASSERT_FALSE(shader->hasErrors()) << shader->getErrors().toUtf8().cstr();

    device->setRenderTarget(0, rt.get());
    device->setDepthBuffer(db.get());
    device->setIndexBuffer(ib.get());
    device->setVertexBuffer(vb.get());
    shader->set("diffuse", texture.get());
    device->setShader(shader.get());

    texture->setFilter(Michka::Texture::Filter::default);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/linear.jpg"));

    texture->setFilter(Michka::Texture::Filter::none);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/none.jpg"));

    texture->setFilter(Michka::Texture::Filter::linear);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/linear.jpg"));

    texture->setFilter(Michka::Texture::Filter::trilinear);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/trilinear.jpg"));

    texture->setFilter(Michka::Texture::Filter::anisotropic2);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/anisotropic2.jpg"));

    texture->setFilter(Michka::Texture::Filter::anisotropic4);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/anisotropic4.jpg"));

    texture->setFilter(Michka::Texture::Filter::anisotropic8);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/anisotropic8.jpg"));

    texture->setFilter(Michka::Texture::Filter::anisotropic16);
    device->clear(true, true, true, Michka::Color::black);
    device->draw();
    ASSERT_EQ(rt->get(), Michka::Image(filesPath + "Images/TextureFilter/anisotropic16.jpg"));
}
