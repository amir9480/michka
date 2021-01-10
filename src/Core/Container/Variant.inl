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
#include "Core/Reflection/Type.h"

namespace Michka
{
    namespace Private
    {
        FORCE_INLINE CustomVariantBase::CustomVariantBase()
        {
            //
        }

        FORCE_INLINE String CustomVariantBase::getType() const
        {
            return mType;
        }

        template<typename T>
        CustomVariant<T>::CustomVariant(const T& _value)
        {
            mType = Type<T>::typeName;
            mData = new T(_value);
        }

        template<typename T>
        CustomVariant<T>::~CustomVariant()
        {
            delete mData;
        }

        template<typename T>
        CustomVariantBase* CustomVariant<T>::clone()
        {
            return new CustomVariant<T>(*mData);
        }

        template<typename T>
        bool CustomVariant<T>::equal(CustomVariantBase* _other)
        {
            return *mData == *(dynamic_cast<CustomVariant<T>*>(_other)->mData);
        }

        template<typename T>
        String CustomVariant<T>::toString() const
        {
            if constexpr (HasToString<T>::value)
            {
                return mData->toString();
            }
            else
            {
                return String("Unknown custom variant");
            }
        }

        template<typename T>
        CustomVariantReference<T>::CustomVariantReference(T* _value)
        {
            mType = Type<T>::typeName;
            mData = _value;
        }

        template<typename T>
        CustomVariantReference<T>::~CustomVariantReference()
        {    // @NOCOVERAGE
             // @NOCOVERAGE
        }

        template<typename T>
        CustomVariantBase* CustomVariantReference<T>::clone()
        {
            return new CustomVariantReference<T>(mData);
        }

        template<typename T>
        bool CustomVariantReference<T>::equal(CustomVariantBase* _other)
        {
            return mData == dynamic_cast<CustomVariantReference<T>*>(_other)->mData;
        }

        template<typename T>
        String CustomVariantReference<T>::toString() const
        {
            if constexpr (HasToString<T>::value)
            {
                return mData->toString();
            }
            else if constexpr (Michka::Type<T>::isNumeric)
            {
                return String::number(*mData);
            }
            else
            {
                return String("Unknown reference variant");
            }
        }
    }

    /* --------------------------------- Variant -------------------------------- */

    FORCE_INLINE Variant::Variant() :
        mType(Variant::Type::typeNull),
        mInt(0)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const std::nullptr_t& _value)  :
        mType(Variant::Type::typeNull),
        mInt(0)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const float& _value) :
        mType(Variant::Type::typeFloat),
        mFloat(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const double& _value) :
        mType(Variant::Type::typeFloat),
        mFloat(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const bool& _value) :
        mType(Variant::Type::typeBool),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const int& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned int& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const short int& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned short int& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const long long int& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned long long int& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const unsigned char& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const wchar_t& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char16_t& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char32_t& _value) :
        mType(Variant::Type::typeInt),
        mInt(_value)
    {
        //
    }

    FORCE_INLINE Variant::Variant(const char* _value) :
        mType(Variant::Type::typeString)
    {
        mString = new String(_value);
    }

    FORCE_INLINE Variant::Variant(const wchar_t* _value) :
        mType(Variant::Type::typeString)
    {
        mString = new String(_value);
    }

    FORCE_INLINE Variant::Variant(const char32_t* _value)  :
        mType(Variant::Type::typeString)
    {
        mString = new String(_value);
    }

    FORCE_INLINE Variant::Variant(const String& _value) :
        mType(Variant::Type::typeString)
    {
        mString = new String(_value);
    }

    FORCE_INLINE Variant::Variant(const List<Variant>& _value)
    {
        *this = _value;
    }

    template<typename T>
    FORCE_INLINE Variant::Variant(const std::initializer_list<T>& _value)
    {
        *this = _value;
    }

    template<typename T>
    FORCE_INLINE Variant::Variant(const T& _value)
    {
        *this = _value;
    }

    template<typename T>
    FORCE_INLINE Variant::Variant(T* _value)
    {
        *this = _value;
    }

    FORCE_INLINE Variant::Variant(const Variant& _value)
    {
        *this = _value;
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

    FORCE_INLINE bool Variant::is(const Type& _type) const
    {
        return mType == _type;
    }

    FORCE_INLINE bool Variant::isNull() const
    {
        return mType == Type::typeNull;
    }

    FORCE_INLINE bool Variant::isBool() const
    {
        return mType == Type::typeBool;
    }

    FORCE_INLINE bool Variant::isInt() const
    {
        return mType == Type::typeInt;
    }

    FORCE_INLINE bool Variant::isFloat() const
    {
        return mType == Type::typeFloat;
    }

    FORCE_INLINE bool Variant::isString() const
    {
        return mType == Type::typeString;
    }

    FORCE_INLINE bool Variant::isArray() const
    {
        return mType == Type::typeArray;
    }

    FORCE_INLINE bool Variant::isReference() const
    {
        return mType == Type::typeReference;
    }

    FORCE_INLINE bool Variant::isCustom() const
    {
        return mType == Type::typeCustom;
    }

    template<typename T>
    bool Variant::isConvertibleTo() const
    {
        switch (mType)
        {
            case Type::typeNull:
                return Michka::Type<T>::isNumeric || Michka::Type<T>::is<std::nullptr_t>();
            case Type::typeBool:
            case Type::typeInt:
                return Michka::Type<T>::isNumeric || Michka::Type<T>::is<String>();
            case Type::typeFloat:
                return Michka::Type<T>::isNumeric || Michka::Type<T>::is<String>();
            case Type::typeString:
                return Michka::Type<T>::isNumeric ||
                    Michka::Type<T>::is<String>() ||
                    Michka::Type<T>::is<String8>() ||
                    Michka::Type<T>::is<String32>() ||
                    Michka::Type<T>::is<wchar_t*>();
            case Type::typeArray:
                return (Michka::Type<T>::is<List<Variant>>());
            case Type::typeCustom:
                return mCustom->getType() == Michka::Type<Michka::Type<T>::RemovedPointerType>::typeName;
            case Type::typeReference:
                return mCustom->getType() == Michka::Type<Michka::Type<T>::RemovedPointerType>::typeName;
        }

        return false; // @NOCOVERAGE
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
                if constexpr (Michka::Type<T>::is<String>())
                {
                    return String("null");
                }
                break; // @NOCOVERAGE
            case Type::typeBool:
            case Type::typeInt:
                if constexpr (Michka::Type<T>::isNumeric)
                {
                    return (T)mInt;
                }
                if constexpr (Michka::Type<T>::is<String>())
                {
                    return String::number(mInt);
                }
                break; // @NOCOVERAGE
            case Type::typeFloat:
                if constexpr (Michka::Type<T>::isNumeric)
                {
                    return (T)mFloat;
                }
                if constexpr (Michka::Type<T>::is<String>())
                {
                    return String::number(mFloat);
                }
                break; // @NOCOVERAGE
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
                if constexpr (Michka::Type<T>::is<const wchar_t*>())
                {
                    return mString->cstr();
                }
                break; // @NOCOVERAGE
            case Type::typeArray:
                if constexpr (Michka::Type<T>::is<List<Variant>>())
                {
                    return *mList;
                }
                break; // @NOCOVERAGE
            case Type::typeCustom:
                if (mCustom->getType() == Michka::Type<Michka::Type<T>::RemovedPointerType>::typeName)
                {
                    if constexpr (Michka::Type<T>::isPointer)
                    {
                        return ((dynamic_cast<Private::CustomVariant<Michka::Type<T>::RemovedPointerType>*>(mCustom))->mData);
                    }
                    else
                    {
                        return *((dynamic_cast<Private::CustomVariant<Michka::Type<T>::RemovedPointerType>*>(mCustom))->mData);
                    }
                }
                break;
            case Type::typeReference:
                if (mCustom->getType() == Michka::Type<Michka::Type<T>::RemovedPointerType>::typeName)
                {
                    if constexpr (Michka::Type<T>::isPointer)
                    {
                        return ((dynamic_cast<Private::CustomVariantReference<Michka::Type<T>::RemovedPointerType>*>(mCustom))->mData);
                    }
                    else
                    {
                        return *((dynamic_cast<Private::CustomVariantReference<Michka::Type<T>::RemovedPointerType>*>(mCustom))->mData);
                    }
                }
                break;
        }

        return T();
    }

    FORCE_INLINE Variant& Variant::operator = (const std::nullptr_t& _value)
    {
        destroy();
        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const float& _value)
    {
        destroy();
        mType = Type::typeFloat;
        mFloat = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const double& _value)
    {
        destroy();
        mType = Type::typeFloat;
        mFloat = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const bool& _value)
    {
        destroy();
        mType = Type::typeBool;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const int& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned int& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const short int& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned short int& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const long long int& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned long long int& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const unsigned char& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const wchar_t& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char16_t& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char32_t& _value)
    {
        destroy();
        mType = Type::typeInt;
        mInt = _value;

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char* _value)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_value);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const wchar_t* _value)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_value);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const char32_t* _value)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_value);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const String& _value)
    {
        destroy();
        mType = Type::typeString;
        mString = new String(_value);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const List<Variant>& _value)
    {
        destroy();
        mType = Type::typeArray;
        mList = new List<Variant>(_value);

        return *this;
    }

    template<typename T>
    FORCE_INLINE Variant& Variant::operator = (const std::initializer_list<T>& _value)
    {
        destroy();
        mType = Type::typeArray;
        mList = new List<Variant>();
        for (auto element : _value)
        {
            mList->pushBack(Variant(element));
        }

        return *this;
    }

    template<typename T>
    FORCE_INLINE Variant& Variant::operator = (const T& _value)
    {
        destroy();
        mType = Type::typeCustom;
        mCustom = new Private::CustomVariant<T>(_value);

        return *this;
    }

    template<typename T>
    FORCE_INLINE Variant& Variant::operator = (T* _value)
    {
        destroy();
        mType = Type::typeReference;
        mCustom = new Private::CustomVariantReference<T>(_value);

        return *this;
    }

    FORCE_INLINE Variant& Variant::operator = (const Variant& _value)
    {
        destroy();
        mType = _value.mType;
        switch (mType)
        {
            case Type::typeNull:
                break; // @NOCOVERAGE
            case Type::typeBool:
            case Type::typeInt:
                mInt = _value.mInt;
                break;
            case Type::typeFloat:
                mFloat = _value.mFloat;
                break;
            case Type::typeString:
                mString = new String(*_value.mString);
                break;
            case Type::typeArray:
                mList = new List<Variant>(*_value.mList);
                break;
            case Type::typeCustom:
            case Type::typeReference:
                mCustom = _value.mCustom->clone();
                break;
        };

        return *this;
    }

    FORCE_INLINE bool Variant::operator != (const Variant& _other) const
    {
        return !(*this == _other);
    }

    template<typename T>
    Variant::operator T() const
    {
        return to<T>();
    }
}
