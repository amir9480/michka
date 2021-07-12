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

#include "Variant.h"
#include "Core/Math/Utility.h"

namespace Michka
{
    namespace Private
    {
        CustomVariantBase::~CustomVariantBase()
        {
            //
        }

        bool CustomVariantBase::equal(CustomVariantBase* _other)
        {                 // @NOCOVERAGE
            return false; // @NOCOVERAGE
        }

        String CustomVariantBase::toString() const
        {                             // @NOCOVERAGE
            return String("Unknown"); // @NOCOVERAGE
        }
    }

    String Variant::toString() const
    {
        switch (mType)
        {
            case Type::typeNull:
                return String("null");
            case Type::typeBool:
                return mInt == 0 ? String("false") : String("true");
            case Type::typeInt:
                return String::number(mInt);
            case Type::typeFloat:
                return String::number(mFloat);
            case Type::typeString:
                return *mString;
            case Type::typeArray:
                return "{" + mList->join(",") + "}";
            case Type::typeCustom:
            case Type::typeReference:
                return mCustom->toString();
        };
        return String("Unknown"); // @NOCOVERAGE
    }

    bool Variant::operator == (const Variant& _other) const
    {
        switch (mType)
        {
            case Type::typeNull:
                return _other.mType == Type::typeNull;
            case Type::typeBool:
                return _other.mType == Type::typeBool && mInt == _other.mInt;
            case Type::typeInt:
                return _other.mType == Type::typeInt && mInt == _other.mInt;
            case Type::typeFloat:
                return _other.mType == Type::typeFloat && Math::equals(mFloat, _other.mFloat);
            case Type::typeString:
                return _other.mType == Type::typeString && *mString == *_other.mString;
            case Type::typeArray:
                return _other.mType == Type::typeArray && *mList == *_other.mList;
            case Type::typeCustom:
                return _other.mType == Type::typeCustom && mCustom->getType() == _other.mCustom->getType() && mCustom->equal(_other.mCustom);
            case Type::typeReference:
                return _other.mType == Type::typeReference && mCustom->getType() == _other.mCustom->getType() && mCustom->equal(_other.mCustom);
        };

        return false; // @NOCOVERAGE
    }
}
