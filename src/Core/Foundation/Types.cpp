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

#include "Michka/Core/Foundation/Types.h"
#include "Michka/Core/Container/Color.h"
#include "Michka/Core/Container/String.h"
#include "Michka/Core/Container/Variant.h"
#include "Michka/Core/Math/BoundingBox.h"
#include "Michka/Core/Math/BoundingSphere.h"
#include "Michka/Core/Math/Matrix3.h"
#include "Michka/Core/Math/Matrix.h"
#include "Michka/Core/Math/Plane.h"
#include "Michka/Core/Math/Quaternion.h"
#include "Michka/Core/Math/Ray.h"
#include "Michka/Core/Math/Vector2.h"
#include "Michka/Core/Math/Vector3.h"
#include "Michka/Core/Math/Vector4.h"
#include "Michka/Graphics/VertexDeclaration.h"

namespace Michka
{
    std::ostream& operator << (std::ostream& _out, const String8& _value)
    {
        return _out << _value.cstr();
    }

    std::ostream& operator << (std::ostream& _out, const String& _value)
    {
        return _out << _value.toUtf8().cstr();
    }

    std::ostream& operator << (std::ostream& _out, const String32& _value)
    {
        return _out << _value.toUtf8().cstr();
    }

    std::ostream& operator << (std::ostream& _out, const Vector2& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Vector3& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Vector4& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Color& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Quaternion& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Matrix3& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Matrix& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const BoundingSphere& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const BoundingBox& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Plane& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Ray& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const Variant& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const VertexAttribute& _value)
    {
        return _out << _value.toString();
    }

    std::ostream& operator << (std::ostream& _out, const VertexDeclaration& _value)
    {
        return _out << _value.toString();
    }
}
