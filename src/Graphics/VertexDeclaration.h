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

#ifndef __VERTEX_DECLARATION_H__
#define __VERTEX_DECLARATION_H__

#include "Core/Defines.h"
#include "Core/Container/Vector.h"

namespace Michka
{
    struct VertexAttribute
    {
        enum class Name
        {
            position,
		    normal,
		    tangent,
		    binormal,
		    blendIndices,
		    blendWeight,
		    color0,
		    color1,
		    color2,
		    color3,
		    texcoord0,
		    texcoord1,
		    texcoord2,
		    texcoord3,
		    texcoord4,
		    texcoord5,
		    texcoord6,
		    texcoord7,
        };

        enum class Type
        {
            float32,
            int16,
            int32,
        };

        String toString() const;

        Name name;
        Type type;
        u8 elements = 1;
    };

    class VertexDeclaration
    {
    public:
        static VertexDeclaration begin();

        VertexDeclaration& end();

        VertexDeclaration& float32(const u8& _elements, const VertexAttribute::Name& _name);

        VertexDeclaration& int16(const u8& _elements, const VertexAttribute::Name& _name);

        VertexDeclaration& int32(const u8& _elements, const VertexAttribute::Name& _name);

        String toString() const;
    protected:
        Vector<VertexAttribute> mAttributes;
    };
}

#endif // __VERTEX_DECLARATION_H__
