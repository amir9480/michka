#include "String.h"
#include "Helpers.h"

namespace Mishka
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
	bool StringTemplate<char>::operator==(const char* _str) const
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
	bool StringTemplate<wchar_t>::operator==(const wchar_t* _str) const
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
	bool StringTemplate<char32_t>::operator==(const char32_t* _str) const
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
	StringTemplate<char>& StringTemplate<char>::operator=<char>(const char* _str)
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
	StringTemplate<wchar_t>& StringTemplate<wchar_t>::operator=<wchar_t>(const wchar_t* _str)
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
	StringTemplate<char32_t>& StringTemplate<char32_t>::operator=<char32_t>(const char32_t* _str)
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
}

