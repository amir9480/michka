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
#include <initializer_list>

namespace Michka
{
    class Variant;

    namespace Private
    {
        class MICHKA_API CustomVariantBase
        {
        public:
            FORCE_INLINE CustomVariantBase();
            virtual ~CustomVariantBase();

            /**
             * @brief Get a copy of this.
             */
            virtual CustomVariantBase* clone() = 0;

            /**
             * @brief Compare to another custom variant.
             *
             * @param _other
             */
            virtual bool equal(CustomVariantBase* _other);

            /**
             * @brief Get type name.
             */
            FORCE_INLINE String getType() const;

            /**
             * @brief Get value as string.
             */
            virtual String toString() const;

        protected:
            String mType;
        };

        template<typename T>
        class MICHKA_API CustomVariant : public CustomVariantBase
        {
            friend class Variant;
        public:
            CustomVariant(const T& _value);
            virtual ~CustomVariant();

            /**
             * @brief Get a copy of this.
             */
            virtual CustomVariantBase* clone();

            /**
             * @brief Compare to another custom variant.
             *
             * @param _other
             */
            virtual bool equal(CustomVariantBase* _other);

            /**
             * @brief Get value as string.
             */
            virtual String toString() const;

        protected:
            T* mData = nullptr;
        };

        template<typename T>
        class MICHKA_API CustomVariantReference : public CustomVariantBase
        {
            friend class Variant;
        public:
            CustomVariantReference(T* _value);
            virtual ~CustomVariantReference();

            /**
             * @brief Get a copy of this.
             */
            virtual CustomVariantBase* clone();

            /**
             * @brief Compare to another custom variant.
             *
             * @param _other
             */
            virtual bool equal(CustomVariantBase* _other);

            /**
             * @brief Get value as string.
             */
            virtual String toString() const;

        protected:
            T* mData = nullptr;
        };
    }

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
            typeReference,
            typeCustom,
        };
    public:
        FORCE_INLINE Variant();
        FORCE_INLINE Variant(const std::nullptr_t& _value);
        FORCE_INLINE Variant(const float& _value);
        FORCE_INLINE Variant(const double& _value);
        FORCE_INLINE Variant(const bool& _value);
        FORCE_INLINE Variant(const int& _value);
        FORCE_INLINE Variant(const unsigned int& _value);
        FORCE_INLINE Variant(const short int& _value);
        FORCE_INLINE Variant(const unsigned short int& _value);
        FORCE_INLINE Variant(const long long int& _value);
        FORCE_INLINE Variant(const unsigned long long int& _value);
        FORCE_INLINE Variant(const char& _value);
        FORCE_INLINE Variant(const unsigned char& _value);
        FORCE_INLINE Variant(const wchar_t& _value);
        FORCE_INLINE Variant(const char16_t& _value);
        FORCE_INLINE Variant(const char32_t& _value);
        FORCE_INLINE Variant(const char* _value);
        FORCE_INLINE Variant(const wchar_t* _value);
        FORCE_INLINE Variant(const char32_t* _value);
        FORCE_INLINE Variant(const String& _value);
        FORCE_INLINE Variant(const List<Variant>& _value);
        template<typename T>
        FORCE_INLINE Variant(const std::initializer_list<T>& _value);
        template<typename T>
        FORCE_INLINE Variant(const T& _value);
        template<typename T>
        FORCE_INLINE Variant(T* _value);
        FORCE_INLINE Variant(const Variant& _value);
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
         * @brief Check type is a special variant type.
         *
         * @param _type
         */
        FORCE_INLINE bool is(const Type& _type) const;

        /**
         * @brief Check type is string
         */
        FORCE_INLINE bool isNull() const;

        /**
         * @brief Check type is bool
         */
        FORCE_INLINE bool isBool() const;

        /**
         * @brief Check type is int
         */
        FORCE_INLINE bool isInt() const;

        /**
         * @brief Check type is float
         */
        FORCE_INLINE bool isFloat() const;

        /**
         * @brief Check type is string
         */
        FORCE_INLINE bool isString() const;

        /**
         * @brief Check type is array
         */
        FORCE_INLINE bool isArray() const;

        /**
         * @brief Check type is reference
         */
        FORCE_INLINE bool isReference() const;

        /**
         * @brief Check type is custom
         */
        FORCE_INLINE bool isCustom() const;

        /**
         * @brief Check variant can convert to.
         */
        template<typename T>
        bool isConvertibleTo() const;

        /**
         * @brief Convert variant to native type.
         *
         * @tparam T
         */
        template<typename T>
        T to() const;

        /**
         * @brief Get value as string.
         */
        String toString() const;

        FORCE_INLINE Variant& operator = (const std::nullptr_t& _value);
        FORCE_INLINE Variant& operator = (const float& _value);
        FORCE_INLINE Variant& operator = (const double& _value);
        FORCE_INLINE Variant& operator = (const bool& _value);
        FORCE_INLINE Variant& operator = (const int& _value);
        FORCE_INLINE Variant& operator = (const unsigned int& _value);
        FORCE_INLINE Variant& operator = (const short int& _value);
        FORCE_INLINE Variant& operator = (const unsigned short int& _value);
        FORCE_INLINE Variant& operator = (const long long int& _value);
        FORCE_INLINE Variant& operator = (const unsigned long long int& _value);
        FORCE_INLINE Variant& operator = (const char& _value);
        FORCE_INLINE Variant& operator = (const unsigned char& _value);
        FORCE_INLINE Variant& operator = (const wchar_t& _value);
        FORCE_INLINE Variant& operator = (const char16_t& _value);
        FORCE_INLINE Variant& operator = (const char32_t& _value);
        FORCE_INLINE Variant& operator = (const char* _value);
        FORCE_INLINE Variant& operator = (const wchar_t* _value);
        FORCE_INLINE Variant& operator = (const char32_t* _value);
        FORCE_INLINE Variant& operator = (const String& _value);
        FORCE_INLINE Variant& operator = (const List<Variant>& _value);
        template<typename T>
        FORCE_INLINE Variant& operator = (const std::initializer_list<T>& _value);
        template<typename T>
        FORCE_INLINE Variant& operator = (const T& _value);
        template<typename T>
        FORCE_INLINE Variant& operator = (T* _value);
        FORCE_INLINE Variant& operator = (const Variant& _value);

        bool operator == (const Variant& _other) const;
        FORCE_INLINE bool operator != (const Variant& _other) const;

        template<typename T>
        operator T () const;

    private:
        Type mType = Type::typeNull;
        union
        {
            i64 mInt;
            double mFloat;
            i64* mIntReference;
            double* mFloatReference;
            String* mString;
            List<Variant>* mList;
            Private::CustomVariantBase* mCustom;
        };
    };
}

#include "Variant.inl"

#endif // __VARIANT_H__
