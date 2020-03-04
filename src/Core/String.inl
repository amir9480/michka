#include "String.h"
#include "Helpers.h"

namespace Mishka
{
	template<typename T>
	const StringTemplate<T> StringTemplate<T>::empty;

	template<typename T>
	const u32 StringTemplate<T>::notFound = 0xffffffff;

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
		*this = _other.mData;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>::StringTemplate(const StringTemplate<wchar_t>& _other)
	{
		*this = _other.mData;
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
	const T* StringTemplate<T>::cstr() const
	{
		static const T emptyString[2] = { 0 };
		if (mData)
		{
			return mData;
		}
		return emptyString;
	}

	template<typename T>
	FORCE_INLINE u32 StringTemplate<T>::find(const T& _character, const u32& _offset) const
	{
		if (mData)
		{
			T* pointer = static_cast<T*>(memchr((void*)(mData + _offset), T(_character), getSize() * sizeof(T)));
			if (pointer)
			{
				return u32(pointer - mData);
			}
		}
		return notFound;
	}

	template<typename T>
	u32 StringTemplate<T>::findFromRight(const T& _character, const u32& _offset) const
	{
		u32 offset =  _offset == 0xffffffff ? getSize() : _offset;
		u32 result = notFound;
		if (mData)
		{
			while (T* pointer = (T*)memchr((void*)(mData + (result != notFound ? result + 1 : 0)), T(_character), getSize() * sizeof(T)))
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
			while ((offset = find(_string[0], offset)) != notFound && getSize() - offset >= _string.getSize())
			{
				for (u32 i = 0; i <= _string.getSize(); i++)
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
	u32 StringTemplate<T>::findFromRight(const StringTemplate<T>& _string, const u32& _offset) const
	{
		if (_string.isNotEmpty() && this->isNotEmpty())
		{
			u32 offset =  (_offset == 0xffffffff ? getSize() : _offset) - _string.getSize();
			while ((offset = findFromRight(_string[0], offset)) != notFound)
			{
				for (u32 i = 0; i <= _string.getSize(); i++)
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
	template<typename TYPE>
	StringTemplate<T> StringTemplate<T>::number(TYPE _number, const u8& _base)
	{
		MISHKA_ASSERT(_base >= 2 && _base <= 16, "String::number(...): Base must be between 2 & 16.");
		static const StringTemplate<T> numberCharacters = "0123456789abcdef";
		StringTemplate<T> out;
		out.resize((sizeof(TYPE) * 8) + 1);
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
	StringTemplate<T>& StringTemplate<T>::reverse()
	{
		// TODO: Support utf8 / utf16
		u32 size = getSize();
		u32 sizeOn2 = getSize() / 2;
		for (u32 i = 0; i < sizeOn2; i++)
		{
			swap(mData[i], mData[size - 1 - i]);
		}
		return *this;
	}

	template<typename T>
	StringTemplate<T>& StringTemplate<T>::resize(u32 _newSize)
	{
		T* old = nullptr;
		if (mData)
		{
			old = mData;
		}
		mData = new T[_newSize + 1];
		if (old)
		{
			u32 size = stringSize(old);
			size = _newSize < size ? _newSize : size;
			memcpy(mData, old, size * sizeof(T));
			mData[size] = 0;
			delete[] old;
		}
		else
		{
			memset(mData, 0, (_newSize + 1) * sizeof(T));
		}
		return *this;
	}

	template<typename T>
	template<typename TYPE>
	TYPE StringTemplate<T>::toNumber(const u32& _base)const
	{
		MISHKA_ASSERT(_base >= 2 && _base <= 16, "String::number(...): Base must be between 2 & 16.");
		static const StringTemplate<T> numberCharacters = "0123456789abcdef";
		TYPE out = 0;
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
				} else {
					out = out * _base + index;
				}
				iterator++;
			}
			if constexpr(std::is_signed<TYPE>::value)
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
	template<typename T2>
	StringTemplate<T>& StringTemplate<T>::operator=(const T2* _str)
	{
		if (_str)
		{
			u32 size = stringSize(_str) + 1;
			if (size >= getSize())
			{
				clear();
				mData = new T[size];
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
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator=(const StringTemplate<char>& _other)
	{
		*this = _other.mData;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator=(const StringTemplate<wchar_t>& _other)
	{
		*this = _other.mData;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator=(const StringTemplate<char32_t>& _other)
	{
		*this = _other.mData;
		return *this;
	}

	template<typename T>
	FORCE_INLINE StringTemplate<T>& StringTemplate<T>::operator=(StringTemplate<T>&& _other)
	{
		clear();
		mData = _other.mData;
		_other.mData = nullptr;
		return *this;
	}

	template<typename T>
	template<typename T2>
	bool StringTemplate<T>::operator==(const T2* _str) const
	{
		u32 thisSize = stringSize(mData);
		u32 otherSize = stringSize(_str);
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
	FORCE_INLINE bool StringTemplate<T>::operator!=(const T2* _str) const
	{
		return !((*this) == _str);
	}

	template<typename T>
	template<typename T2>
	FORCE_INLINE bool StringTemplate<T>::operator==(const StringTemplate<T2>& _str) const
	{
		return *this == _str.mData;
	}

	template<typename T>
	template<typename T2>
	FORCE_INLINE bool StringTemplate<T>::operator!=(const StringTemplate<T2>& _str) const
	{
		return !(*this == _str.mData);
	}

	template<typename T>
	FORCE_INLINE T& StringTemplate<T>::operator[](const u32& _index)
	{
#		if(MISHKA_DEBUG)
			MISHKA_ASSERT(_index < getSize(), "StringTemplate<T>::operator[]. Index must be lower that string size.");
#		endif
		return mData[_index];
	}

	template<typename T>
	FORCE_INLINE T StringTemplate<T>::operator[](const u32& _index) const
	{
#		if(MISHKA_DEBUG)
			MISHKA_ASSERT(_index < getSize(), "StringTemplate<T>::operator[]. Index must be lower that string size.");
#		endif
		return mData[_index];
	}

	template<typename T>
	FORCE_INLINE u32 stringSize<T>(const T* _str)
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
	bool StringTemplate<char>::operator==(const char* _str) const;

	template<>
	template<>
	bool StringTemplate<wchar_t>::operator==(const wchar_t* _str) const;

	template<>
	template<>
	bool StringTemplate<char32_t>::operator==(const char32_t* _str) const;

	template<>
	template<>
	StringTemplate<char>& StringTemplate<char>::operator=<char>(const char* _str);

	template<>
	template<>
	StringTemplate<wchar_t>& StringTemplate<wchar_t>::operator=<wchar_t>(const wchar_t* _str);

	template<>
	template<>
	StringTemplate<char32_t>& StringTemplate<char32_t>::operator=<char32_t>(const char32_t* _str);

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
