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

#ifndef __VERTEX_DECLARATION_H__
#define __VERTEX_DECLARATION_H__

#include "Core/Helpers.h"
#include "Core/Container/Vector.h"

namespace Michka
{
    struct VertexAttribute
    {
        MICHKA_STRUCT();

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

        /**
         * @brief Get the size of attribute in bytes.
         */
        u8 getSize() const;

        String toString() const;

        Name name;
        Type type;
        u8 elements = 1;
    };

    class VertexDeclaration
    {
        MICHKA_CLASS();
    public:
        /**
         * @brief Begin declaration.
         */
        static VertexDeclaration begin();

        /**
         * @brief End of declaration.
         */
        VertexDeclaration& end();

        /**
         * @brief Add 32-bit float point number to layout.
         *
         * @param _elements number of elements
         * @param _name name of vertex part
         */
        VertexDeclaration& float32(const u8& _elements, const VertexAttribute::Name& _name);

        /**
         * @brief Get the vertex declaration attributes.
         */
        const Vector<VertexAttribute>& getAttributes() const;

        /**
         * @brief Get vertex declaration
         *
         * @return u64 const
         */
        u64 getHash() const;

        /**
         * @brief Get the Stride size in bytes.
         */
        u8 getStride() const;

        /**
         * @brief Add 16-bit integer number to layout.
         *
         * @param _elements number of elements
         * @param _name name of vertex part
         */
        VertexDeclaration& int16(const u8& _elements, const VertexAttribute::Name& _name);

        /**
         * @brief Add 32-bit integer number to layout.
         *
         * @param _elements number of elements
         * @param _name name of vertex part
         */
        VertexDeclaration& int32(const u8& _elements, const VertexAttribute::Name& _name);

        /**
         * @brief Show as string.
         */
        String toString() const;

    protected:
        VertexDeclaration();

    protected:
        Vector<VertexAttribute> mAttributes;
        u64 mHash = 0;
        u8 mStride = 0;
    };
}

#endif // __VERTEX_DECLARATION_H__
