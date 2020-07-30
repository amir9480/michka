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

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include "Core/Defines.h"
#include "Core/Container/String.h"
#include "Core/Container/List.h"

namespace Michka
{
    class MICHKA_API Variant
    {
    public:
        enum class Type
        {
            typeNull,
            typeBool,
            typeInt,
            typeFloat,
            typeString,
            typeArray,
            typeCustom
        };
    public:
        FORCE_INLINE Variant();
        FORCE_INLINE Variant(const std::nullptr_t& _val);
        FORCE_INLINE Variant(const int& _val);
        FORCE_INLINE Variant(const unsigned int& _val);
        FORCE_INLINE Variant(const float& _val);
        FORCE_INLINE Variant(const double& _val);
        FORCE_INLINE Variant(const bool& _val);
        FORCE_INLINE Variant(const short int& _val);
        FORCE_INLINE Variant(const unsigned short int& _val);
        FORCE_INLINE Variant(const long long int& _val);
        FORCE_INLINE Variant(const unsigned long long int& _val);
        FORCE_INLINE Variant(const char& _val);
        FORCE_INLINE Variant(const unsigned char& _val);
        FORCE_INLINE Variant(const wchar_t& _val);
        FORCE_INLINE Variant(const char16_t& _val);
        FORCE_INLINE Variant(const char32_t& _val);
        FORCE_INLINE Variant(const char* _val);
        FORCE_INLINE Variant(const wchar_t* _val);
        FORCE_INLINE Variant(const char32_t* _val);
        FORCE_INLINE Variant(const String& _val);
        FORCE_INLINE Variant(const Variant& _val);
        FORCE_INLINE ~Variant();

        /**
         * @brief Destroy variant and set to null.
         *
         * @return Self
         */
        FORCE_INLINE Variant& destroy();

        /**
         * @brief Get variant type.
         */
        FORCE_INLINE Type getType() const;

        /**
         * @brief Convert variant to native type.
         *
         * @tparam T
         */
        template<typename T>
        T to() const;

        FORCE_INLINE Variant& operator = (const std::nullptr_t& _val);
        FORCE_INLINE Variant& operator = (const int& _val);
        FORCE_INLINE Variant& operator = (const unsigned int& _val);
        FORCE_INLINE Variant& operator = (const float& _val);
        FORCE_INLINE Variant& operator = (const double& _val);
        FORCE_INLINE Variant& operator = (const bool& _val);
        FORCE_INLINE Variant& operator = (const short int& _val);
        FORCE_INLINE Variant& operator = (const unsigned short int& _val);
        FORCE_INLINE Variant& operator = (const long long int& _val);
        FORCE_INLINE Variant& operator = (const unsigned long long int& _val);
        FORCE_INLINE Variant& operator = (const char& _val);
        FORCE_INLINE Variant& operator = (const unsigned char& _val);
        FORCE_INLINE Variant& operator = (const wchar_t& _val);
        FORCE_INLINE Variant& operator = (const char16_t& _val);
        FORCE_INLINE Variant& operator = (const char32_t& _val);
        FORCE_INLINE Variant& operator = (const char* _val);
        FORCE_INLINE Variant& operator = (const wchar_t* _val);
        FORCE_INLINE Variant& operator = (const char32_t* _val);
        FORCE_INLINE Variant& operator = (const String& _val);
        FORCE_INLINE Variant& operator = (const Variant& _val);

    private:
        Type mType;
        union
        {
            i64 mInt;
            double mFloat;
            String* mString;
            List<Variant>* mList;
            void* mCustom;
        };
    };
}

#include "Variant.inl"

#endif // __VARIANT_H__
