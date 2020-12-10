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

#include <gtest/gtest.h>
#include <sstream>
#include "Core/Core.h"
#include "Graphics/Graphics.h"

TEST(TypesTest, Ostream)
{
    std::stringstream s;

    s << Michka::String("Hello World");
    ASSERT_EQ(s.str(), "Hello World");
    s.str("");

    s << Michka::String8("Hello World");
    ASSERT_EQ(s.str(), "Hello World");
    s.str("");

    s << Michka::String32("Hello World");
    ASSERT_EQ(s.str(), "Hello World");
    s.str("");

    s << Michka::Vector2(1.5f, 2.0f);
    ASSERT_EQ(s.str(), "Vector2(1.5, 2)");
    s.str("");

    s << Michka::Vector3(1.5f, 2.0f, 3.0f);
    ASSERT_EQ(s.str(), "Vector3(1.5, 2, 3)");
    s.str("");

    s << Michka::Vector4(1.5f, 2.0f, 3.0f);
    ASSERT_EQ(s.str(), "Vector4(1.5, 2, 3, 1)");
    s.str("");

    s << Michka::Color(255, 0, 0, 255);
    ASSERT_EQ(s.str(), "Color(255, 0, 0, 255)");
    s.str("");

    s << Michka::Quaternion(1.5f, 2.0f, 3.0f, 1.0f);
    ASSERT_EQ(s.str(), "Quaternion(1.5, 2, 3, 1)");
    s.str("");

    s << Michka::Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    ASSERT_EQ(s.str(), "Matrix3(\n1, 2, 3,\n4, 5, 6,\n7, 8, 9\n)");
    s.str("");

    s << Michka::Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    ASSERT_EQ(s.str(), "Matrix(\n1, 2, 3, 4,\n5, 6, 7, 8,\n9, 10, 11, 12,\n13, 14, 15, 16\n)");
    s.str("");

    s << Michka::BoundingBox(Michka::Vector3::zero, Michka::Vector3::one);
    ASSERT_EQ(s.str(), "BoundingBox(min=Vector3(0, 0, 0), max=Vector3(1, 1, 1))");
    s.str("");

    s << Michka::BoundingSphere(Michka::Vector3::zero, 2.5f);
    ASSERT_EQ(s.str(), "BoundingSphere(position=Vector3(0, 0, 0), radius=2.5)");
    s.str("");

    s << Michka::Plane(1.5f, 2.0f, 3.0f, 1.0f);
    ASSERT_EQ(s.str(), "Plane(1.5, 2, 3, 1)");
    s.str("");

    s << Michka::Ray(Michka::Vector3::one, Michka::Vector3::forward);
    ASSERT_EQ(s.str(), "Ray(position=Vector3(1, 1, 1), direction=Vector3(0, 0, 1))");
    s.str("");

    s << Michka::Variant();
    ASSERT_EQ(s.str(), "null");
    s.str("");

    s << Michka::Variant(14);
    ASSERT_EQ(s.str(), "14");
    s.str("");

    s << Michka::Vector<int>();
    ASSERT_EQ(s.str(), "Vector(size=0)");
    s.str("");

    s << Michka::List<int>();
    ASSERT_EQ(s.str(), "List(size=0)");
    s.str("");

    s << Michka::Vector({1,2,4});
    ASSERT_EQ(s.str(), "Vector{1,2,4}");
    s.str("");

    s << Michka::List({1,2,4});
    ASSERT_EQ(s.str(), "List{1,2,4}");
    s.str("");

    s << Michka::VertexAttribute({Michka::VertexAttribute::Name::normal, Michka::VertexAttribute::Type::float32, 3});
    ASSERT_EQ(s.str(), "VertexAttribute(name=normal,type=float32,elements=3)");
    s.str("");

    s << Michka::VertexDeclaration::begin()
        .float32(3, Michka::VertexAttribute::Name::position)
        .float32(3, Michka::VertexAttribute::Name::normal)
        .float32(3, Michka::VertexAttribute::Name::binormal)
        .float32(3, Michka::VertexAttribute::Name::tangent)
        .float32(2, Michka::VertexAttribute::Name::texcoord0)
    .end();

    ASSERT_EQ(
        s.str(),
        "VertexDeclaration(\n"
        "    VertexAttribute(name=position,type=float32,elements=3),\n"
        "    VertexAttribute(name=normal,type=float32,elements=3),\n"
        "    VertexAttribute(name=binormal,type=float32,elements=3),\n"
        "    VertexAttribute(name=tangent,type=float32,elements=3),\n"
        "    VertexAttribute(name=texcoord0,type=float32,elements=2)\n"
        ")"
    );
}
