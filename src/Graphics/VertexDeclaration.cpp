#include "VertexDeclaration.h"
#include "Core/Container/String.h"

namespace Michka
{
    String VertexAttribute::toString() const
    {
        String vertexAttributeNames[] = {"position", "normal", "tangent", "binormal", "blendIndices", "blendWeight", "color0", "color1", "color2", "color3", "texcoord0", "texcoord1", "texcoord2", "texcoord3", "texcoord4", "texcoord5", "texcoord6", "texcoord7"};
        String vertexAttributeTypes[] = {"float32", "int16", "int32"};
        return "VertexAttribute(name=" + vertexAttributeNames[(int)name] + ",type=" + vertexAttributeTypes[(int)type] + ",elements=" + String::number(elements) + ")";
    }

    VertexDeclaration VertexDeclaration::begin()
    {
        return VertexDeclaration();
    }

    VertexDeclaration& VertexDeclaration::end()
    {
        return *this;
    }

    VertexDeclaration& VertexDeclaration::float32(const u8& _elements, const VertexAttribute::Name& _name)
    {
        mAttributes.pushBack({_name, VertexAttribute::Type::float32, _elements});
        return *this;
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
        return "VertexDeclaration(\n    " + mAttributes.implode(",\n    ") + "\n)";
    }
}
