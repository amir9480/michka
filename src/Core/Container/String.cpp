#include "String.h"
#include "../Helpers.h"
#include "../Memory/Memory.h"
#include <utility>
#include <memory>

namespace Michka
{
	template<>
	template<>
	float StringTemplate<char>::toNumber<float>(const u32& _base) const
	{
		float result;
		sscanf(mData, "%g", &result);
		return result;
	}

	template<>
	template<>
	double StringTemplate<char>::toNumber<double>(const u32& _base) const
	{
		double result;
		sscanf(mData, "%lg", &result);
		return result;
	}

	template<>
	template<>
	long double StringTemplate<char>::toNumber<long double>(const u32& _base) const
	{
		long double result;
		sscanf(mData, "%Lg", &result);
		return result;
	}


	template<>
	template<>
	bool StringTemplate<char>::operator == (const char* _str) const
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
		return memcmp(mData, _str, sizeof(char) * thisSize) == 0;
	}

	template<>
	template<>
	bool StringTemplate<wchar_t>::operator == (const wchar_t* _str) const
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
		return memcmp(mData, _str, sizeof(wchar_t) * thisSize) == 0;
	}

	template<>
	template<>
	bool StringTemplate<char32_t>::operator == (const char32_t* _str) const
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
		return memcmp(mData, _str, sizeof(char32_t) * thisSize) == 0;
	}

	template<>
	template<>
	StringTemplate<char>& StringTemplate<char>::operator = <char>(const char* _str)
	{
		if (_str)
		{
			u32 size = stringSize(_str) + 1;
			if (size >= getSize())
			{
				clear();
				mData = new char[size];
			}
			memcpy(mData, _str, size * sizeof(char));
		}
		else
		{
			clear();
		}
		return *this;
	}

	template<>
	template<>
	StringTemplate<wchar_t>& StringTemplate<wchar_t>::operator = <wchar_t>(const wchar_t* _str)
	{
		if (_str)
		{
			u32 size = stringSize(_str) + 1;
			if (size >= getSize())
			{
				clear();
				mData = new wchar_t[size];
			}
			memcpy(mData, _str, size * sizeof(wchar_t));
		}
		else
		{
			clear();
		}
		return *this;
	}

	template<>
	template<>
	StringTemplate<char32_t>& StringTemplate<char32_t>::operator = <char32_t>(const char32_t* _str)
	{
		if (_str)
		{
			u32 size = stringSize(_str) + 1;
			if (size >= getSize())
			{
				clear();
				mData = new char32_t[size];
			}
			memcpy(mData, _str, size * sizeof(char32_t));
		}
		else
		{
			clear();
		}
		return *this;
	}


	template<>
	template<>
	float StringTemplate<wchar_t>::toNumber<float>(const u32& _base) const
	{
		return StringTemplate<char>(mData).toNumber<float>();
	}

	template<>
	template<>
	double StringTemplate<wchar_t>::toNumber<double>(const u32& _base) const
	{
		return StringTemplate<char>(mData).toNumber<double>();
	}

	template<>
	template<>
	long double StringTemplate<wchar_t>::toNumber<long double>(const u32& _base) const
	{
		return StringTemplate<char>(mData).toNumber<long double>();
	}

	template<>
	template<>
	float StringTemplate<char32_t>::toNumber<float>(const u32& _base) const
	{
		return StringTemplate<char>(mData).toNumber<float>();
	}

	template<>
	template<>
	double StringTemplate<char32_t>::toNumber<double>(const u32& _base) const
	{
		return StringTemplate<char>(mData).toNumber<double>();
	}

	template<>
	template<>
	long double StringTemplate<char32_t>::toNumber<long double>(const u32& _base) const
	{
		return StringTemplate<char>(mData).toNumber<long double>();
	}

	template<>
	StringTemplate<char> StringTemplate<char>::fromUtf8(const char* _string)
	{
		return StringTemplate<char>(_string);
	}

	template<>
	StringTemplate<wchar_t> StringTemplate<wchar_t>::fromUtf8(const char* _string)
	{
		StringTemplate<wchar_t> out;
		u32 strLength = StringTemplate<char>::stringLength(_string);
		out.resize(strLength * 2);
		u32 iterator = 0, encodedUtf16Iterator = 0;
		for (u32 i = 0; i < strLength; i++)
		{
			u32 character = utf8Decode(_string + iterator);
			Utf16Character encodedCharacter = utf16Encode(character);
			u32 encodedCharacterSize = stringSize(encodedCharacter.character);
			memcpy((void*)&out[encodedUtf16Iterator], (void*)encodedCharacter.character, encodedCharacterSize * sizeof(wchar_t));
			encodedUtf16Iterator += encodedCharacterSize;

			if (character <= 0x7f)
			{
				iterator += 1;
			}
			else if (character <= 0x7ff)
			{
				iterator += 2;
			}
			else if (character <= 0xffff)
			{
				iterator += 3;
			}
			else if (character <= 0x1fffff)
			{
				iterator += 4;
			}
			else if (character <= 0x3ffffff)
			{
				iterator += 5;
			}
			else if (character <= 0x7fffffff)
			{
				iterator += 6;
			}
		}
		return out;
	}

	template<>
	StringTemplate<char32_t> StringTemplate<char32_t>::fromUtf8(const char* _string)
	{
		StringTemplate<char32_t> out;
		u32 strLength = StringTemplate<char>::stringLength(_string);
		out.resize(strLength);
		u32 iterator = 0;
		for (u32 i = 0; i < strLength; i++)
		{
			u32 character = utf8Decode(_string + iterator);
			out[i] = character;

			if (character <= 0x7f)
			{
				iterator += 1;
			}
			else if (character <= 0x7ff)
			{
				iterator += 2;
			}
			else if (character <= 0xffff)
			{
				iterator += 3;
			}
			else if (character <= 0x1fffff)
			{
				iterator += 4;
			}
			else if (character <= 0x3ffffff)
			{
				iterator += 5;
			}
			else if (character <= 0x7fffffff)
			{
				iterator += 6;
			}
		}
		return out;
	}

	template<>
	StringTemplate<char> StringTemplate<char>::fromUtf16(const wchar_t* _string)
	{
		return StringTemplate<wchar_t>(_string).toUtf8();
	}

	template<>
	StringTemplate<wchar_t> StringTemplate<wchar_t>::fromUtf16(const wchar_t* _string)
	{
		return StringTemplate<wchar_t>(_string);
	}

	template<>
	StringTemplate<char32_t> StringTemplate<char32_t>::fromUtf16(const wchar_t* _string)
	{
		StringTemplate<char32_t> out;
		u32 strLength = StringTemplate<wchar_t>::stringLength(_string);
		out.resize(strLength);
		u32 iterator = 0;
		for (u32 i = 0; i < strLength; i++)
		{
			u32 character = utf16Decode(_string + iterator);
			out[i] = character;
			out[i + 1] = 0;

			if (character >= 0x10000)
			{
				iterator += 2;
			}
			else
			{
				iterator++;
			}
		}
		return out;
	}

	template<>
	StringTemplate<char> StringTemplate<char>::fromUtf32(const char32_t* _string)
	{
		return StringTemplate<char32_t>(_string).toUtf8();
	}

	template<>
	StringTemplate<wchar_t> StringTemplate<wchar_t>::fromUtf32(const char32_t* _string)
	{
		return StringTemplate<char32_t>(_string).toUtf16();
	}

	template<>
	StringTemplate<char32_t> StringTemplate<char32_t>::fromUtf32(const char32_t* _string)
	{
		return StringTemplate<char32_t>(_string);
	}

	template<>
	StringTemplate<char> StringTemplate<char>::toUtf8()
	{
		return StringTemplate<char>(*this);
	}

	template<>
	StringTemplate<char> StringTemplate<wchar_t>::toUtf8()
	{
		StringTemplate<char> out;
		u32 thisLength = getLength();
		out.resize(thisLength * 6);
		u32 iterator = 0, encodedUtf8Iterator = 0;
		for (u32 i = 0; i < thisLength; i++)
		{
			u32 character = utf16Decode(mData + iterator);
			Utf8Character encoedCharacter = utf8Encode(character);
			u32 encoedCharacterSize = StringTemplate<char>::stringSize(encoedCharacter.character);
			memcpy(&out[encodedUtf8Iterator], encoedCharacter.character, encoedCharacterSize);
			encodedUtf8Iterator += encoedCharacterSize;
			if (character >= 0x10000)
			{
				iterator+=2;
			}
			else
			{
				iterator++;
			}
		}
		return out;
	}

	template<>
	StringTemplate<char> StringTemplate<char32_t>::toUtf8()
	{
		StringTemplate<char> out;
		u32 thisLength = getLength();
		out.resize(thisLength * 6);
		u32 iterator = 0;
		for (u32 i = 0; i < thisLength; i++)
		{
			u32 character = mData[i];
			Utf8Character encoedCharacter = utf8Encode(character);
			u32 encoedCharacterSize = StringTemplate<char>::stringSize(encoedCharacter.character);
			memcpy(&out[iterator], encoedCharacter.character, encoedCharacterSize);
			iterator += encoedCharacterSize;
		}
		return out;
	}

	template<>
	StringTemplate<wchar_t> StringTemplate<char>::toUtf16()
	{
		return StringTemplate<wchar_t>::fromUtf8(mData);
	}

	template<>
	StringTemplate<wchar_t> StringTemplate<wchar_t>::toUtf16()
	{
		return StringTemplate<wchar_t>(*this);
	}

	template<>
	StringTemplate<wchar_t> StringTemplate<char32_t>::toUtf16()
	{
		StringTemplate<wchar_t> out;
		u32 stringLength = getLength();
		out.resize(stringLength * 2);
		u32 iterator = 0;
		for (u32 i = 0; i < stringLength; i++)
		{
			u32 character = mData[i];
			Utf16Character encodedCharacter = utf16Encode(character);
			u32 encodedCharacterSize = StringTemplate<wchar_t>::stringSize(encodedCharacter.character);
			memcpy((void*)&out[iterator], (void*)encodedCharacter.character, encodedCharacterSize * sizeof(wchar_t));
			iterator += encodedCharacterSize;
		}
		return out;
	}

	template<>
	StringTemplate<char32_t> StringTemplate<char>::toUtf32()
	{
		return StringTemplate<char32_t>::fromUtf8(mData);
	}

	template<>
	StringTemplate<char32_t> StringTemplate<wchar_t>::toUtf32()
	{
		return StringTemplate<char32_t>::fromUtf16(mData);
	}

	template<>
	StringTemplate<char32_t> StringTemplate<char32_t>::toUtf32()
	{
		return *this;
	}

	template<>
	u32 StringTemplate<char>::stringLength(const char* _str)
	{
		u32 out = 0, iterator = 0;
		u32 strSize = stringSize(_str);
		while (iterator < strSize)
		{
			u32 character = utf8Decode(_str + iterator);

			if (character <= 0x7f)
			{
				iterator += 1;
			}
			else if (character <= 0x7ff)
			{
				iterator += 2;
			}
			else if (character <= 0xffff)
			{
				iterator += 3;
			}
			else if (character <= 0x1fffff)
			{
				iterator += 4;
			}
			else if (character <= 0x3ffffff)
			{
				iterator += 5;
			}
			else if (character <= 0x7fffffff)
			{
				iterator += 6;
			}
			out++;
		}
		return out;
	}

	template<>
	u32 StringTemplate<wchar_t>::stringLength(const wchar_t* _str)
	{
		u32 out = 0, iterator = 0;
		u32 strSize = stringSize(_str);
		while (iterator < strSize)
		{
			u32 character = utf16Decode(_str + iterator);

			if (character < 0x10000)
			{
				iterator += 1;
			}
			else
			{
				iterator += 2;
			}
			out++;
		}
		return out;
	}

	template<>
	u32 StringTemplate<char32_t>::stringLength(const char32_t* _str)
	{
		return stringSize(_str);
	}
}

