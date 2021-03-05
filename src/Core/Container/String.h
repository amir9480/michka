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

#ifndef __STRING_H__
#define __STRING_H__

#include "Core/Defines.h"
#include "Core/Reflection/Type.h"
#include "Core/Reflection/ReflectionClass.h"
#include "MichkaGenerated/Core/Container/String.generated.h"

namespace Michka
{
    template<typename T>
    class Vector;

    template<typename T>
    class MICHKA_API StringTemplate
    {
        MICHKA_CLASS(StringTemplate<T>);
    public:
        typedef StringTemplate<char> String8;
        typedef StringTemplate<wchar_t> String;
        typedef StringTemplate<char32_t> String32;
        typedef T* Iterator;
        typedef const T* ConstIterator;


    public:
        FORCE_INLINE StringTemplate();
        template<typename T2>
        FORCE_INLINE StringTemplate(const T2* _str);
        FORCE_INLINE StringTemplate(const StringTemplate<char>& _other);
        FORCE_INLINE StringTemplate(const StringTemplate<wchar_t>& _other);
        FORCE_INLINE StringTemplate(const StringTemplate<char32_t>& _other);
        FORCE_INLINE StringTemplate(StringTemplate<T>&& _other);
        FORCE_INLINE ~StringTemplate();

        /**
         * @brief Clear string.
         *
         * @return Self
         */
        FORCE_INLINE StringTemplate<T>& clear();

        /**
         * @brief Iterator begin.
         */
        Iterator begin();
        ConstIterator begin() const;

        /**
         * @brief Get string as C characters.
         */
        const T* cstr() const;

        /**
         * @brief Iterator end.
         */
        Iterator end();
        ConstIterator end() const;

        /**
         * @brief Find a character in string.
         *
         * @param _character
         * @param _offset
         * @return index of character. If not found StringTemplate<T>::notFound will return.
         */
        u32 find(const T& _character, const u32& _offset = 0) const;

        /**
         * @brief Find a character from end to begining.
         *
         * @param _character
         * @param _offset
         * @return u32 index of character. If not found StringTemplate<T>::notFound will return.
         */
        u32 findLast(const T& _character, const u32& _offset = u32Info::max) const;

        /**
         * @brief Find a sub string inside string.
         *
         * @param _string
         * @param _offset
         * @return u32 index of string. If not found StringTemplate<T>::notFound will return.
         */
        u32 find(const StringTemplate<T>& _string, const u32& _offset = 0) const;

        /**
         * @brief Find a sub string inside string from end to begin.
         *
         * @param _string
         * @param _offset
         * @return u32 index of character. If not found StringTemplate<T>::notFound will return.
         */
        u32 findLast(const StringTemplate<T>& _string, const u32& _offset = u32Info::max) const;

        /**
         * @brief Create string from utf8 encoded string.
         *
         * @param _string
         */
        static StringTemplate<T> fromUtf8(const char* _string);

        /**
         * @brief Create string from utf8 encoded string.
         *
         * @param _string
         */
        static StringTemplate<T> fromUtf16(const wchar_t* _string);

        /**
         * @brief Create string from utf32 encoded string.
         *
         * @param _string
         */
        static StringTemplate<T> fromUtf32(const char32_t* _string);

        /**
         * @brief Get copy of this with removed space (or any other character) from beginning.
         *
         * @param _characters
         */
        FORCE_INLINE StringTemplate<T> getLeftTrimed(const StringTemplate<T>& _characters = "\t\n\r ") const;

        /**
         * @brief Count of characters.
         *
         * @sa getSize
         * @return length
         */
        FORCE_INLINE u32 getLength() const;

        /**
         * @brief Clone string, find a sub string and replace it with another substring and returns result.
         *
         * @param _find
         * @param _replace
         * @param _offset
         * @return String copy after replace
         */
        FORCE_INLINE StringTemplate<T> getReplaced(const StringTemplate<T>& _find, const StringTemplate<T>& _replace = StringTemplate<T>::empty, const u32& _start = 0, const u32& _end = u32Info::max) const;

        /**
         * @brief Get reversed copy of this string.
         *
         * @return Reversed string
         */
        FORCE_INLINE StringTemplate<T> getReversed() const;

        /**
         * @brief Get copy of this with removed space (or any other character) from end.
         *
         * @param _characters
         */
        FORCE_INLINE StringTemplate<T> getRightTrimed(const StringTemplate<T>& _characters = "\t\n\r ") const;

        /**
         * @brief Get size of string.
         * @warning This is not count of characters. for counting characters use getLength instead..
         *
         * @sa getLength
         * @return size
         */
        FORCE_INLINE u32 getSize() const;

        /**
         * @brief Get copy of this with removed space (or any other character) from beginning and end.
         *
         * @param _characters
         */
        FORCE_INLINE StringTemplate<T> getTrimed(const StringTemplate<T>& _characters = "\t\n\r ") const;

        /**
         * @brief Insert a substring in middle of string.
         *
         * @param _string
         * @param _offset
         * @return Self
         */
        String& insert(const StringTemplate<T>& _string, const u32& _offset = 0);

        /**
         * @brief Check string is empty.
         */
        FORCE_INLINE bool isEmpty() const;

        /**
         * @brief Check string is not empty.
         */
        FORCE_INLINE bool isNotEmpty() const;

        /**
         * @brief Remove space (or any other character) from beginning.
         *
         * @return Self
         */
        FORCE_INLINE StringTemplate<T>& leftTrim(const StringTemplate<T>& _characters = "\t\n\r ");

        /**
         * @brief Convert boolean to string.
         */
        static StringTemplate<T> number(bool _bool);

        /**
         * @brief Convert float number to string.
         */
        static StringTemplate<T> number(float _number);

        /**
         * @brief Convert double number to string.
         */
        static StringTemplate<T> number(double _number);

        /**
         * @brief Convert long double number to string.
         */
        static StringTemplate<T> number(long double _number);

        /**
         * @brief Convert any integer type to string.
         */
        template<typename NumberType>
        static StringTemplate<T> number(NumberType _number, const u8& _base = 10);

        /**
         * @brief Prepend a string to this string.
         *
         * @param _other
         * @return Self
         */
        FORCE_INLINE StringTemplate<T>& prepend(const StringTemplate<T>& _other);

        /**
         * @brief Remove part of string for _size characters.
         *
         * @param _start
         * @param _size
         * @return
         */
        StringTemplate<T>& remove(const u32& _start, const u32& _size = u32Info::max);

        /**
         * @brief Reverse string.
         *
         * @return Self
         */
        StringTemplate<T>& reverse();

        /**
         * @brief Find a sub string and replace it with another substring.
         *
         * @param _find
         * @param _replace
         * @param _start
         * @param _end
         * @return Self
         */
        StringTemplate<T>& replace(const StringTemplate<T>& _find, const StringTemplate<T>& _replace = StringTemplate<T>::empty, const u32& _start = 0, const u32& _end = u32Info::max);

        /**
         * @brief Resize string buffer.
         *
         * @return Self
         */
        StringTemplate<T>& resize(u32 _newSize);

        /**
         * @brief Remove space (or any other character) from end.
         *
         * @return Self
         */
        FORCE_INLINE StringTemplate<T>& rightTrim(const StringTemplate<T>& _characters = "\t\n\r ");

        /**
         * @brief Split string to sub string based on character.
         *
         * @param _character
         */
        Vector<StringTemplate<T>> split(const T& _character) const;

        /**
         * @brief Split string to sub string based on string.
         *
         * @param _character
         */
        Vector<StringTemplate<T>> split(const StringTemplate<T>& _string) const;

        /**
         * @brief Get size of string.
         *
         * @tparam T
         * @param _str string
         * @return string size
         *
         * @sa stringLength
         */
        static u32 stringSize(const T* _str);

        /**
         * @brief Get string characters count.
         *
         * @tparam T
         * @param _str string
         * @return string length
         *
         * @sa stringSize
         */
        static u32 stringLength(const T* _str);

        /**
         * @brief Get part of string.
         *
         * @param _start
         * @param _size
         * @return
         */
        StringTemplate<T> subString(const u32& _start, const u32& _size = u32Info::max) const;

        /**
         * @brief Convert to lowercase.
         *
         * @return
         */
        StringTemplate<T> toLower() const;

        /**
         * @brief Convert string to number.
         *
         * @tparam NumberType
         * @param _base integer base
         */
        template<typename NumberType>
        NumberType toNumber(const u32& _base = 10) const;

        /**
         * @brief Convert to upper case.
         *
         * @return
         */
        StringTemplate<T> toUpper() const;

        /**
         * @brief Convert to utf8 encoded string.
         *
         * @return
         */
        StringTemplate<char> toUtf8() const;

        /**
         * @brief Convert to utf16 encoded string.
         *
         * @return
         */
        StringTemplate<wchar_t> toUtf16() const;

        /**
         * @brief Convert to utf32 encoded string.
         *
         * @return
         */
        StringTemplate<char32_t> toUtf32() const;

        /**
         * @brief Remove space (or any other character) from beginning and end.
         *
         * @return Self
         */
        FORCE_INLINE StringTemplate<T>& trim(const StringTemplate<T>& _characters = "\t\n\r ");

        template<typename T2>
        StringTemplate<T>& operator = (const T2* _str);
        FORCE_INLINE StringTemplate<T>& operator = (const StringTemplate<char>& _other);
        FORCE_INLINE StringTemplate<T>& operator = (const StringTemplate<wchar_t>& _other);
        FORCE_INLINE StringTemplate<T>& operator = (const StringTemplate<char32_t>& _other);
        FORCE_INLINE StringTemplate<T>& operator = (StringTemplate<T>&& _other);

        FORCE_INLINE StringTemplate<T> operator + (const StringTemplate<T>& _other) const;
        FORCE_INLINE StringTemplate<T>& operator += (const StringTemplate<T>& _other);


        template<typename T2>
        bool operator == (const T2* _str) const;
        template<typename T2>
        FORCE_INLINE bool operator != (const T2* _str) const;
        template<typename T2>
        FORCE_INLINE bool operator == (const StringTemplate<T2>& _str) const;
        template<typename T2>
        FORCE_INLINE bool operator != (const StringTemplate<T2>& _str) const;

        FORCE_INLINE T& operator [] (const u32& _index);
        FORCE_INLINE T operator [] (const u32& _index) const;
    public:
        /**
         * @brief Not found index for find functions.
         */
        static const u32 notFound;

        /**
         * @brief An empty string
         */
        static const StringTemplate<T> empty;
    private:
        struct Utf8Character
        {
            char character[7];
        };

        struct Utf16Character
        {
            wchar_t character[3];
        };

        /**
         * @brief Encode a character to UTF8.
         *
         * @param _character
         */
        FORCE_INLINE static Utf8Character utf8Encode(u32 _character);

        /**
         * @brief Decode a UTF8 encoded character.
         *
         * @param _character
         */
        FORCE_INLINE static u32 utf8Decode(const char* _character);

        /**
         * @brief Encode a character to UTF16.
         *
         * @param _character
         */
        FORCE_INLINE static Utf16Character utf16Encode(u32 _character);

        /**
         * @brief Decode a UTF8 encoded character.
         *
         * @param _character
         */
        FORCE_INLINE static u32 utf16Decode(const wchar_t* _character);
    private:
        T* mData = nullptr;
    };

    template<typename T, typename T2>
    FORCE_INLINE StringTemplate<T2> operator + (const T* _first, const StringTemplate<T2>& _second);

    typedef StringTemplate<char> String8;
    typedef StringTemplate<wchar_t> String;
    typedef StringTemplate<char32_t> String32;
}

#include "String.inl"

#endif // __STRING_H__
