#ifndef __STRING_H__
#define __STRING_H__

#include "Defines.h"

namespace Mishka
{
	/**
	 * \brief Get size of string.
	 *
	 * \tparam T
	 * \param _str string
	 * \return string size
	 */
	template<typename T>
	FORCE_INLINE u32 stringSize(const T* _str);

	template<typename T>
	class StringTemplate
	{
	public:
		typedef StringTemplate<char> String8;
		typedef StringTemplate<wchar_t> String;
		typedef StringTemplate<char32_t> String32;


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
		 * \brief Clear string.
		 *
		 * \return Self
		 */
		FORCE_INLINE StringTemplate<T>& clear();

		/**
		 * \brief Get string as C characters.
		 */
		const T* cstr() const;

		/**
		 * \brief Find a character in string.
		 * if not found then StringBase<T>::notFound will return.
		 *
		 * \param _character
		 * \return index of character
		 */
		template<typename T2>
		u32 find(const T2& _character) const;

		/**
		 * \brief Get string length.
		 *
		 * \return size
		 */
		FORCE_INLINE u32 getSize() const;

		/**
		 * \brief Get reversed copy of this string.
		 *
		 * \return Reversed string
		 */
		FORCE_INLINE StringTemplate<T> getReversed() const;

		/**
		 * \brief Check string is empty.
		 */
		FORCE_INLINE bool isEmpty() const;

		/**
		 * \brief Reverse string.
		 *
		 * \return Self
		 */
		StringTemplate<T>& reverse();

		/**
		 * \brief Resize string buffer.
		 *
		 * \return Self
		 */
		StringTemplate<T>& resize(u32 _newSize);

		/**
		 * \brief Convert float number to string.
		 */
		static StringTemplate<T> number(float _number);

		/**
		 * \brief Convert double number to string.
		 */
		static StringTemplate<T> number(double _number);

		/**
		 * \brief Convert long double number to string.
		 */
		static StringTemplate<T> number(long double _number);

		/**
		 * \brief Convert any integer type to string.
		 */
		template<typename TYPE>
		static StringTemplate<T> number(TYPE _number, const u8& _base = 10);

		/**
		 * \brief Convert string to number.
		 *
		 * \tparam TYPE
		 * \param _base integer base
		 */
		template<typename TYPE>
		TYPE toNumber(const u32& _base = 10) const;

		template<typename T2>
		StringTemplate<T>& operator = (const T2* _str);
		FORCE_INLINE StringTemplate<T>& operator = (const StringTemplate<char>& _other);
		FORCE_INLINE StringTemplate<T>& operator = (const StringTemplate<wchar_t>& _other);
		FORCE_INLINE StringTemplate<T>& operator = (const StringTemplate<char32_t>& _other);
		FORCE_INLINE StringTemplate<T>& operator = (StringTemplate<T>&& _other);
		template<typename T2>
		bool operator == (const T2* _str) const;
		template<typename T2>
		FORCE_INLINE bool operator != (const T2* _str) const;
		template<typename T2>
		FORCE_INLINE bool operator == (const StringTemplate<T2>& _str) const;
		template<typename T2>
		FORCE_INLINE bool operator != (const StringTemplate<T2>& _str) const;

		FORCE_INLINE T& operator[] (const u32& _index);
		FORCE_INLINE T operator[] (const u32& _index) const;
	public:
		/**
		 * \brief Not found index for find functions.
		 */
		static const u32 notFound;

		/**
		 * \brief An empty string
		 */
		static const StringTemplate<T> empty;
	private:
		T* mData = nullptr;
	};

	typedef StringTemplate<char> String8;
	typedef StringTemplate<wchar_t> String;
	typedef StringTemplate<char32_t> String32;
}

#include "String.inl"

#endif // __STRING_H__
