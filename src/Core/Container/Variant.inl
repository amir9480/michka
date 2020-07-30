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

#include "Variant.h"
#include "Core/Reflection/Type.h"

namespace Michka
{
    FORCE_INLINE Variant::Variant() :
        mType(Variant::Type::typeNull),
        mInt(0)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const std::nullptr_t& _val)  :
        mType(Variant::Type::typeNull),
        mInt(0)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const int& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned int& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const float& _val) :
        mType(Variant::Type::typeFloat),
        mFloat(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const double& _val) :
        mType(Variant::Type::typeFloat),
        mFloat(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const bool& _val) :
        mType(Variant::Type::typeBool),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const short int& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned short int& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const long long int& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned long long int& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned char& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const wchar_t& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char16_t& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char32_t& _val) :
        mType(Variant::Type::typeInt),
        mInt(_val)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char* _val) :
        mType(Variant::Type::typeString)
    {
        mString = new String(_val);
    }

    FORCE_INLINE Variant::Variant(const wchar_t* _val) :
        mType(Variant::Type::typeString)
    {
        mString = new String(_val);
    }

    FORCE_INLINE Variant::Variant(const char32_t* _val)  :
        mType(Variant::Type::typeString)
    {
        mString = new String(_val);
    }

    FORCE_INLINE Variant::Variant(const String& _val) :
        mType(Variant::Type::typeString)
    {
        mString = new String(_val);
    }

    FORCE_INLINE Variant::Variant(const Variant& _val) :
        mType(Variant::Type::typeNull)
    {
        *this = _val;
    }

    FORCE_INLINE  Variant::~Variant()
    {
        destroy();
    }

    FORCE_INLINE Variant& Variant::destroy()
    {
        switch (mType)
        {
            case Type::typeString:
                delete mString;
                break;
            case Type::typeArray:
                delete mList;
                break;
            case Type::typeCustom:
                delete mCustom;
                break;
        }
        mInt = 0;
        mType = Variant::Type::typeNull;
        return *this;
    }

    FORCE_INLINE Variant::Type Variant::getType() const
    {
        return mType;
    }

    template<typename T>
    T Variant::to() const
    {
        switch (mType)
        {
            case Type::typeNull:
                if constexpr (Michka::Type<T>::isNumeric)
                {
                    return (T)0;
                }
                break;
            case Type::typeBool:
            case Type::typeInt:
                if constexpr (Michka::Type<T>::isNumeric)
                {
                    return (T)mInt;
                }
                break;
            case Type::typeFloat:
                if constexpr (Michka::Type<T>::isNumeric)
                {
                    return (T)mFloat;
                }
                break;
            case Type::typeString:
                if constexpr (Michka::Type<T>::isNumeric)
                {
                    return mString->toNumber<T>();
                }
                if constexpr (Michka::Type<T>::is<String>())
                {
                    return *mString;
                }
                if constexpr (Michka::Type<T>::is<String8>())
                {
                    return mString->toUtf8();
                }
                if constexpr (Michka::Type<T>::is<String32>())
                {
                    return mString->toUtf32();
                }
                if constexpr (Michka::Type<T>::is<wchar_t*>())
                {
                    return mString->cstr();
                }
                break;
        };

        return T();
    }

    FORCE_INLINE Variant& Variant::operator = (const std::nullptr_t& _val)
    {
        destroy();
        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const int& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned int& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const float& _val)
    {
        destroy();
        mType = Type::typeFloat;
        mFloat = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const double& _val)
    {
        destroy();
        mType = Type::typeFloat;
        mFloat = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const bool& _val)
    {
        destroy();
        mType = Type::typeBool;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const short int& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned short int& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const long long int& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned long long int& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned char& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const wchar_t& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char16_t& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char32_t& _val)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _val;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char* _val)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_val);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const wchar_t* _val)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_val);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char32_t* _val)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_val);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const String& _val)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_val);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const Variant& _val)
    {
        destroy();
        mType = _val.mType;
        switch (mType)
        {
            case Type::typeNull:
                break;
            case Type::typeBool:
            case Type::typeInt:
                mInt = _val.mInt;
                break;
            case Type::typeFloat:
                mFloat = _val.mFloat;
                break;
            case Type::typeString:
                mString = new String(*_val.mString);
                break;
        };

        return *this;
    }
}
