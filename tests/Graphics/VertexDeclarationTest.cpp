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
#include "Core/Container/String.h"
#include "Graphics/VertexDeclaration.h"

TEST(VertexDeclarationTest, Create)
{
    auto dec =
        Michka::VertexDeclaration::begin()
            .float32(3, Michka::VertexAttribute::Name::position)
            .float32(3, Michka::VertexAttribute::Name::normal)
            .int16(3, Michka::VertexAttribute::Name::texcoord0)
            .int32(2, Michka::VertexAttribute::Name::texcoord1)
        .end();
    ASSERT_EQ(
        dec.toString(),
        "VertexDeclaration(\n"
        "    VertexAttribute(name=position,type=float32,elements=3),\n"
        "    VertexAttribute(name=normal,type=float32,elements=3),\n"
        "    VertexAttribute(name=texcoord0,type=int16,elements=3),\n"
        "    VertexAttribute(name=texcoord1,type=int32,elements=2)\n"
        ")"
    );
    ASSERT_EQ(dec.getHash(), 2634101685743308180);
    ASSERT_EQ(dec.getStride(), 38);
    ASSERT_EQ(dec.getAttributes()[0].name, Michka::VertexAttribute::Name::position);
    ASSERT_EQ(dec.getAttributes()[0].type, Michka::VertexAttribute::Type::float32);
    ASSERT_EQ(dec.getAttributes()[0].elements, 3);
}
