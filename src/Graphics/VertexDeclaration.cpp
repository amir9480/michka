#include "VertexDeclaration.h"
#include "Core/Container/String.h"
#include "Core/Container/Hash.h"

namespace Michka
{
    u8 VertexAttribute::getSize() const
    {
        switch (type)
        {
            case Type::float32: case Type::int32:
                return elements * 4;
            case Type::int16:
                return elements * 2;
        }

        return 0; // @NOCOVERAGE
    }

    String VertexAttribute::toString() const
    {
        String vertexAttributeNames[] = {"position", "normal", "tangent", "binormal", "blendIndices", "blendWeight", "color0", "color1", "color2", "color3", "texcoord0", "texcoord1", "texcoord2", "texcoord3", "texcoord4", "texcoord5", "texcoord6", "texcoord7"};
        String vertexAttributeTypes[] = {"float32", "int16", "int32"};
        return "VertexAttribute(name=" + vertexAttributeNames[(int)name] + ", type=" + vertexAttributeTypes[(int)type] + ", elements=" + String::number(elements) + ")";
    }

    VertexDeclaration VertexDeclaration::begin()
    {
        return VertexDeclaration();
    }

    VertexDeclaration& VertexDeclaration::end()
    {
        mHash = Hash::make(*this);
        for (auto attribute : mAttributes)
        {
            mStride += attribute.getSize();
        }

        return *this;
    }

    VertexDeclaration& VertexDeclaration::float32(const u8& _elements, const VertexAttribute::Name& _name)
    {
        mAttributes.pushBack({_name, VertexAttribute::Type::float32, _elements});
        return *this;
    }

    const Vector<VertexAttribute>& VertexDeclaration::getAttributes() const
    {
        return mAttributes;
    }

    u64 VertexDeclaration::getHash() const
    {
        return mHash;
    }

    u8 VertexDeclaration::getStride() const
    {
        return mStride;
    }

    VertexDeclaration& VertexDeclaration::int16(const u8& _elements, const VertexAttribute::Name& _name)
    {
        mAttributes.pushBack({_name, VertexAttribute::Type::int16, _elements});
        return *this;
    }

    VertexDeclaration& VertexDeclaration::int32(const u8& _elements, const VertexAttribute::Name& _name)
    {
        mAttributes.pushBack({_name, VertexAttribute::Type::int32, _elements});
        return *this;
    }

    String VertexDeclaration::toString() const
    {
        return "VertexDeclaration(\n    " + mAttributes.join(",\n    ") + "\n)";
    }

    VertexDeclaration::VertexDeclaration()
    {
        //
    }
}
