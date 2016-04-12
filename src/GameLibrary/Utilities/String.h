
#pragma once

#ifndef _GAMELIBRARY_STRING_H
#define _GAMELIBRARY_STRING_H

#include <string>
#include <type_traits>
#include <ostream>
#include <sstream>
#include <codecvt>
#include <cctype>
#include <vector>
#include <iomanip>

#ifdef __OBJC__
	#import <Foundation/Foundation.h>
#endif

#ifndef _STRING_STANDALONE
namespace GameLibrary
{
#endif
	template<typename _STRING_TYPE>
	class BasicString;
	
	#define NULLCHAR 0
	#define _STRING_SAME_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE) typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)), _OTHER_STRING_TYPE>::type
	#define _STRING_DIFF_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE) typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)), _OTHER_STRING_TYPE>::type
	#define _STRING_ISBOOL(_STRING_TYPE, _OTHER_TYPE) typename std::enable_if<(\
		!std::is_same<_STRING_TYPE,_OTHER_TYPE>::value\
		&& std::is_same<_OTHER_TYPE,bool>::value), _OTHER_TYPE>::type
	#ifdef __OBJC__
		#define _STRING_NONCHAR_NUMBER(_STRING_TYPE, _NUM_TYPE) typename std::enable_if<\
			(std::is_arithmetic<_NUM_TYPE>::value || std::is_enum<_NUM_TYPE>::value)\
			&& !std::is_pointer<_NUM_TYPE>::value\
			&& !std::is_same<_NUM_TYPE, _STRING_TYPE>::value\
			&& !std::is_same<_NUM_TYPE, bool>::value\
			&& !std::is_same<_NUM_TYPE, char>::value\
			&& !std::is_same<_NUM_TYPE, char16_t>::value\
			&& !std::is_same<_NUM_TYPE, char32_t>::value\
			&& !std::is_same<_NUM_TYPE, wchar_t>::value\
			&& !std::is_same<_NUM_TYPE, unichar>::value, _NUM_TYPE>::type
		#define _STRING_CHAR_TYPE_SAMESIZE(_STRING_TYPE, _OTHER_STRING_TYPE) typename std::enable_if<\
			!std::is_same<_STRING_TYPE, _OTHER_STRING_TYPE>::value\
			&& (sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE))\
			&& (std::is_same<_OTHER_STRING_TYPE, char>::value\
				|| std::is_same<_OTHER_STRING_TYPE, wchar_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char16_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char32_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, unichar>::value), _OTHER_STRING_TYPE>::type
		#define _STRING_CHAR_TYPE_DIFFSIZE(_STRING_TYPE, _OTHER_STRING_TYPE) typename std::enable_if<\
			!std::is_same<_STRING_TYPE, _OTHER_STRING_TYPE>::value\
			&& (sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE))\
			&& (std::is_same<_OTHER_STRING_TYPE, char>::value\
				|| std::is_same<_OTHER_STRING_TYPE, wchar_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char16_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char32_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, unichar>::value), _OTHER_STRING_TYPE>::type
	#else
		#define _STRING_NONCHAR_NUMBER(_STRING_TYPE, _NUM_TYPE) typename std::enable_if<\
			(std::is_arithmetic<_NUM_TYPE>::value || std::is_enum<_NUM_TYPE>::value)\
			&& !std::is_pointer<_NUM_TYPE>::value\
			&& !std::is_same<_NUM_TYPE, _STRING_TYPE>::value\
			&& !std::is_same<_NUM_TYPE, bool>::value\
			&& !std::is_same<_NUM_TYPE, char>::value\
			&& !std::is_same<_NUM_TYPE, char16_t>::value\
			&& !std::is_same<_NUM_TYPE, char32_t>::value\
			&& !std::is_same<_NUM_TYPE, wchar_t>::value, _NUM_TYPE>::type
		#define _STRING_CHAR_TYPE_SAMESIZE(_STRING_TYPE, _OTHER_STRING_TYPE) typename std::enable_if<\
			!std::is_same<_STRING_TYPE, _OTHER_STRING_TYPE>::value\
			&& (sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE))\
			&& (std::is_same<_OTHER_STRING_TYPE, char>::value\
				|| std::is_same<_OTHER_STRING_TYPE, wchar_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char16_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char32_t>::value), _OTHER_STRING_TYPE>::type
		#define _STRING_CHAR_TYPE_DIFFSIZE(_STRING_TYPE, _OTHER_STRING_TYPE) typename std::enable_if<\
			!std::is_same<_STRING_TYPE, _OTHER_STRING_TYPE>::value\
			&& (sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE))\
			&& (std::is_same<_OTHER_STRING_TYPE, char>::value\
				|| std::is_same<_OTHER_STRING_TYPE, wchar_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char16_t>::value\
				|| std::is_same<_OTHER_STRING_TYPE, char32_t>::value), _OTHER_STRING_TYPE>::type
	#endif
	
	class BasicStringUtils
	{
	public:
		template<typename _STRING_TYPE>
		friend class BasicString;
		
		template<typename _STRING_TYPE>
		static int int_cast(const _STRING_TYPE& val)
		{
			size_t n = (sizeof(int)-sizeof(_STRING_TYPE))*8;
			unsigned int i = val;
			i = (i << n);
			i = (i >> n);
			return (int)i;
		}
		
		template<typename _STRING_TYPE>
		static void convert_fromBool(const bool& b, _STRING_TYPE* chars, size_t*length)
		{
			if(b)
			{
				chars[0] = (_STRING_TYPE)'t';
				chars[1] = (_STRING_TYPE)'r';
				chars[2] = (_STRING_TYPE)'u';
				chars[3] = (_STRING_TYPE)'e';
				chars[4] = NULLCHAR;
				*length = 4;
			}
			else
			{
				chars[0] = (_STRING_TYPE)'f';
				chars[1] = (_STRING_TYPE)'a';
				chars[2] = (_STRING_TYPE)'l';
				chars[3] = (_STRING_TYPE)'s';
				chars[4] = (_STRING_TYPE)'e';
				chars[5] = NULLCHAR;
				*length = 5;
			}
		}
		
		template<typename _NUM_TYPE>
		static _NUM_TYPE ten_to(long the)
		{
			if(the>0)
			{
				_NUM_TYPE val = 10;
				for(int i=1; i<the; i++)
				{
					val *= 10;
				}
				return val;
			}
			else if(the<0)
			{
				_NUM_TYPE val = 10;
				for(int i=-1; i>the; i--)
				{
					val *= 10;
				}
				return 1/val;
			}
			return 1;
		}
		
		template<typename T, size_t T_SIZE=sizeof(T)>
		struct utf_eqv {};
		template<typename T>
		struct utf_eqv<T,1> { typedef char type; };
		#ifdef _WIN32
			template<typename T>
			struct utf_eqv<T,2> { typedef int16_t type; };
			template<typename T>
			struct utf_eqv<T, 4> { typedef int32_t type; };
		#else
			template<typename T>
			struct utf_eqv<T,2> { typedef char16_t type; };
			template<typename T>
			struct utf_eqv<T, 4> { typedef char32_t type; };
		#endif
		
		template<typename _OUTPUT_STRING_TYPE, typename _NUM_TYPE>
		static void convert_fromNumber(const _NUM_TYPE& num, std::basic_stringstream<_OUTPUT_STRING_TYPE>* ss)
		{
			*ss << std::setprecision(10);
			if(sizeof(_NUM_TYPE)==1)
			{
				*ss << (int)num;
			}
			else
			{
				*ss << num;
			}
		}
		
		template<typename _OUT, typename _IN, typename std::enable_if<(sizeof(_OUT)==sizeof(_IN)), size_t>::type = 0>
		static std::basic_string<_OUT>& string_cast(std::basic_string<_IN>&& str)
		{
			std::basic_string<_IN>& str_l = str;
			return *((std::basic_string<_OUT>*)&str_l);
		}
		
		//same size chars
		template<typename _OUTPUT_STRING_TYPE, typename _INPUT_STRING_TYPE,
			typename std::enable_if<(
				(sizeof(_OUTPUT_STRING_TYPE)==sizeof(_INPUT_STRING_TYPE))
				&& std::is_integral<_OUTPUT_STRING_TYPE>::value
				&& std::is_integral<_INPUT_STRING_TYPE>::value), _OUTPUT_STRING_TYPE>::type = 0>
		static void convert_fromString(const _INPUT_STRING_TYPE* str, size_t length, std::basic_string<_OUTPUT_STRING_TYPE>* output)
		{
			if(length==0)
			{
				return;
			}
			*output = (const _OUTPUT_STRING_TYPE*)str;
		}
		
		//multibyte to byte
		template<typename _OUTPUT_STRING_TYPE, typename _INPUT_STRING_TYPE,
			typename std::enable_if<(
				(sizeof(_OUTPUT_STRING_TYPE)==1 && sizeof(_INPUT_STRING_TYPE)>1 && sizeof(_INPUT_STRING_TYPE)<=4)
				&& std::is_integral<_OUTPUT_STRING_TYPE>::value
				//for some reason I have to specify _INPUT_STRING_TYPE as the enable_if type or it won't compile in visual studio...
				&& std::is_integral<_INPUT_STRING_TYPE>::value), _INPUT_STRING_TYPE>::type = 0>
		static void convert_fromString(const _INPUT_STRING_TYPE* str, size_t length, std::basic_string<_OUTPUT_STRING_TYPE>* output)
		{
			typedef typename utf_eqv<_INPUT_STRING_TYPE>::type INPUT_TYPE;
			if(sizeof(_INPUT_STRING_TYPE)==2)
			{
				std::wstring_convert<std::codecvt_utf8_utf16<INPUT_TYPE>, INPUT_TYPE> convert;
				*output = std::move(string_cast<_OUTPUT_STRING_TYPE,char>(convert.to_bytes((const INPUT_TYPE*)str, (const INPUT_TYPE*)str+length)));
			}
			else if(sizeof(_INPUT_STRING_TYPE)==4)
			{
				std::wstring_convert<std::codecvt_utf8<INPUT_TYPE>, INPUT_TYPE> convert;
				*output = std::move(string_cast<_OUTPUT_STRING_TYPE,char>(convert.to_bytes((const INPUT_TYPE*)str, (const INPUT_TYPE*)str+length)));
			}
		}
		
		//multibyte to multibyte
		template<typename _OUTPUT_STRING_TYPE, typename _INPUT_STRING_TYPE,
			typename std::enable_if<(
				(sizeof(_OUTPUT_STRING_TYPE)>1 && sizeof(_INPUT_STRING_TYPE)>1)
				&& std::is_integral<_OUTPUT_STRING_TYPE>::value
				&& std::is_integral<_INPUT_STRING_TYPE>::value), _OUTPUT_STRING_TYPE>::type = 0>
		static void convert_fromString(const _INPUT_STRING_TYPE* str, size_t length, std::basic_string<_OUTPUT_STRING_TYPE>* output)
		{
			typedef typename utf_eqv<_OUTPUT_STRING_TYPE>::type OUTPUT_TYPE;
			std::wstring_convert<std::codecvt_utf16<OUTPUT_TYPE>, OUTPUT_TYPE> convert;
			if(sizeof(_OUTPUT_STRING_TYPE)>sizeof(_INPUT_STRING_TYPE))
			{
				*output = std::move(string_cast<_OUTPUT_STRING_TYPE,OUTPUT_TYPE>(convert.from_bytes((const char*)str, (const char*)str+length)));
			}
			else
			{
				std::string&& buffer = convert.to_bytes((const OUTPUT_TYPE*)str, (const OUTPUT_TYPE*)str+length);
				*output = std::basic_string<_OUTPUT_STRING_TYPE>((const _OUTPUT_STRING_TYPE*)buffer.c_str(), buffer.length()/sizeof(_OUTPUT_STRING_TYPE));
			}
		}
		
		//byte to multibyte
		template<typename _OUTPUT_STRING_TYPE, typename _INPUT_STRING_TYPE,
			typename std::enable_if<(
				(sizeof(_INPUT_STRING_TYPE)==1 && sizeof(_OUTPUT_STRING_TYPE)>1 && sizeof(_OUTPUT_STRING_TYPE)<=4)
				&& std::is_integral<_OUTPUT_STRING_TYPE>::value
				&& std::is_integral<_INPUT_STRING_TYPE>::value), _OUTPUT_STRING_TYPE>::type = 0>
		static void convert_fromString(const _INPUT_STRING_TYPE* str, size_t length, std::basic_string<_OUTPUT_STRING_TYPE>* output)
		{
			typedef typename utf_eqv<_OUTPUT_STRING_TYPE>::type OUTPUT_TYPE;
			if(sizeof(_OUTPUT_STRING_TYPE)==2)
			{
				std::wstring_convert<std::codecvt_utf8_utf16<OUTPUT_TYPE>, OUTPUT_TYPE> convert;
				*output = std::move(string_cast<_OUTPUT_STRING_TYPE,OUTPUT_TYPE>(convert.from_bytes((const char*)str, (const char*)str+length)));
			}
			else if(sizeof(_OUTPUT_STRING_TYPE)==4)
			{
				std::wstring_convert<std::codecvt_utf8<OUTPUT_TYPE>, OUTPUT_TYPE> convert;
				*output = std::move(string_cast<_OUTPUT_STRING_TYPE,OUTPUT_TYPE>(convert.from_bytes((const char*)str, (const char*)str+length)));
			}
		}
		
		template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const BasicString<_STRING_SAME_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const BasicString<_STRING_DIFF_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const std::basic_string<_STRING_SAME_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const std::basic_string<_STRING_DIFF_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr);
		
		template<typename _STRING_TYPE, typename _OTHER_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_NONCHAR_NUMBER(_STRING_TYPE,_OTHER_TYPE)& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_TYPE>
		static void string_plus(const _STRING_NONCHAR_NUMBER(_STRING_TYPE,_OTHER_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr);
		
		template<typename _STRING_TYPE, typename _OTHER_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_ISBOOL(_STRING_TYPE,_OTHER_TYPE)& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_TYPE>
		static void string_plus(const _STRING_ISBOOL(_STRING_TYPE,_OTHER_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr);
		
		template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_CHAR_TYPE_SAMESIZE(_STRING_TYPE,_OTHER_STRING_TYPE)& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_TYPE>
		static void string_plus(const _STRING_CHAR_TYPE_SAMESIZE(_STRING_TYPE,_OTHER_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr);
		
		template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
		static void string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_CHAR_TYPE_DIFFSIZE(_STRING_TYPE,_OTHER_STRING_TYPE)& right, BasicString<_STRING_TYPE>* outputStr);
		template<typename _STRING_TYPE, typename _OTHER_TYPE>
		static void string_plus(const _STRING_CHAR_TYPE_DIFFSIZE(_STRING_TYPE,_OTHER_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr);
		
	private:
		enum CharType
		{
			STRINGCMP_CHARTYPE_SYMBOL,
			STRINGCMP_CHARTYPE_NUMBER,
			STRINGCMP_CHARTYPE_UPPERCASE_LETTER,
			STRINGCMP_CHARTYPE_LOWERCASE_LETTER
		};
		
		template<typename _STRING_TYPE>
		static unsigned char getCharType(const _STRING_TYPE&c)
		{
			int cint = int_cast<_STRING_TYPE>(c);
			if(std::isdigit(cint))
			{
				return STRINGCMP_CHARTYPE_NUMBER;
			}
			else if(std::isupper(cint))
			{
				return STRINGCMP_CHARTYPE_UPPERCASE_LETTER;
			}
			else if(std::islower(cint) || std::isalpha(cint))
			{
				return STRINGCMP_CHARTYPE_LOWERCASE_LETTER;
			}
			return STRINGCMP_CHARTYPE_SYMBOL;
		}
		
		static void throw_out_of_bounds(size_t index, size_t size);
		static void throw_number_format_error(const std::string& typeName, const std::string& reason);
	};
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const BasicString<_STRING_TYPE>& right);
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const _STRING_TYPE* right);
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const _STRING_TYPE* left, const BasicString<_STRING_TYPE>& right);
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const _STRING_TYPE& right);
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const _STRING_TYPE& left, const BasicString<_STRING_TYPE>& right);
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const std::basic_string<_STRING_TYPE>& right);
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const std::basic_string<_STRING_TYPE>& left, const BasicString<_STRING_TYPE>& right);
	
	template<typename _STRING_TYPE>
	class BasicString
	{
	private:
		_STRING_TYPE* characters;
		size_t size;
		
	public:
		typedef _STRING_TYPE char_type;
		static constexpr size_t NOTFOUND = (size_t)-1;
		
		friend class BasicStringUtils;
		template<typename _OTHER_STRING_TYPE>
		friend class BasicString;
		
		friend BasicString operator+ <>(const BasicString& left, const BasicString& right);
		friend BasicString operator+ <>(const BasicString& left, const _STRING_TYPE* right);
		friend BasicString operator+ <>(const _STRING_TYPE* left, const BasicString& right);
		friend BasicString operator+ <>(const BasicString& left, const _STRING_TYPE& right);
		friend BasicString operator+ <>(const _STRING_TYPE& left, const BasicString& right);
		friend BasicString operator+ <>(const BasicString& left, const std::basic_string<_STRING_TYPE>& right);
		friend BasicString operator+ <>(const std::basic_string<_STRING_TYPE>& left, const BasicString& right);
		
		static size_t strlen(const _STRING_TYPE* str)
		{
			size_t size = 0;
			while(str[size] != NULLCHAR)
			{
				size++;
			}
			return size;
		}
		
		BasicString()
			: size(0),
			characters((_STRING_TYPE*)std::calloc(1, sizeof(_STRING_TYPE)))
		{
			if(characters==nullptr)
			{
				throw std::bad_alloc();
			}
			characters[0] = NULLCHAR;
		}
		
		BasicString(const _STRING_TYPE* str, size_t length)
			: size(length),
			characters((_STRING_TYPE*)std::calloc(length+1, sizeof(_STRING_TYPE)))
		{
			if(characters==nullptr)
			{
				throw std::bad_alloc();
			}
			for(size_t i=0; i<size; i++)
			{
				characters[i] = str[i];
			}
			characters[size] = NULLCHAR;
		}
		
		BasicString(const _STRING_TYPE* str)
			: BasicString(str, BasicString<_STRING_TYPE>::strlen(str))
		{
			//
		}
		
		BasicString(const BasicString<_STRING_TYPE>& str)
			: BasicString(str.characters, str.size)
		{
			//
		}
		
		BasicString(BasicString<_STRING_TYPE>&& str)
			: size(str.size),
			characters(str.characters)
		{
			str.size = 0;
			str.characters = nullptr;
		}
		
		BasicString(const std::basic_string<_STRING_TYPE>& str)
			: BasicString(str.c_str(), str.length())
		{
			//
		}
		
		#ifdef __OBJC__
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)==sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		explicit BasicString(NSString* nsString)
			: size(0),
			characters(nullptr)
		{
			size_t size_new = (size_t)nsString.length;
			NSRange range = NSMakeRange(0, (NSUInteger)size_new);
			_STRING_TYPE*characters_new = (_STRING_TYPE*)std::calloc(size_new+1, sizeof(_STRING_TYPE));
			if(characters_new==nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size = size_new;
			[nsString getCharacters:(unichar*)characters range:range];
			characters[size_new] = NULLCHAR;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(_CHAR_TYPE)==sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		explicit BasicString(NSString* nsString)
			: BasicString((const _STRING_TYPE*)[nsString UTF8String])
		{
			//
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)!=sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		explicit BasicString(NSString* nsString)
			: size(0),
			characters(nullptr)
		{
			size_t length = (size_t)nsString.length;
			std::basic_string<_STRING_TYPE> output;
			unichar* str = new unichar[length+1];
			NSRange range = NSMakeRange(0, (NSUInteger)length);
			[nsString getCharacters:str range:range];
			str[length] = NULLCHAR;
			BasicStringUtils::convert_fromString<_STRING_TYPE,unichar>(str, length, &output);
			delete[] str;
			set(output.c_str(), output.length());
		}
		#endif
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(!std::is_same<_OTHER_STRING_TYPE,_STRING_TYPE>::value
				&& (sizeof(_OTHER_STRING_TYPE)==sizeof(_STRING_TYPE))
				&& std::is_integral<_STRING_TYPE>::value
				#ifdef __OBJC__
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,unichar>::value)), size_t>::type = 0>
				#else
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value)), size_t>::type = 0>
				#endif
		BasicString(const _OTHER_STRING_TYPE& c)
			: size(1),
			characters((_STRING_TYPE*)std::calloc(2, sizeof(_STRING_TYPE)))
		{
			//same char size
			if(characters == nullptr)
			{
				throw std::bad_alloc();
			}
			characters[0] = (_STRING_TYPE)c;
			characters[size] = NULLCHAR;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(!std::is_same<_OTHER_STRING_TYPE,_STRING_TYPE>::value
				&& (sizeof(_OTHER_STRING_TYPE)!=sizeof(_STRING_TYPE))
				&& std::is_integral<_STRING_TYPE>::value
				#ifdef __OBJC__
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,unichar>::value)), size_t>::type = 0>
				#else
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value)), size_t>::type = 0>
				#endif
		BasicString(const _OTHER_STRING_TYPE& c)
			: size(0),
			characters(nullptr)
		{
			//different char size
			_OTHER_STRING_TYPE str[2] = {c, NULLCHAR};
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str,1,&output);
			set(output.c_str(), output.length());
		}
		
		template<typename _SAME_STRING_TYPE,
			typename std::enable_if<std::is_same<_SAME_STRING_TYPE,_STRING_TYPE>::value, size_t>::type = 0>
		BasicString(const _SAME_STRING_TYPE& c)
			: size(1),
			characters((_STRING_TYPE*)std::calloc(2, sizeof(_STRING_TYPE)))
		{
			//same char
			if(characters == nullptr)
			{
				throw std::bad_alloc();
			}
			characters[0] = c;
			characters[size] = NULLCHAR;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString(const _OTHER_STRING_TYPE* str, size_t length)
			: BasicString((const _STRING_TYPE*)str, length)
		{
			//same char size
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString(const _OTHER_STRING_TYPE* str, size_t length)
			: size(0),
			characters(nullptr)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str, length, &output);
			set(output.c_str(), output.length());
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit BasicString(const _OTHER_STRING_TYPE* str)
			: BasicString((const _STRING_TYPE*)str, BasicString<_OTHER_STRING_TYPE>::strlen(str))
		{
			//same char size
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit BasicString(const _OTHER_STRING_TYPE* str)
			: BasicString(str, BasicString<_OTHER_STRING_TYPE>::strlen(str))
		{
			//different char size
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit BasicString(const BasicString<_OTHER_STRING_TYPE>& str)
			: BasicString((const _STRING_TYPE*)str.characters, str.size)
		{
			//same char size
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit BasicString(const BasicString<_OTHER_STRING_TYPE>& str)
			: BasicString(str.characters, str.size)
		{
			//different char size
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit BasicString(const std::basic_string<_OTHER_STRING_TYPE>& str)
			: BasicString((const _STRING_TYPE*)str.c_str(), str.length())
		{
			//same char size
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit BasicString(const std::basic_string<_OTHER_STRING_TYPE>& str)
			: BasicString(str.c_str(), str.length())
		{
			//different char size
		}
		
		~BasicString()
		{
			if(characters!=nullptr)
			{
				std::free(characters);
			}
		}
		
		size_t length() const
		{
			return size;
		}
		
		void clear()
		{
			_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, sizeof(_STRING_TYPE));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size = 0;
			characters[0] = NULLCHAR;
		}
		
		_STRING_TYPE& charAt(size_t index)
		{
			if(index >= size)
			{
				BasicStringUtils::throw_out_of_bounds(index, size);
			}
			return characters[index];
		}
		
		const _STRING_TYPE& charAt(size_t index) const
		{
			if(index >= size)
			{
				BasicStringUtils::throw_out_of_bounds(index, size);
			}
			return characters[index];
		}
		
		const _STRING_TYPE* getData() const
		{
			return characters;
		}
		
		operator const _STRING_TYPE*() const
		{
			return characters;
		}
		
		operator const std::basic_string<_STRING_TYPE>() const
		{
			return std::basic_string<_STRING_TYPE>(characters, size);
		}
		
		#ifdef __OBJC__
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)==sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		explicit operator NSString*() const
		{
			return [NSString stringWithCharacters:(const unichar*)characters length:(NSUInteger)size];
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(_CHAR_TYPE)==sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		explicit operator NSString*() const
		{
			return [NSString stringWithUTF8String:(const char*)characters];
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)!=sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		explicit operator NSString*() const
		{
			std::basic_string<unichar> output;
			BasicStringUtils::convert_fromString<unichar,_STRING_TYPE>(characters, size, &output);
			return [NSString stringWithCharacters:(const unichar*)output.c_str() length:(NSUInteger)output.length()];
		}
		#endif
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit operator const std::basic_string<_OTHER_STRING_TYPE>() const
		{
			//same char size
			return std::basic_string<_OTHER_STRING_TYPE>((const _OTHER_STRING_TYPE*)characters, size);
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		explicit operator const std::basic_string<_OTHER_STRING_TYPE>() const
		{
			//different char size
			std::basic_string<_OTHER_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_OTHER_STRING_TYPE,_STRING_TYPE>(characters, size, &output);
			return output;
		}
		
		void set(const _STRING_TYPE* str, size_t length)
		{
			size_t size_new = length;
			_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			for(size_t i=0; i<size_new; i++)
			{
				characters[i] = str[i];
			}
			size = size_new;
			characters[size] = NULLCHAR;
		}
		
		void set(const _STRING_TYPE* str)
		{
			set(str, BasicString<_STRING_TYPE>::strlen(str));
		}
		
		BasicString<_STRING_TYPE>& operator=(const BasicString<_STRING_TYPE>& str)
		{
			set(str.characters, str.size);
			return *this;
		}
		
		BasicString<_STRING_TYPE>& operator=(BasicString<_STRING_TYPE>&& str)
		{
			if(characters!=nullptr)
			{
				size = 0;
				std::free(characters);
			}
			characters = str.characters;
			size = str.size;
			str.size = 0;
			str.characters = nullptr;
			return *this;
		}
		
		BasicString<_STRING_TYPE>& operator=(const _STRING_TYPE* str)
		{
			set(str, BasicString<_STRING_TYPE>::strlen(str));
			return *this;
		}
		
		BasicString<_STRING_TYPE>& operator=(const std::basic_string<_STRING_TYPE>& str)
		{
			set(str.c_str(), str.length());
			return *this;
		}
		
		#ifdef __OBJC__
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)==sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(NSString* nsString)
		{
			size_t size_new = (size_t)nsString.length;
			NSRange range = NSMakeRange(0, (NSUInteger)size_new);
			_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new==nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size = size_new;
			[nsString getCharacters:(unichar*)characters range:range];
			characters[size_new] = NULLCHAR;
			return *this;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(_CHAR_TYPE)==sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(NSString* nsString)
		{
			set((const _STRING_TYPE*)[nsString UTF8String]);
			return *this;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
		typename std::enable_if<(sizeof(unichar)!=sizeof(_CHAR_TYPE)
								 && sizeof(_CHAR_TYPE)!=sizeof(char)
								 && std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(NSString* nsString)
		{
			size_t length = (size_t)nsString.length;
			std::basic_string<_STRING_TYPE> output;
			unichar* str = new unichar[length+1];
			NSRange range = NSMakeRange(0, (NSUInteger)length);
			[nsString getCharacters:str range:range];
			str[length] = NULLCHAR;
			BasicStringUtils::convert_fromString<_STRING_TYPE,unichar>(str, length, &output);
			delete[] str;
			set(output.c_str(), output.length());
		}
		#endif
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(!std::is_same<_OTHER_STRING_TYPE,_STRING_TYPE>::value
				&& (sizeof(_OTHER_STRING_TYPE)==sizeof(_STRING_TYPE))
				&& std::is_integral<_STRING_TYPE>::value
				#ifdef __OBJC__
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,unichar>::value)), size_t>::type = 0>
				#else
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value)), size_t>::type = 0>
				#endif
		BasicString<_STRING_TYPE>& operator=(const _OTHER_STRING_TYPE& c)
		{
			//same char size
			size_t size_new = 1;
			_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			characters[0] = (_STRING_TYPE)c;
			size = size_new;
			characters[size] = NULLCHAR;
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(!std::is_same<_OTHER_STRING_TYPE,_STRING_TYPE>::value
				&& (sizeof(_OTHER_STRING_TYPE)!=sizeof(_STRING_TYPE))
				&& std::is_integral<_STRING_TYPE>::value
				#ifdef __OBJC__
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,unichar>::value)), size_t>::type = 0>
				#else
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value)), size_t>::type = 0>
				#endif
		BasicString<_STRING_TYPE>& operator=(const _OTHER_STRING_TYPE& c)
		{
			//different char size
			_OTHER_STRING_TYPE str[2] = {c, NULLCHAR};
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str, 1, &output);
			set(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _SAME_STRING_TYPE,
			typename std::enable_if<std::is_same<_SAME_STRING_TYPE,_STRING_TYPE>::value, size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const _SAME_STRING_TYPE& c)
		{
			//same char
			size_t size_new = 1;
			_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			characters[0] = c;
			size = size_new;
			characters[size] = NULLCHAR;
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const _OTHER_STRING_TYPE* str)
		{
			//same char size
			set((const _STRING_TYPE*)str, BasicString<_OTHER_STRING_TYPE>::strlen(str));
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const _OTHER_STRING_TYPE* str)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str, BasicString<_OTHER_STRING_TYPE>::strlen(str), &output);
			set(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const BasicString<_OTHER_STRING_TYPE>& str)
		{
			//same char size
			set((const _STRING_TYPE*)str.characters, str.size);
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const BasicString<_OTHER_STRING_TYPE>& str)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str.characters, str.size, &output);
			set(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const std::basic_string<_OTHER_STRING_TYPE>& str)
		{
			//same char size
			set((const _STRING_TYPE*)str.c_str(), str.length());
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator=(const std::basic_string<_OTHER_STRING_TYPE>& str)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str.c_str(), str.length(), &output);
			set(output.c_str(), output.length());
			return *this;
		}
		
		void append(const _STRING_TYPE* str, size_t length)
		{
			size_t size_new = size + length;
			_STRING_TYPE* characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size_t counter = 0;
			for(size_t i=size; i<size_new; i++)
			{
				characters[i] = str[counter];
				counter++;
			}
			size = size_new;
			characters[size] = NULLCHAR;
		}
		
		void append(const _STRING_TYPE* str)
		{
			append(str, BasicString::strlen(str));
		}
		
		void append(const _STRING_TYPE& c)
		{
			size_t size_new = size+1;
			_STRING_TYPE* characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			characters[size] = c;
			size = size_new;
			characters[size] = NULLCHAR;
		}
		
		BasicString<_STRING_TYPE>& operator+=(const _STRING_TYPE& c)
		{
			append(c);
			return *this;
		}
		
		BasicString<_STRING_TYPE>& operator+=(const _STRING_TYPE* str)
		{
			append(str);
			return *this;
		}
		
		BasicString<_STRING_TYPE>& operator+=(const BasicString<_STRING_TYPE>& str)
		{
			append(str.characters, str.size);
			return *this;
		}
		
		BasicString<_STRING_TYPE>& operator+=(const std::basic_string<_STRING_TYPE>& str)
		{
			append(str.c_str(), str.length());
			return *this;
		}
		
		#ifdef __OBJC__
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)==sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(NSString* nsString)
		{
			size_t nsLength = (size_t)nsString.length;
			size_t size_new = size + nsLength;
			_STRING_TYPE* characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
			if(characters_new==nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size_t size_old = size;
			size = size_new;
			NSRange range = NSMakeRange(0, (NSUInteger)nsLength);
			[nsString getCharacters:(unichar*)(characters+size_old) range:range];
			characters[size_new] = NULLCHAR;
			return *this;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(_CHAR_TYPE)==sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(NSString* nsString)
		{
			append((const _STRING_TYPE*)[nsString UTF8String]);
			return *this;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<(sizeof(unichar)!=sizeof(_CHAR_TYPE)
				&& sizeof(_CHAR_TYPE)!=sizeof(char)
				&& std::is_integral<_CHAR_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(NSString* nsString)
		{
			size_t nsLength = (size_t)nsString.length;
			std::basic_string<_STRING_TYPE> output;
			unichar* str = new unichar[nsLength+1];
			NSRange range = NSMakeRange(0, (NSUInteger)nsLength);
			[nsString getCharacters:str range:range];
			str[nsLength] = NULLCHAR;
			BasicStringUtils::convert_fromString<_STRING_TYPE,unichar>(str, nsLength, &output);
			delete[] str;
			append(output.c_str(), output.length());
			return *this;
		}
		#endif
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(!std::is_same<_OTHER_STRING_TYPE,_STRING_TYPE>::value
				&& (sizeof(_OTHER_STRING_TYPE)==sizeof(_STRING_TYPE))
				&& std::is_integral<_STRING_TYPE>::value
				#ifdef __OBJC__
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,unichar>::value)), size_t>::type = 0>
				#else
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value)), size_t>::type = 0>
				#endif
		BasicString<_STRING_TYPE>& operator+=(const _OTHER_STRING_TYPE& c)
		{
			//same char size
			append((_STRING_TYPE)c);
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(!std::is_same<_OTHER_STRING_TYPE,_STRING_TYPE>::value
				&& (sizeof(_OTHER_STRING_TYPE)!=sizeof(_STRING_TYPE))
				&& std::is_integral<_STRING_TYPE>::value
				#ifdef __OBJC__
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,unichar>::value)), size_t>::type = 0>
				#else
					&& (std::is_same<_OTHER_STRING_TYPE,char>::value
						|| std::is_same<_OTHER_STRING_TYPE,wchar_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char16_t>::value
						|| std::is_same<_OTHER_STRING_TYPE,char32_t>::value)), size_t>::type = 0>
				#endif
		BasicString<_STRING_TYPE>& operator+=(const _OTHER_STRING_TYPE& c)
		{
			//different char size
			_OTHER_STRING_TYPE str[2] = {c, NULLCHAR};
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString(str, 1, &output);
			append(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _SAME_STRING_TYPE,
			typename std::enable_if<std::is_same<_SAME_STRING_TYPE,_STRING_TYPE>::value, size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const _SAME_STRING_TYPE& c)
		{
			//same char
			append(c);
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const _OTHER_STRING_TYPE* str)
		{
			//same char size
			append((const _STRING_TYPE*)str, BasicString<_OTHER_STRING_TYPE>::strlen(str));
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const _OTHER_STRING_TYPE* str)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str, BasicString<_OTHER_STRING_TYPE>::strlen(str), &output);
			append(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const BasicString<_OTHER_STRING_TYPE>& str)
		{
			//same char size
			append((const _STRING_TYPE*)str.characters, str.size);
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const BasicString<_OTHER_STRING_TYPE>& str)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str.characters, str.size, &output);
			append(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)==sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const std::basic_string<_OTHER_STRING_TYPE>& str)
		{
			//same char size
			append((const _STRING_TYPE*)str.c_str(), str.length());
			return *this;
		}
		
		template<typename _OTHER_STRING_TYPE,
			typename std::enable_if<(sizeof(_STRING_TYPE)!=sizeof(_OTHER_STRING_TYPE)
				&& std::is_integral<_OTHER_STRING_TYPE>::value
				&& std::is_integral<_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const std::basic_string<_OTHER_STRING_TYPE>& str)
		{
			//different char size
			std::basic_string<_STRING_TYPE> output;
			BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(str.c_str(), str.length(), &output);
			append(output.c_str(), output.length());
			return *this;
		}
		
		template<typename _BOOL_TYPE,
			typename std::enable_if<(std::is_same<_BOOL_TYPE,bool>::value
				&& !std::is_same<_BOOL_TYPE,_STRING_TYPE>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const bool& b)
		{
			_STRING_TYPE chars[6];
			size_t bool_length = 0;
			BasicStringUtils::convert_fromBool<_STRING_TYPE>(b, chars, &bool_length);
			append(chars, bool_length);
			return *this;
		}
		
		template<typename _NUM_TYPE,
			typename std::enable_if<((std::is_arithmetic<_NUM_TYPE>::value || std::is_enum<_NUM_TYPE>::value)
				&& !std::is_same<_NUM_TYPE, _STRING_TYPE>::value
				&& !std::is_pointer<_NUM_TYPE>::value
				&& !std::is_same<_NUM_TYPE, bool>::value
				&& !std::is_same<_NUM_TYPE, char>::value
				&& !std::is_same<_NUM_TYPE, wchar_t>::value
				&& !std::is_same<_NUM_TYPE, char16_t>::value
				&& !std::is_same<_NUM_TYPE, char32_t>::value), size_t>::type = 0>
		BasicString<_STRING_TYPE>& operator+=(const _NUM_TYPE& num)
		{
			std::basic_stringstream<_STRING_TYPE> ss;
			BasicStringUtils::convert_fromNumber<_STRING_TYPE,_NUM_TYPE>(num, &ss);
			std::basic_string<_STRING_TYPE>&& str = ss.str();
			append(str.c_str(), str.length());
			return *this;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<std::is_integral<_CHAR_TYPE>::value, size_t>::type = 0>
		int compare(const BasicString<_STRING_TYPE>& cmp) const
		{
			size_t amount = 0;
			if(size < cmp.size)
			{
				amount = size;
			}
			else
			{
				amount = cmp.size;
			}
			for(size_t i=0; i<amount; i++)
			{
				const _STRING_TYPE& c1 = characters[i];
				const _STRING_TYPE& c2 = cmp.characters[i];
				unsigned char type1 = getCharType(c1);
				unsigned char type2 = getCharType(c2);
				if(type1==type2)
				{
					if(c1<c2)
					{
						return -1;
					}
					else if(c2<c1)
					{
						return 1;
					}
				}
				else
				{
					if(type1==BasicStringUtils::STRINGCMP_CHARTYPE_UPPERCASE_LETTER && type2==BasicStringUtils::STRINGCMP_CHARTYPE_LOWERCASE_LETTER)
					{
						_STRING_TYPE c1mod = (_STRING_TYPE)std::tolower(BasicStringUtils::int_cast<_STRING_TYPE>(c1));
						if(c2<c1mod)
						{
							return 1;
						}
						return -1;
					}
					else if(type1==BasicStringUtils::STRINGCMP_CHARTYPE_LOWERCASE_LETTER && type2==BasicStringUtils::STRINGCMP_CHARTYPE_UPPERCASE_LETTER)
					{
						_STRING_TYPE c2mod = (_STRING_TYPE)std::tolower(BasicStringUtils::int_cast<_STRING_TYPE>(c2));
						if(c1<c2mod)
						{
							return -1;
						}
						return 1;
					}
					else
					{
						if(type1<type2)
						{
							return -1;
						}
						else if(type2<type1)
						{
							return 1;
						}
					}
				}
			}
			if(size < cmp.size)
			{
				return -1;
			}
			else if(cmp.size < size)
			{
				return 1;
			}
			return 0;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<!std::is_integral<_CHAR_TYPE>::value, size_t>::type = 0>
		int compare(const BasicString<_STRING_TYPE>& cmp) const
		{
			size_t amount = 0;
			if(size < cmp.size)
			{
				amount = size;
			}
			else
			{
				amount = cmp.size;
			}
			for(size_t i=0; i<amount; i++)
			{
				const _STRING_TYPE& c1 = characters[i];
				const _STRING_TYPE& c2 = cmp.characters[i];
				if(c1<c2)
				{
					return -1;
				}
				else if(c1>c2)
				{
					return 1;
				}
			}
			if(size < cmp.size)
			{
				return -1;
			}
			else if(cmp.size < size)
			{
				return 1;
			}
			return 0;
		}
		
		bool operator<(const BasicString<_STRING_TYPE>& str) const
		{
			return compare(str)<0;
		}
		
		bool operator<=(const BasicString<_STRING_TYPE>& str) const
		{
			return compare(str)<=0;
		}
		
		bool operator>(const BasicString<_STRING_TYPE>& str) const
		{
			return compare(str)>0;
		}
		
		bool operator>=(const BasicString<_STRING_TYPE>& str) const
		{
			return compare(str)>=0;
		}
		
		bool equals(const BasicString<_STRING_TYPE>& str) const
		{
			if(size == str.size)
			{
				for(size_t i=0; i<size; i++)
				{
					if(characters[i] != str.characters[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		
		bool equals(const _STRING_TYPE* str) const
		{
			if(size == BasicString<_STRING_TYPE>::strlen(str))
			{
				for(size_t i=0; i<size; i++)
				{
					if(characters[i] != str[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		
		bool operator==(const BasicString<_STRING_TYPE>& str) const
		{
			return equals(str);
		}
		
		bool operator==(const _STRING_TYPE* str) const
		{
			return equals(str);
		}
		
		bool operator!=(const BasicString<_STRING_TYPE>& str) const
		{
			return !equals(str);
		}
		
		bool operator!=(const _STRING_TYPE* str) const
		{
			return !equals(str);
		}
		
		size_t indexOf(const _STRING_TYPE& find, size_t startIndex=0) const
		{
			if(startIndex>size)
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			for(size_t i=startIndex; i<size; i++)
			{
				if(characters[i]==find)
				{
					return i;
				}
			}
			return NOTFOUND;
		}
		
		size_t indexOf(const BasicString<_STRING_TYPE>& find, size_t startIndex=0) const
		{
			if(startIndex>size)
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			if(find.size==0)
			{
				return NOTFOUND;
			}
			else if(find.size > size)
			{
				return NOTFOUND;
			}
			size_t finish = size - find.size;
			for(size_t i=0; i<=finish; i++)
			{
				if(characters[i]==find.characters[0])
				{
					bool match = true;
					for(size_t j=1; j<find.size; j++)
					{
						if(characters[i+j] != find.characters[j])
						{
							match = false;
							j = find.size;
						}
					}
					if(match)
					{
						return i;
					}
				}
			}
			return NOTFOUND;
		}
		
		size_t indexOf(const _STRING_TYPE* find, size_t startIndex=0) const
		{
			if(startIndex>size)
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			size_t find_size = BasicString<_STRING_TYPE>::strlen(find);
			if(find_size==0)
			{
				return NOTFOUND;
			}
			else if(find_size > size)
			{
				return NOTFOUND;
			}
			size_t finish = size - find_size;
			for(size_t i=0; i<=finish; i++)
			{
				if(characters[i]==find[0])
				{
					bool match = true;
					for(size_t j=1; j<find_size; j++)
					{
						if(characters[i+j] != find[j])
						{
							match = false;
							j = find_size;
						}
					}
					if(match)
					{
						return i;
					}
				}
			}
			return NOTFOUND;
		}
		
		size_t lastIndexOf(const _STRING_TYPE& find, size_t startIndex) const
		{
			if(startIndex==(size_t)-1)
			{
				return NOTFOUND;
			}
			else if(startIndex>(size-1))
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			for(size_t i=startIndex; i!=(size_t)-1; i--)
			{
				if(characters[i]==find)
				{
					return i;
				}
			}
			return NOTFOUND;
		}
		
		size_t lastIndexOf(const _STRING_TYPE& find) const
		{
			return lastIndexOf(find, size-1);
		}
		
		size_t lastIndexOf(const BasicString<_STRING_TYPE>& find, size_t startIndex) const
		{
			if(startIndex==(size_t)-1)
			{
				return NOTFOUND;
			}
			else if(startIndex>(size-1))
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			else if(find.size==0)
			{
				return NOTFOUND;
			}
			else if(find.size > size)
			{
				return NOTFOUND;
			}
			size_t find_last = find.size-1;
			for(size_t i=startIndex; i>=find_last; i--)
			{
				if(characters[i]==find.characters[find_last])
				{
					bool match = true;
					size_t counter = i-1;
					for(size_t j=(find_last-1); j!=(size_t)-1; j--)
					{
						if(characters[counter] != find.characters[j])
						{
							match = false;
							j = 0;
						}
						else
						{
							counter--;
						}
					}
					if(match)
					{
						return i;
					}
				}
			}
			return NOTFOUND;
		}
		
		size_t lastIndexOf(const BasicString<_STRING_TYPE>& find) const
		{
			return lastIndexOf(find, size-1);
		}
		
		size_t lastIndexOf(const _STRING_TYPE* find, size_t startIndex) const
		{
			size_t find_size = BasicString<_STRING_TYPE>::strlen(find);
			if(startIndex==(size_t)-1)
			{
				return NOTFOUND;
			}
			else if(startIndex>(size-1))
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			else if(find_size==0)
			{
				return NOTFOUND;
			}
			else if(find_size > size)
			{
				return NOTFOUND;
			}
			size_t find_last = find_size-1;
			for(size_t i=startIndex; i>=find_last; i--)
			{
				if(characters[i]==find[find_last])
				{
					bool match = true;
					size_t counter = i-1;
					for(size_t j=(find_last-1); j!=(size_t)-1; j--)
					{
						if(characters[counter] != find[j])
						{
							match = false;
							j = 0;
						}
						else
						{
							counter--;
						}
					}
					if(match)
					{
						return i;
					}
				}
			}
			return NOTFOUND;
		}
		
		size_t lastIndexOf(const _STRING_TYPE* find)
		{
			return lastIndexOf(find, size-1);
		}
		
		BasicString<_STRING_TYPE> replace(const _STRING_TYPE& find, const _STRING_TYPE& replace) const
		{
			BasicString<_STRING_TYPE> newStr;
			_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size+1)*sizeof(_STRING_TYPE));
			if(newStr_characters_new==nullptr)
			{
				throw std::bad_alloc();
			}
			newStr.characters = newStr_characters_new;
			newStr.size = size;
			for(size_t i=0; i<size; i++)
			{
				if(characters[i] == find)
				{
					newStr.characters[i] = replace;
				}
				else
				{
					newStr.characters[i] = characters[i];
				}
			}
			newStr.characters[size] = NULLCHAR;
			return newStr;
		}
		
		BasicString<_STRING_TYPE> replace(const BasicString<_STRING_TYPE>& find, const BasicString<_STRING_TYPE>& replace) const
		{
			if(find.size==0)
			{
				return *this;
			}
			else if(find.size > size)
			{
				return *this;
			}
			std::vector<size_t> indexes;
			size_t finish = size - find.size;
			for(size_t i=0; i<=finish; i++)
			{
				if(characters[i]==find.characters[0])
				{
					bool match = true;
					for(size_t j=1; j<find.size; j++)
					{
						if(characters[i+j] != find.characters[j])
						{
							match = false;
							j = find.size;
						}
					}
					if(match)
					{
						indexes.push_back(i);
						i += (find.size-1);
					}
				}
			}
			size_t indexes_size = indexes.size();
			if(indexes_size>0)
			{
				BasicString<_STRING_TYPE> newStr;
				size_t size_new = size + (replace.size*indexes_size) - (find.size*indexes_size);
				_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
				if(newStr_characters_new==nullptr)
				{
					throw std::bad_alloc();
				}
				newStr.characters = newStr_characters_new;
				newStr.size = size_new;
				size_t oldStr_counter = 0;
				size_t indexes_counter = 0;
				for(size_t i=0; i<size_new; i++)
				{
					if(oldStr_counter==indexes[indexes_counter])
					{
						for(size_t j=0; j<replace.size; j++)
						{
							newStr.characters[i] = replace.characters[j];
							i++;
						}
						i--;
						oldStr_counter += find.size;
						indexes_counter++;
					}
					else
					{
						newStr.characters[i] = characters[oldStr_counter];
						oldStr_counter++;
					}
				}
				newStr.characters[size_new] = NULLCHAR;
				return newStr;
			}
			return *this;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<std::is_integral<_CHAR_TYPE>::value, size_t>::type = 0>
		BasicString<_STRING_TYPE> toLowerCase() const
		{
			BasicString<_STRING_TYPE> newStr;
			_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size+1)*sizeof(_STRING_TYPE));
			if(newStr_characters_new==nullptr)
			{
				throw std::bad_alloc();
			}
			newStr.characters = newStr_characters_new;
			newStr.size = size;
			for(size_t i=0; i<size; i++)
			{
				newStr.characters[i] = (_STRING_TYPE)std::tolower(BasicStringUtils::int_cast<_STRING_TYPE>(characters[i]));
			}
			newStr.characters[size] = NULLCHAR;
			return newStr;
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<std::is_integral<_CHAR_TYPE>::value, size_t>::type = 0>
		BasicString<_STRING_TYPE> toUpperCase() const
		{
			BasicString<_STRING_TYPE> newStr;
			_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size+1)*sizeof(_STRING_TYPE));
			if(newStr_characters_new==nullptr)
			{
				throw std::bad_alloc();
			}
			newStr.characters = newStr_characters_new;
			newStr.size = size;
			for(size_t i=0; i<size; i++)
			{
				newStr.characters[i] = (_STRING_TYPE)std::toupper(BasicStringUtils::int_cast<_STRING_TYPE>(characters[i]));
			}
			newStr.characters[size] = NULLCHAR;
			return newStr;
		}
		
		BasicString<_STRING_TYPE> substring(size_t startIndex, size_t endIndex) const
		{
			if(startIndex > size)
			{
				BasicStringUtils::throw_out_of_bounds(startIndex, size);
			}
			else if(endIndex > size && !(endIndex<startIndex && endIndex==(size_t)-1))
			{
				BasicStringUtils::throw_out_of_bounds(endIndex, size);
			}
			
			BasicString<_STRING_TYPE> newStr;
			if(startIndex>endIndex)
			{
				size_t size_new = startIndex - endIndex;
				_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
				if(newStr_characters_new==nullptr)
				{
					throw std::bad_alloc();
				}
				newStr.characters = newStr_characters_new;
				newStr.size = size_new;
				size_t counter = 0;
				for(size_t i=startIndex; i>endIndex; i--)
				{
					newStr.characters[counter] = characters[i];
					counter++;
				}
			}
			else if(startIndex<endIndex)
			{
				size_t size_new = endIndex - startIndex;
				_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
				if(newStr_characters_new==nullptr)
				{
					throw std::bad_alloc();
				}
				newStr.characters = newStr_characters_new;
				newStr.size = size_new;
				size_t counter = 0;
				for(size_t i=startIndex; i<endIndex; i++)
				{
					newStr.characters[counter] = characters[i];
					counter++;
				}
			}
			return newStr;
		}
		
		BasicString<_STRING_TYPE> substring(size_t startIndex) const
		{
			return substring(startIndex, size);
		}
		
		template<typename _CHAR_TYPE=_STRING_TYPE,
			typename std::enable_if<std::is_integral<_CHAR_TYPE>::value, size_t>::type = 0>
		BasicString<_STRING_TYPE> trim() const
		{
			if(size==0)
			{
				return *this;
			}
			bool hitLetter = false;
			size_t startIndex = 0;
			for(size_t i=0; i<size && !hitLetter; i++)
			{
				if(!std::isblank(BasicStringUtils::int_cast<_STRING_TYPE>(characters[i])))
				{
					startIndex = i;
					hitLetter = true;
				}
			}
			if(!hitLetter)
			{
				return BasicString<_STRING_TYPE>();
			}
			hitLetter = false;
			size_t endIndex = size;
			for(size_t i=(size-1); i>=startIndex && !hitLetter; i--)
			{
				if(!std::isblank(BasicStringUtils::int_cast<_STRING_TYPE>(characters[i])))
				{
					endIndex = i+1;
					hitLetter = true;
				}
			}
			return substring(startIndex, endIndex);
		}
		
		std::vector<BasicString<_STRING_TYPE> > split(const _STRING_TYPE& delim) const
		{
			std::vector<BasicString<_STRING_TYPE> > elements;
			size_t lastStart = 0;
			for(size_t i=0; i<size; i++)
			{
				if(characters[i]==delim)
				{
					if(lastStart<i)
					{
						elements.push_back(substring(lastStart, i));
					}
					lastStart = i+1;
				}
			}
			if(lastStart<size)
			{
				elements.push_back(substring(lastStart, size));
			}
			return elements;
		}
		
		template<typename _NUM_TYPE,
			typename std::enable_if<std::is_arithmetic<_NUM_TYPE>::value, size_t>::type = 0>
		_NUM_TYPE toArithmeticValue() const
		{
			if(size==0)
			{
				return 0;
			}
			size_t decimalIndex = (size_t)-1;
			size_t startIndex = (size_t)-1;
			bool hitNumber = false;
			for(size_t i=0; i<size; i++)
			{
				const _STRING_TYPE& c = characters[i];
				int cint = BasicStringUtils::int_cast<_STRING_TYPE>(c);
				if(std::isdigit(cint))
				{
					hitNumber = true;
					startIndex = i;
				}
				else if(c==(_STRING_TYPE)',')
				{
					if(!hitNumber)
					{
						BasicStringUtils::throw_number_format_error(typeid(_NUM_TYPE).name(), "Unexpected character at index "+std::to_string(i));
					}
				}
				else if(c==(_STRING_TYPE)'-' || c==(_STRING_TYPE)'+')
				{
					if(hitNumber)
					{
						startIndex = i-1;
						i = size;
					}
				}
				else if(c==(_STRING_TYPE)'.')
				{
					startIndex = i-1;
					decimalIndex = i;
					i = size;
				}
				else if(!std::isblank(cint))
				{
					startIndex = i-1;
					i = size;
				}
			}
			if(startIndex==(size_t)-1 && decimalIndex!=0)
			{
				BasicStringUtils::throw_number_format_error(typeid(_NUM_TYPE).name(), "Unexpected character at index 0");
			}
			_NUM_TYPE mult = 1;
			_NUM_TYPE num = 0;
			int tens_counter = 0;
			//in front of decimal point
			for(size_t i=startIndex; i!=(size_t)-1; i--)
			{
				const _STRING_TYPE& c = characters[i];
				if(std::isdigit(BasicStringUtils::int_cast<_STRING_TYPE>(c)))
				{
					_NUM_TYPE digit = (_NUM_TYPE)(c - (_STRING_TYPE)'0');
					num += (digit*BasicStringUtils::ten_to<_NUM_TYPE>(tens_counter));
					tens_counter++;
				}
				else if(c==(_STRING_TYPE)'-')
				{
					mult *= -1;
				}
			}
			if(!std::is_integral<_NUM_TYPE>::value && decimalIndex!=(size_t)-1)
			{
				tens_counter = -1;
				//behind decimal point
				for(size_t i=decimalIndex+1; i<size; i++)
				{
					const _STRING_TYPE& c = characters[i];
					int cint = BasicStringUtils::int_cast<_STRING_TYPE>(c);
					if(std::isdigit(cint))
					{
						_NUM_TYPE digit = (_NUM_TYPE)(c - (_STRING_TYPE)'0');
						num += (digit*BasicStringUtils::ten_to<_NUM_TYPE>(tens_counter));
						tens_counter--;
					}
					else if(!std::isblank(cint) && c!=(_STRING_TYPE)',')
					{
						i = size;
					}
				}
			}
			if(!std::is_unsigned<_NUM_TYPE>::value)
			{
				return mult*num;
			}
			return num;
		}
	};
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const BasicString<_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t size_new = left.size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const _STRING_TYPE* right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t right_size = BasicString<_STRING_TYPE>::strlen(right);
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const _STRING_TYPE* left, const BasicString<_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t left_size = BasicString<_STRING_TYPE>::strlen(left);
		size_t size_new = left_size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left[i];
		}
		size_t counter = 0;
		for(size_t i=left_size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const _STRING_TYPE& right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t size_new = left.size + 1;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		newStr.characters[left.size] = right;
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const _STRING_TYPE& left, const BasicString<_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t size_new = 1 + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		newStr.characters[0] = left;
		size_t counter = 0;
		for(size_t i=1; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const std::basic_string<_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t right_size = right.length();
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const std::basic_string<_STRING_TYPE>& left, const BasicString<_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		size_t left_size = left.length();
		size_t size_new = left_size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
		return newStr;
	}
	
	#ifdef __OBJC__
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, NSString* right)
	{
		//TODO do this shit better
		BasicString<_STRING_TYPE> right_str;
		right_str += right;
		return left + right_str;
	}
	
	template<typename _STRING_TYPE>
	BasicString<_STRING_TYPE> operator+(NSString* left, const BasicString<_STRING_TYPE>& right)
	{
		//TODO do this shit better
		BasicString<_STRING_TYPE> left_str;
		left_str += left;
		return left_str + right;
	}
	#endif
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_CHAR_TYPE_SAMESIZE(_STRING_TYPE,_OTHER_STRING_TYPE)& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		size_t size_new = left.size + 1;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		newStr.characters[left.size] = (_STRING_TYPE)right;
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_CHAR_TYPE_DIFFSIZE(_STRING_TYPE,_OTHER_STRING_TYPE)& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		_OTHER_STRING_TYPE right_arr[2] ={right, NULLCHAR};
		std::basic_string<_STRING_TYPE> right_str;
		BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(right_arr,1,&right_str);
		size_t right_size = right_str.length();
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right_str[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const _STRING_CHAR_TYPE_SAMESIZE(_STRING_TYPE,_OTHER_STRING_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		size_t size_new = 1 + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		newStr.characters[0] = (_STRING_TYPE)left;
		size_t counter = 0;
		for(size_t i=1; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const _STRING_CHAR_TYPE_DIFFSIZE(_STRING_TYPE,_OTHER_STRING_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		_OTHER_STRING_TYPE left_arr[2] ={left, NULLCHAR};
		std::basic_string<_STRING_TYPE> left_str;
		BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(left_arr,1,&left_str);
		size_t left_size = left_str.length();
		size_t size_new = left_size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left_str[i];
		}
		size_t counter = 0;
		for(size_t i=left_size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_ISBOOL(_STRING_TYPE,_OTHER_TYPE)& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		_STRING_TYPE right_chars[6];
		size_t right_size = 0;
		BasicStringUtils::convert_fromBool<_STRING_TYPE>(right, right_chars, &right_size);
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right_chars[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_TYPE>
	void BasicStringUtils::string_plus(const _STRING_ISBOOL(_STRING_TYPE,_OTHER_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		_STRING_TYPE left_chars[6];
		size_t left_size = 0;
		BasicString<_STRING_TYPE>::bool_chars(left, left_chars, &left_size);
		size_t size_new = left_size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left_chars[i];
		}
		size_t counter = 0;
		for(size_t i=left_size; i<right.size; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _NUM_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const _STRING_NONCHAR_NUMBER(_STRING_TYPE,_NUM_TYPE)& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		std::basic_stringstream<_STRING_TYPE> ss;
		BasicStringUtils::convert_fromNumber<_STRING_TYPE,_NUM_TYPE>(right, &ss);
		std::basic_string<_STRING_TYPE>&& right_str = ss.str();
		size_t right_size = right_str.length();
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right_str[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _NUM_TYPE>
	void BasicStringUtils::string_plus(const _STRING_NONCHAR_NUMBER(_STRING_TYPE,_NUM_TYPE)& left, const BasicString<_STRING_TYPE>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		std::basic_stringstream<_STRING_TYPE> ss;
		BasicStringUtils::convert_fromNumber<_STRING_TYPE,_NUM_TYPE>(left, &ss);
		std::basic_string<_STRING_TYPE>&& left_str = ss.str();
		size_t left_size = left.length();
		size_t size_new = left_size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_TYPE,
		typename std::enable_if<
			(std::is_arithmetic<_OTHER_TYPE>::value || std::is_enum<_OTHER_TYPE>::value)
			&& !std::is_same<_STRING_TYPE,_OTHER_TYPE>::value, size_t>::type = 0>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const _OTHER_TYPE& right)
	{
		BasicString<_STRING_TYPE> newStr;
		BasicStringUtils::string_plus<_STRING_TYPE,_OTHER_TYPE>(left, right, &newStr);
		return newStr;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_TYPE,
		typename std::enable_if<
			(std::is_arithmetic<_OTHER_TYPE>::value || std::is_enum<_OTHER_TYPE>::value)
			&& !std::is_same<_STRING_TYPE,_OTHER_TYPE>::value, size_t>::type = 0>
	BasicString<_STRING_TYPE> operator+(const _OTHER_TYPE& left, const BasicString<_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		BasicStringUtils::string_plus<_STRING_TYPE,_OTHER_TYPE>(left, right, &newStr);
		return newStr;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const BasicString<_STRING_SAME_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		size_t size_new = left.size + right.size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = (_STRING_TYPE)right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const BasicString<_STRING_DIFF_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		std::basic_string<_STRING_TYPE> right_str;
		BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(right.characters, right.size, &right_str);
		size_t right_size = right_str.length();
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right_str[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE, typename std::enable_if<!std::is_same<_STRING_TYPE,_OTHER_STRING_TYPE>::value>::type* = nullptr>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const BasicString<_OTHER_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		BasicStringUtils::string_plus<_STRING_TYPE,_OTHER_STRING_TYPE>(left, right, &newStr);
		return newStr;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const std::basic_string<_STRING_SAME_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		size_t right_size = right.length();
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = (_STRING_TYPE)right[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE>
	void BasicStringUtils::string_plus(const BasicString<_STRING_TYPE>& left, const std::basic_string<_STRING_DIFF_CHAR_SIZE(_STRING_TYPE,_OTHER_STRING_TYPE)>& right, BasicString<_STRING_TYPE>* outputStr)
	{
		BasicString<_STRING_TYPE>& newStr = *outputStr;
		std::basic_string<_STRING_TYPE> right_str;
		BasicStringUtils::convert_fromString<_STRING_TYPE,_OTHER_STRING_TYPE>(right.c_str(), right.length(), &right_str);
		size_t right_size = right_str.length();
		size_t size_new = left.size + right_size;
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<size_new; i++)
		{
			newStr.characters[i] = right_str[counter];
			counter++;
		}
		newStr.characters[size_new] = NULLCHAR;
	}
	
	template<typename _STRING_TYPE, typename _OTHER_STRING_TYPE, typename std::enable_if<!std::is_same<_STRING_TYPE, _OTHER_STRING_TYPE>::value>::type* = nullptr>
	BasicString<_STRING_TYPE> operator+(const BasicString<_STRING_TYPE>& left, const std::basic_string<_OTHER_STRING_TYPE>& right)
	{
		BasicString<_STRING_TYPE> newStr;
		BasicStringUtils::string_plus<_STRING_TYPE,_OTHER_STRING_TYPE>(left, right, &newStr);
		return newStr;
	}
	
	typedef BasicString<std::string::value_type> String;
	typedef BasicString<std::wstring::value_type> WideString;
	
	#undef _STRING_SAME_CHAR_SIZE
	#undef _STRING_DIFF_CHAR_SIZE
	#undef _STRING_ISBOOL
	#undef _STRING_NONCHAR_NUMBER
	#undef _STRING_CHAR_TYPE_SAMESIZE
	#undef _STRING_CHAR_TYPE_DIFFSIZE
	
	#undef NULLCHAR
	
#ifndef _STRING_STANDALONE
}
#endif

#endif //_GAMELIBRARY_STRING_H
