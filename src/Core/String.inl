#include "String.h"
#include "Helpers.h"
#include "Type.h"
#include "Exception.h"

namespace Michka
{
	template<typename T>
	const StringTemplate<T> StringTemplate<T>::empty;

	template<typename T>
	const u32 StringTemplate<T>::notFound = u32Info::max;

	template<typename T>
	FORCE_INLINE StringTemplate<T>::StringTemplate()
	{
	}

	template<typename T>
	template<typename T2>
	FORCE_INLINE StringTemplate<T>::StringTemplate(const T2* _str)
	{
		*this = _str;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>::StringTemplate(const StringTemplate<char>& _other)
	{
		*this = _other.cstr();
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>::StringTemplate(const StringTemplate<wchar_t>& _other)
	{
		*this = _other.cstr();
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>::StringTemplate(const StringTemplate<char32_t>& _other)
	{
		*this = _other.mData;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>::StringTemplate(StringTemplate<T>&& _other)
	{
		*this = std::move(_other);
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>::~StringTemplate()
	{
		clear();
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::clear()
	{
		if (mData)
		{
			delete[] mData;
			mData = nullptr;
		}
		return *this;
	}

	template<typename T>
	typename StringTemplate<T>::Iterator StringTemplate<T>::begin()
	{
		return mData;
	}

	template<typename T>
	typename StringTemplate<T>::ConstIterator StringTemplate<T>::begin() const
	{
		return mData;
	}

	template<typename T>
	const T* StringTemplate<T>::cstr() const
	{
		static const T emptyString[2] = { 0, 0 };
		if (mData)
		{
			return mData;
		}
		return emptyString;
	}

	template<typename T>
	typename StringTemplate<T>::Iterator StringTemplate<T>::end()
	{
		return mData + getSize();
	}

	template<typename T>
	typename StringTemplate<T>::ConstIterator StringTemplate<T>::end() const
	{
		return mData + getSize();
	}

	template<typename T>
	FORCE_INLINE u32 StringTemplate<T>::find(const T& _character, const u32& _offset) const
	{
		u32 thisSize = getSize();
		if (mData)
		{
			T* pointer = static_cast<T*>(memchr((void*)(mData + _offset), T(_character), (thisSize - _offset) * sizeof(T)));
			if (pointer)
			{
				return u32(pointer - mData);
			}
		}
		return notFound;
	}

	template<typename T>
	u32 StringTemplate<T>::findLast(const T& _character, const u32& _offset) const
	{
		u32 thisSize = getSize();
		u32 offset =  _offset == u32Info::max ? thisSize : _offset;
		if (offset == 0)
		{
			return notFound;
		}
		u32 result = notFound;
		if (mData)
		{
			while (T* pointer = (T*)memchr((void*)(mData + (result != notFound ? result + 1 : 0)), T(_character), thisSize * sizeof(T)))
			{
				if (u32(pointer - mData) > offset)
				{
					break;
				}
				result = u32(pointer - mData);
			}
		}
		return result;
	}

	template<typename T>
	u32 StringTemplate<T>::find(const StringTemplate<T>& _string, const u32& _offset) const
	{
		if (_string.isNotEmpty() && this->isNotEmpty())
		{
			u32 offset = _offset;
			u32 thisSize = getSize();
			while ((offset = find(_string[0], offset)) != notFound && thisSize - offset >= _string.getSize())
			{
				for (register u32 i = 0; i <= _string.getSize(); i++)
				{
					if (_string.mData[i] == 0)
					{
						return offset;
					}
					if (mData[i + offset] != _string.mData[i])
					{
						offset++;
						break;
					}
				}
			}
		}
		return notFound;
	}

	template<typename T>
	u32 StringTemplate<T>::findLast(const StringTemplate<T>& _string, const u32& _offset) const
	{
		if (_string.isNotEmpty() && this->isNotEmpty())
		{
			u32 offset =  (_offset == u32Info::max ? getSize() : _offset) - _string.getSize();
			u32 thisSize = getSize();
			while ((offset = findLast(_string[0], offset)) != notFound && thisSize - offset >= _string.getSize())
			{
				for (register u32 i = 0; i <= _string.getSize(); i++)
				{
					if (_string.mData[i] == 0)
					{
						return offset;
					}
					if (mData[i + offset] != _string.mData[i])
					{
						break;
					}
				}
			}
		}
		return notFound;
	}

	template<typename T>
	FORCE_INLINE u32 StringTemplate<T>::getLength() const
	{
		return stringLength(mData);
	}

	template<typename T>
	FORCE_INLINE u32 StringTemplate<T>::getSize() const
	{
		return stringSize(mData);
	}

	template<typename T>
	inline FORCE_INLINE StringTemplate<T> StringTemplate<T>::getReversed() const
	{
		StringTemplate<T> out = mData;
		return out.reverse();
	}

	template<typename T>
	String& StringTemplate<T>::insert(const StringTemplate<T>& _string, const u32& _offset)
	{
		if (_string.getSize() > 0)
		{
			u32 thisSize = getSize();
			u32 strSize = _string.getSize();
			u32 spaceSize = (_offset >= thisSize ? (_offset - thisSize) + 1 : 0);
			resize(thisSize + strSize + spaceSize);
			if (spaceSize > 0)
			{
				for (register u32 i = thisSize; i < thisSize + spaceSize; i++)
				{
					mData[i] = ' ';
				}
			}
			else
			{
				memcpy((void*)(mData + _offset + strSize), (void*)(mData + _offset), (thisSize >= _offset ? thisSize - _offset : 0) * sizeof(T));
			}
			memcpy((void*)(mData + _offset), (void*)(_string.mData), strSize * sizeof(T));
		}
		return *this;
	}

	template<typename T>
	FORCE_INLINE bool StringTemplate<T>::isEmpty() const
	{
		return getSize() == 0;
	}

	template<typename T>
	FORCE_INLINE bool StringTemplate<T>::isNotEmpty() const
	{
		return getSize() != 0;
	}

	template<typename T>
	template<typename NumberType>
	StringTemplate<T> StringTemplate<T>::number(NumberType _number, const u8& _base)
	{
		if (_base < 2 || _base > 16)
		{
			throw Exception("String::number(...) : Base must be between 2 & 16.");
		}
		static const StringTemplate<T> numberCharacters = "0123456789abcdef";
		StringTemplate<T> out;
		out.resize((sizeof(NumberType) * 8) + 1);
		bool negetive = false;
		int index = 0;
		if (_number < 0)
		{
			negetive = true;
			_number = -_number;
		}
		do
		{
			out[index++] = numberCharacters[_number % _base];
			_number /= _base;
		} while (_number > 0);
		if (negetive)
		{
			out[index++] = (T)'-';
		}
		return out.reverse();
	}

	template<typename T>
	StringTemplate<T> StringTemplate<T>::number(float _number)
	{
		char buffer[100];
		sprintf(buffer, "%g", _number);
		return buffer;
	}

	template<typename T>
	StringTemplate<T> StringTemplate<T>::number(double _number)
	{
		char buffer[100];
		sprintf(buffer, "%lg", _number);
		return buffer;
	}

	template<typename T>
	StringTemplate<T> StringTemplate<T>::number(long double _number)
	{
		char buffer[100];
		sprintf(buffer, "%Lg", _number);
		return buffer;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::prepend(const StringTemplate<T>& _other)
	{
		*this = _other + std::move(*this);
		return *this;
	}

	template<typename T>
	StringTemplate<T>& StringTemplate<T>::remove(const u32& _start, const u32& _size)
	{
		u32 thisSize = getSize();
		u32 size = min(_size, thisSize - _start);
		if (_start == 0 && _size >= thisSize)
		{
			clear();
		}
		else
		{
			memcpy((void*)(mData + _start), (void*)(mData + _start + size), (thisSize - _start) * sizeof(T));
		}
		return *this;
	}

	template<typename T>
	StringTemplate<T>& StringTemplate<T>::reverse()
	{
		// TODO: Support utf8 / utf16
		u32 size = getSize();
		u32 sizeOn2 = getSize() / 2;
		for (register u32 i = 0; i < sizeOn2; i++)
		{
			swap(mData[i], mData[size - 1 - i]);
		}
		return *this;
	}

	template<typename T>
	StringTemplate<T>& StringTemplate<T>::replace(const StringTemplate<T>& _find, const StringTemplate<T>& _replace, const u32& _start, const u32& _end)
	{
		u32 positionToReplace = _start;
		u32 replaceSize = _replace.getSize();
		u32 findSize = _find.getSize();
		if (replaceSize == findSize)
		{
			while ((positionToReplace = find(_find, positionToReplace)) != notFound && positionToReplace <= _end)
			{
				memcpy((void*)(mData + positionToReplace), (void*)_replace.mData, replaceSize * sizeof(T));
			}
		}
		else if (replaceSize > findSize)
		{
			while ((positionToReplace = find(_find, positionToReplace)) != notFound && positionToReplace <= _end)
			{
				u32 thisSize = getSize();
				resize(thisSize + (replaceSize - findSize));
				memcpy((void*)(mData + positionToReplace + findSize + (replaceSize - findSize)), (void*)(mData + positionToReplace + findSize), (thisSize - (positionToReplace + findSize)) * sizeof(T));
				memcpy((void*)(mData + positionToReplace), (void*)_replace.mData, replaceSize * sizeof(T));
			}
		}
		else
		{
			while ((positionToReplace = find(_find, positionToReplace)) != notFound && positionToReplace <= _end)
			{
				u32 thisSize = getSize();
				memcpy((void*)(mData + positionToReplace + findSize - (findSize - replaceSize)), (void*)(mData + positionToReplace + findSize), (thisSize - (positionToReplace + findSize) + 1) * sizeof(T));
				memcpy((void*)(mData + positionToReplace), (void*)_replace.mData, replaceSize * sizeof(T));
			}
		}
		return *this;
	}

	template<typename T>
	StringTemplate<T>& StringTemplate<T>::resize(u32 _newSize)
	{
		if (_newSize != getSize())
		{
			T* old = nullptr;
			if (mData)
			{
				old = mData;
			}
			mData = new T[_newSize + 1];
			memset(mData, 0, (_newSize + 1) * sizeof(T));
			if (old)
			{
				u32 size = stringSize(old);
				size = _newSize < size ? _newSize : size;
				memcpy(mData, old, size * sizeof(T));
				delete[] old;
			}
		}
		return *this;
	}

	template<typename T>
	StringTemplate<T> StringTemplate<T>::subString(const u32& _start, const u32& _size) const
	{
		u32 thisSize = getSize();
		u32 size = min(_size, thisSize - _start);
		if (size == 0)
		{
			return empty;
		}
		StringTemplate<T> out;
		out.resize(size);
		memcpy((void*)out.mData, (void*)(mData + _start), size * sizeof(T));
		return out;
	}

	template<typename T>
	StringTemplate<T> StringTemplate<T>::toLower() const
	{
		StringTemplate<T> out = *this;
		u32 strSize = getSize();
		for (register u32 i = 0; i < strSize; i++)
		{
			out.mData[i] = (out.mData[i] >= 'A' && out.mData[i] <= 'Z') ? out.mData[i] + 32 : out.mData[i];
		}
		return out;
	}

	template<typename T>
	template<typename NumberType>
	NumberType StringTemplate<T>::toNumber(const u32& _base)const
	{
		if (_base < 2 || _base > 16)
		{
			throw Exception("String::number(...) : Base must be between 2 & 16.");
		}
		static const StringTemplate<T> numberCharacters = "0123456789abcdef";
		NumberType out = 0;
		u32 index = 0, iterator = 0, size = getSize();
		if (size > 0)
		{
			if (mData[0] == '-' || mData[0] == '+')
			{
				iterator++;
			}
			while (iterator < size)
			{
				if ((index = numberCharacters.find(mData[iterator])) == notFound)
				{
					return 0;
				}
				else
				{
					out = out * _base + index;
				}
				iterator++;
			}
			if constexpr(Type<NumberType>::isSigned)
			{
				if (mData[0] == '-')
				{
					out = -out;
				}
			}
		}
		return out;
	}

	template<typename T>
	StringTemplate<T> StringTemplate<T>::toUpper() const
	{
		StringTemplate<T> out = *this;
		u32 strSize = getSize();
		for (register u32 i = 0; i < strSize; i++)
		{
			out.mData[i] = (out.mData[i] >= 'a' && out.mData[i] <= 'z') ? out.mData[i] - 32 : out.mData[i];
		}
		return out;
	}

	template<typename T>
	template<typename T2>
	StringTemplate<T>& StringTemplate<T>::operator = (const T2* _str)
	{
		if (_str)
		{
			u32 size = StringTemplate<T2>::stringSize(_str) + 1;
			if (size >= getSize())
			{
				clear();
				mData = new T[size + 1];
			}
			for (register u32 i = 0; i < size; i++)
			{
				mData[i] = T(_str[i]);
			}
		}
		else
		{
			clear();
		}
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator = (const StringTemplate<char>& _other)
	{
		*this = _other.mData;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator = (const StringTemplate<wchar_t>& _other)
	{
		*this = _other.mData;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator = (const StringTemplate<char32_t>& _other)
	{
		*this = _other.mData;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator = (StringTemplate<T>&& _other)
	{
		clear();
		mData = _other.mData;
		_other.mData = nullptr;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T> StringTemplate<T>::operator + (const StringTemplate<T>& _other) const
	{
		StringTemplate<T> out;
		u32 thisSize = getSize();
		u32 otherSize = _other.getSize();
		out.resize(thisSize + otherSize);
		memcpy((void*)out.mData, (void*)mData, thisSize * sizeof(T));
		memcpy((void*)(out.mData + thisSize), (void*)_other.mData, otherSize * sizeof(T));
		return out;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator += (const StringTemplate<T>& _other)
	{
		u32 thisSize = getSize();
		u32 otherSize = _other.getSize();
		resize(thisSize + otherSize);
		memcpy((void*)(mData + thisSize), (void*)_other.mData, otherSize * sizeof(T));
		return *this;
	}

	template<typename T>
	template<typename T2>
	bool StringTemplate<T>::operator == (const T2* _str) const
	{
		u32 thisSize = StringTemplate<T>::stringSize(mData);
		u32 otherSize = StringTemplate<T2>::stringSize(_str);
		if (thisSize != otherSize)
		{
			return false;
		}
		if (thisSize == 0)
		{
			return true;
		}
		for (register u32 i = 0; i < thisSize; i++)
		{
			if (mData[i] != _str[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	template<typename T2>
	FORCE_INLINE bool StringTemplate<T>::operator != (const T2* _str) const
	{
		return !((*this) == _str);
	}

	template<typename T>
	template<typename T2>
	FORCE_INLINE bool StringTemplate<T>::operator == (const StringTemplate<T2>& _str) const
	{
		return *this == _str.mData;
	}

	template<typename T>
	template<typename T2>
	FORCE_INLINE bool StringTemplate<T>::operator != (const StringTemplate<T2>& _str) const
	{
		return !(*this == _str.mData);
	}

	template<typename T>
	FORCE_INLINE T& StringTemplate<T>::operator [](const u32& _index)
	{
		return mData[_index];
	}

	template<typename T>
	FORCE_INLINE T StringTemplate<T>::operator [](const u32& _index) const
	{
		return mData[_index];
	}

	template<typename T>
	u32 StringTemplate<T>::stringSize(const T* _str)
	{
		if (_str)
		{
			register u32 size = 0;
			while (_str[size] != 0)
			{
				size++;
			}
			return size;
		}
		return 0;
	}

	template<typename T, typename T2>
	FORCE_INLINE StringTemplate<T2> operator + (const T* _first, const StringTemplate<T2>& _second)
	{
		static_assert(Type<char>::is<char>() || Type<wchar_t>::is<char>() || Type<char32_t>::is<char>());
		StringTemplate<T2> first = _first;
		return first + _second;
	}

	template<typename T>
	FORCE_INLINE typename StringTemplate<T>::Utf8Character StringTemplate<T>::utf8Encode(u32 _character)
	{
		Utf8Character out;
		out.character[0] = '\0';
		if (_character <= 0x7f)
		{
			out.character[0] = _character;
			out.character[1] = '\0';
		}
		else if (_character <= 0x7ff)
		{
			out.character[0] = 0xC0 | _character >> 6;
			out.character[1] = 0x80 | ((_character) & (~(0xC0)));
			out.character[2] = '\0';
		}
		else if (_character <= 0xffff)
		{
			out.character[0] = 0xE0 | _character >> 12;
			out.character[1] = 0x80 | ((_character >> 6) & (~(0xC0)));
			out.character[2] = 0x80 | ((_character) & (~(0xC0)));
			out.character[3] = '\0';
		}
		else if (_character <= 0x1fffff)
		{
			out.character[0] = 0xF0 | _character >> 18;
			out.character[1] = 0x80 | ((_character >> 12) & (~(0xC0)));
			out.character[2] = 0x80 | ((_character >> 6) & (~(0xC0)));
			out.character[3] = 0x80 | ((_character) & (~(0xC0)));
			out.character[4] = '\0';
		}
		else if (_character <= 0x3FFFFFF)
		{
			out.character[0] = 0xF8 | _character >> 24;
			out.character[1] = 0x80 | ((_character >> 18) & (~(0xC0)));
			out.character[2] = 0x80 | ((_character >> 12) & (~(0xC0)));
			out.character[3] = 0x80 | ((_character >> 6) & (~(0xC0)));
			out.character[4] = 0x80 | ((_character) & (~(0xC0)));
			out.character[5] = '\0';
		}
		else if (_character <= 0x7FFFFFFF)
		{
			out.character[0] = 0xFC | _character >> 30;
			out.character[1] = 0x80 | ((_character >> 24) & (~(0xC0)));
			out.character[2] = 0x80 | ((_character >> 18) & (~(0xC0)));
			out.character[3] = 0x80 | ((_character >> 12) & (~(0xC0)));
			out.character[4] = 0x80 | ((_character >> 6) & (~(0xC0)));
			out.character[4] = 0x80 | ((_character) & (~(0xC0)));
			out.character[5] = '\0';
		}
		return out;
	}

	template<typename T>
	FORCE_INLINE u32 StringTemplate<T>::utf8Decode(const char* _character)
	{
		const unsigned char* _input = (const unsigned char*)_character;
		u32 out = 0;
		if ((_input[0] & 0xFE) == 0xFC)
		{
			out = (_input[0] & (~0xFE)) << 30;
			out += (_input[1] & (~0xC0)) << 24;
			out += (_input[2] & (~0xC0)) << 18;
			out += (_input[3] & (~0xC0)) << 12;
			out += (_input[4] & (~0xC0)) << 6;
			out += (_input[5] & (~0xC0));
		}
		else if ((_input[0] & 0xFC) == 0xF8)
		{
			out = (_input[0] & (~0xFC)) << 24;
			out += (_input[1] & (~0xC0)) << 18;
			out += (_input[2] & (~0xC0)) << 12;
			out += (_input[3] & (~0xC0)) << 6;
			out += (_input[4] & (~0xC0));
		}
		else if ((_input[0] & 0xF8) == 0xF0)
		{
			out = (_input[0] & (~0xF8)) << 18;
			out += (_input[1] & (~0xC0)) << 12;
			out += (_input[2] & (~0xC0)) << 6;
			out += (_input[3] & (~0xC0));
		}
		else if ((_input[0] & 0xF0) == 0xE0)
		{
			out = (_input[0] & (~0xF0)) << 12;
			out += (_input[1] & (~0xC0)) << 6;
			out += (_input[2] & (~0xC0));
		}
		else if ((_input[0] & 0xE0) == 0xC0)
		{
			out = (_input[0] & (~0xE0)) << 6;
			out += (_input[1] & (~0xC0));
		}
		else
		{
			out = _input[0];
		}

		return out;
	}

	template<typename T>
	FORCE_INLINE typename StringTemplate<T>::Utf16Character StringTemplate<T>::utf16Encode(u32 _character)
	{
	    Utf16Character out;
		out.character[0] = L'\0';
		if (_character < 0x10000)
		{
			out.character[0] = _character;
			out.character[1] = L'\0';
		}
		else if (_character >= 0x10000 && _character <= 0x10FFFF)
		{
			_character = _character - 0x10000;
			out.character[0] = 0xD800 | (_character >> 10);
			out.character[1] = 0xDC00 | (_character & 0x03FF);
			out.character[2] = L'\0';
		}
		return out;
	}

	template<typename T>
	FORCE_INLINE u32 StringTemplate<T>::utf16Decode(const wchar_t* _character)
	{
		const u16 *_input = (const u16 *)_character;
		u32 out = 0;
		if (((_input[0] & 0xFC00) == 0xD800) && ((_input[1] & 0xFC00) == 0xDC00))
		{
			out = 0x10000;
			out += (_input[0] & 0x3FF) << 10;
			out += (_input[1] & 0x3FF);
		}
		else
		{
			out = _input[0];
		}
		return out;
	}

	template<>
	template<>
	float StringTemplate<char>::toNumber<float>(const u32& _base) const;

	template<>
	template<>
	double StringTemplate<char>::toNumber<double>(const u32& _base) const;

	template<>
	template<>
	long double StringTemplate<char>::toNumber<long double>(const u32& _base) const;

	template<>
	template<>
	bool StringTemplate<char>::operator == (const char* _str) const;

	template<>
	template<>
	bool StringTemplate<wchar_t>::operator == (const wchar_t* _str) const;

	template<>
	template<>
	bool StringTemplate<char32_t>::operator == (const char32_t* _str) const;

	template<>
	template<>
	StringTemplate<char>& StringTemplate<char>::operator = <char>(const char* _str);

	template<>
	template<>
	StringTemplate<wchar_t>& StringTemplate<wchar_t>::operator = <wchar_t>(const wchar_t* _str);

	template<>
	template<>
	StringTemplate<char32_t>& StringTemplate<char32_t>::operator = <char32_t>(const char32_t* _str);

	template<>
	template<>
	float StringTemplate<wchar_t>::toNumber<float>(const u32& _base) const;

	template<>
	template<>
	double StringTemplate<wchar_t>::toNumber<double>(const u32& _base) const;

	template<>
	template<>
	long double StringTemplate<wchar_t>::toNumber<long double>(const u32& _base) const;

	template<>
	template<>
	float StringTemplate<char32_t>::toNumber<float>(const u32& _base) const;

	template<>
	template<>
	double StringTemplate<char32_t>::toNumber<double>(const u32& _base) const;

	template<>
	template<>
	long double StringTemplate<char32_t>::toNumber<long double>(const u32& _base) const;
}

