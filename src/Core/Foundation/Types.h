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

#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__

#include <ostream>
#include "Core/Defines.h"

namespace Michka
{
    class BoundingSphere;
    class BoundingBox;
    class Matrix;
    class Matrix3;
    class Plane;
    class Quaternion;
    class Ray;
    class Variant;
    class Vector2;
    class Vector3;
    class Vector4;
    struct VertexAttribute;
    class VertexDeclaration;
    template<typename T>
    class List;
    template<typename T>
    class Vector;

    std::ostream& operator << (std::ostream& _out, const String8& _value);
    std::ostream& operator << (std::ostream& _out, const String& _value);
    std::ostream& operator << (std::ostream& _out, const String32& _value);
    std::ostream& operator << (std::ostream& _out, const Vector2& _value);
    std::ostream& operator << (std::ostream& _out, const Vector3& _value);
    std::ostream& operator << (std::ostream& _out, const Vector4& _value);
    std::ostream& operator << (std::ostream& _out, const Quaternion& _value);
    std::ostream& operator << (std::ostream& _out, const Matrix3& _value);
    std::ostream& operator << (std::ostream& _out, const Matrix& _value);
    std::ostream& operator << (std::ostream& _out, const BoundingSphere& _value);
    std::ostream& operator << (std::ostream& _out, const BoundingBox& _value);
    std::ostream& operator << (std::ostream& _out, const Plane& _value);
    std::ostream& operator << (std::ostream& _out, const Ray& _value);
    std::ostream& operator << (std::ostream& _out, const Variant& _value);
    std::ostream& operator << (std::ostream& _out, const VertexAttribute& _value);
    std::ostream& operator << (std::ostream& _out, const VertexDeclaration& _value);
    template<typename T>
    std::ostream& operator << (std::ostream& _out, const List<T>& _value);
    template<typename T>
    std::ostream& operator << (std::ostream& _out, const Vector<T>& _value);
};

#include "Types.inl"

#endif // __STD_TYPES_H__
