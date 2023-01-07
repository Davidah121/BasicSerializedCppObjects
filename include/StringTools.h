#pragma once
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>

class StringTools
{
public:

	/**
	 * @brief Converts any string to a std::wstring
	 * 
	 * @tparam T 
	 * @param text 
	 * @return std::wstring 
	 */
	template<typename T>
	static std::wstring toWideString(std::basic_string<T> text)
	{
		std::wstring finalText;
		for (size_t i = 0; i < text.size(); i++)
		{
			finalText += (wchar_t)text[i];
		}

		return finalText;
	}

	/**
	 * @brief Converts any string to a std::string
	 * 
	 * @tparam T 
	 * @param text 
	 * @return std::string 
	 */
	template<typename T>
	static std::string toCString(std::basic_string<T> text)
	{
		std::string finalText;

		for (size_t i = 0; i < text.size(); i++)
		{
			finalText += (char)text[i];
		}

		return finalText;
	}

	/**
	 * @brief Converts a wide string to a valid UTF8 string
	 * 
	 * @param s 
	 * @return std::string 
	 */
	static std::string toUTF8String(std::wstring s)
	{
		std::string finalText;

		for (wchar_t& c : s)
		{
			std::vector<unsigned char> values = StringTools::toUTF8(c);
			for(unsigned char& v : values)
			{
				finalText += (char)v;
			}
		}

		return finalText;
	}

	/**
	 * @brief Converts any string to lowercase
	 * 
	 * @tparam T 
	 * @param text 
	 * @return std::basic_string<T>
	 */
	template<typename T>
	static std::basic_string<T> toLowercase(std::basic_string<T> text)
	{
		std::basic_string<T> finalText;
		for (size_t i = 0; i < text.size(); i++)
		{
			finalText += tolower(text[i]);
		}

		return finalText;
	}

	/**
	 * @brief Converts any string to uppercase
	 * 
	 * @tparam T 
	 * @param text 
	 * @return std::basic_string<T>
	 */
	template<typename T>
	static std::basic_string<T> toUppercase(std::basic_string<T> text)
	{
		std::basic_string<T> finalText = "";
		for (size_t i = 0; i < text.size(); i++)
		{
			finalText += toupper(text[i]);
		}

		return finalText;
	}

	/**
	 * @brief Converts a character to a valid UTF8 character.
	 * 		May use more than one byte for one UTF8 character.
	 * 
	 * @param c 
	 * @return std::vector<unsigned char> 
	 */
	static std::vector<unsigned char> toUTF8(int c);

	/**
	 * @brief Converts the bytes in a valid UTF8 character to an integer representation.
	 * 
	 * @param utf8Char 
	 * @return int 
	 */
	static int utf8ToChar(std::vector<unsigned char> utf8Char);

	/**
	 * @brief Converts the bytes in a std::string or any utf8 compliant string into
	 * 		a set of integers for easier parsing.
	 * 
	 * @param validUTF8String 
	 * @return std::vector<int> 
	 */
	static std::vector<int> utf8ToIntString(std::string validUTF8String);

	/**
	 * @brief Converts the bytes in a std::wstring into
	 * 		a set of integers for easier parsing.
	 * @param str 
	 * @return std::vector<int> 
	 */
	static std::vector<int> wideStringToIntString(std::wstring str);

	/**
	 * @brief Converts a base64 character into a number. Properly handles the url safe cases as well.
	 * 
	 * @param b 
	 * @return int 
	 */
	static int base64CharToNum(unsigned char b);

	/**
	 * @brief Converts a set of bytes into base64 encoding.
	 * 
	 * @param bytes 
	 * @param urlSafe 
	 * 		Replaces select values with others that can be put into a url.
	 * 			Specifically replaces '+' and '/'
	 * @return std::string 
	 */
	static std::string base64Encode(std::vector<unsigned char> bytes, bool urlSafe);

	/**
	 * @brief Converts a set of bytes into base64 encoding.
	 * 
	 * @param bytes 
	 * @param size
	 * @param urlSafe 
	 * 		Replaces select values with others that can be put into a url.
	 * 			Specifically replaces '+' and '/'
	 * @return std::string 
	 */
	static std::string base64Encode(unsigned char* bytes, size_t size, bool urlSafe);

	/**
	 * @brief Converts a base64 encoded string or set of bytes back into the original byte data.
	 * 
	 * @param bytes 
	 * @return std::vector<unsigned char> 
	 */
	static std::vector<unsigned char> base64Decode(std::vector<unsigned char> bytes);

	/**
	 * @brief Converts a base64 encoded string or set of bytes back into the original byte data.
	 * 
	 * @param bytes 
	 * @return std::vector<unsigned char> 
	 */
	static std::vector<unsigned char> base64Decode(std::string bytes);

	/**
	 * @brief Converts a base64 encoded string or set of bytes back into the original byte data.
	 * 
	 * @param bytes 
	 * @param size
	 * @return std::vector<unsigned char> 
	 */
	static std::vector<unsigned char> base64Decode(unsigned char* bytes, size_t size);

	/**
	 * @brief Returns if the strings are equal to each other ignoring the case of the character.
	 * 
	 * @tparam T 
	 * @param a 
	 * @param b 
	 * @return true 
	 * @return false 
	 */
	template<typename T>
	static bool equalsIgnoreCase(std::basic_string<T> a, std::basic_string<T> b)
	{
		if(a.size() == b.size())
		{
			for(size_t i=0; i<a.size(); i++)
			{
				if( toupper(a[i]) != toupper(b[i]))
					return false;
			}
		}
		else
		{
			return false;
		}
		
		return true;
	}

	/**
	 * @brief Returns if the character is apart of the alphabet or is a number.
	 * 		Special characters like '-' and '_' can be added to the check.
	 * 		Only checks in the ASCII space.
	 * 
	 * @param v 
	 * @param underScoreAllowed 
	 * 		Default is false
	 * @param dashAllowed 
	 * 		Default is false
	 * @return true 
	 * @return false 
	 */
	static bool isAlphaNumerial(char v, bool underScoreAllowed = false, bool dashAllowed = false);

	/**
	 * @brief Returns if the number is valid character in the ASCII space.
	 * 
	 * @param v 
	 * @return true 
	 * @return false 
	 */
	static bool isValidChar(int v);
	
	/**
	 * @brief Converts the base10 value to its base16 value represented as a character.
	 * 		Ex:
	 * 		0 -> '0'
	 * 		2 -> '2'
	 * 		10 -> 'A'
	 * 		15 -> 'F'
	 * @param v 
	 * 		Valid values are from [0,15]
	 * @return char 
	 */
	static char base10ToBase16(char v);

	/**
	 * @brief Converts the base16 value represented as a character to its base10 value represented as an integer.
	 * 		Ex:
	 * 		'0' -> 0
	 * 		'2' -> 2
	 * 		'A' -> 10
	 * 		'F' -> 15
	 * @param v 
	 * 		Valid values are from ['0', '9'] and ['A', 'F']
	 * @return int 
	 * 		Returns -1 if unsuccessful
	 */
	static int base16ToBase10(char v);

	/**
	 * @brief Converts the value to a Hexidecimal string.
	 * 
	 * @tparam T 
	 * @param value 
	 * @return char* 
	 */
	template<class T>
	static std::string toHexString(T value)
	{
		int size = sizeof(T) * 2;

		char* hexString = new char[size+1+2];
		int maxVal = 4*sizeof(T) - 4;

		hexString[0] = '0';
		hexString[1] = 'x';

		unsigned long long convertedValue = (unsigned long long)value;
		
		for(size_t i=0; i<size; i++)
		{
			hexString[2 + size-i-1] = base10ToBase16((convertedValue >> (i*4)) & 0xF);
		}

		hexString[size] = '\0';

		std::string retString = hexString;
		delete[] hexString;
		
		return retString;
	}

	/**
	 * @brief Converts a string into a size_t. Assumes that the value is unsigned
	 * 		and fits into a size_t.
	 * 
	 * @param v 
	 * @return size_t 
	 */
	static size_t fromHexString(std::string v)
	{
		//check for 0x at the front
		size_t result = 0;
		if(v.size() <= 0)
			return -1;

		for(size_t k=0; k<v.size(); k++)
		{
			if(v[k] == 'x')
			{
				if(v[k-1] == 0)
				{
					result = 0;
				}
			}
			else
			{
				int temp = base16ToBase10(v[k]);
				if(temp != -1)
				{
					result <<= 4;
					result += temp;
				}
				else
				{
					return -1;
				}
			}
		}
		
		return result;
	}
	
	/**
	 * @brief Splits a string using a single character deliminator.
	 * 
	 * @param s 
	 * @param delim 
	 * @param removeEmpty 
	 * 		Whether to keep empty splits or remove them.
	 * 		Default is true.
	 * @return std::vector<std::string> 
	 */
	static std::vector<std::string> splitString(std::string s, const char delim, bool removeEmpty=true);

	/**
	 * @brief Splits a string using a string as the deliminator.
	 * 
	 * @param s 
	 * @param delim 
	 * @param removeEmpty 
	 * 		Whether to keep empty splits or remove them.
	 * 		Default is true.
	 * @return std::vector<std::string> 
	 */
	static std::vector<std::string> splitString(std::string s, std::string delim, bool removeEmpty=true);

	/**
	 * @brief Splits a string using multiple single character deliminators.
	 * 
	 * @param s 
	 * @param delim 
	 * 		Each character in the string is a separate deliminator
	 * @param removeEmpty 
	 * 		Whether to keep empty splits or remove them.
	 * 		Default is true.
	 * @return std::vector<std::string> 
	 */
	static std::vector<std::string> splitStringMultipleDeliminators(std::string s, std::string delim, bool removeEmpty=true);
	
	/**
	 * @brief Splits a string using a single character deliminator.
	 * 
	 * @param s 
	 * @param delim 
	 * @param removeEmpty 
	 * 		Whether to keep empty splits or remove them.
	 * 		Default is true.
	 * @return std::vector<std::wstring> 
	 */
	static std::vector<std::wstring> splitString(std::wstring s, const wchar_t delim, bool removeEmpty=true);

	/**
	 * @brief Splits a string using a string as the deliminator.
	 * 
	 * @param s 
	 * @param delim 
	 * @param removeEmpty 
	 * 		Whether to keep empty splits or remove them.
	 * 		Default is true.
	 * @return std::vector<std::wstring> 
	 */
	static std::vector<std::wstring> splitString(std::wstring s, std::wstring delim, bool removeEmpty=true);

	/**
	 * @brief Splits a string using multiple single character deliminators.
	 * 
	 * @param s 
	 * @param delim 
	 * @param removeEmpty 
	 * 		Whether to keep empty splits or remove them.
	 * 		Default is true.
	 * @return std::vector<std::wstring> 
	 */
	static std::vector<std::wstring> splitStringMultipleDeliminators(std::wstring s, std::wstring delim, bool removeEmpty=true);

	/**
	 * @brief Removes all white space from the string.
	 * 		There is an option to remove tabs as well.
	 * 
	 * @param originalStr 
	 * @param removeTabs 
	 * @param onlyLeadingAndTrailing
	 * 		Only removes the empty white space at the beginning and ending.
	 * 		Keeps whitespace between data.
	 * @return std::string 
	 */
	static std::string removeWhitespace(std::string originalStr, bool removeTabs = false, bool onlyLeadingAndTrailing = false);

	/**
	 * @brief Removes all white space from the string.
	 * 		There is an option to remove tabs as well.
	 * 
	 * @param originalStr 
	 * @param removeTabs 
	 * @param onlyLeadingAndTrailing
	 * 		Only removes the empty white space at the beginning and ending.
	 * 		Keeps whitespace between data.
	 * @return std::wstring 
	 */
	static std::wstring removeWhitespace(std::wstring originalStr, bool removeTabs = false, bool onlyLeadingAndTrailing = false);
	
	/**
	 * @brief Converts a string into an integer.
	 * 
	 * @param s 
	 * @return int 
	 */
	static int toInt(std::string s);

	/**
	 * @brief Converts a string into an integer.
	 * 
	 * @param s 
	 * @return int 
	 */
	static int toInt(std::wstring s);

	/**
	 * @brief Converts a string into a long.
	 * 
	 * @param s 
	 * @return long 
	 */
	static long toLong(std::string s);

	/**
	 * @brief Converts a string into a long.
	 * 
	 * @param s 
	 * @return long 
	 */
	static long toLong(std::wstring s);

	/**
	 * @brief Converts a string into a double.
	 * 
	 * @param s 
	 * @return double 
	 */
	static double toDouble(std::string s);

	/**
	 * @brief Converts a string into a double.
	 * 
	 * @param s 
	 * @return double 
	 */
	static double toDouble(std::wstring s);

	/**
	 * @brief Converts a string into a float.
	 * 
	 * @param s 
	 * @return float 
	 */
	static float toFloat(std::string s);

	/**
	 * @brief Converts a string into a float.
	 * 
	 * @param s 
	 * @return float 
	 */
	static float toFloat(std::wstring s);

	/**
	 * @brief Converts the value into a string
	 * 
	 * @param k 
	 * @return std::string 
	 */
	static std::string toString(int k);
	static std::string toString(long k);
	static std::string toString(unsigned int k);
	static std::string toString(unsigned long k);
	static std::string toString(long long k);
	static std::string toString(unsigned long long k);
	static std::string toString(float k);
	static std::string toString(double k);
	

private:
};
