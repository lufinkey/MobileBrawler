
#define _CRT_SECURE_NO_WARNINGS

#include "WideString.h"
#include <cmath>
#include <cstdlib>
#include <new>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#ifdef _WIDESTRING_STRING_ENABLED
	#include "String.h"
#endif

#ifndef _STRING_STANDALONE
	#include "../Exception/NumberFormatException.h"
	#include "../Exception/Utilities/StringOutOfBoundsException.h"
#endif

#ifndef _STRING_STANDALONE
namespace GameLibrary
{
#endif
	
	#define _STRING_CLASS WideString
	#define _STRING_TYPE wchar_t
	#define _STRING_EXCEPTION_NUMBERFORMAT NumberFormatException
	#define _STRING_EXCEPTION_OUTOFBOUNDS StringOutOfBoundsException
	#define _STRING_LITERAL(str) L##str
	
	_STRING_CLASS::_STRING_CLASS(const std::wstring&str) : _STRING_CLASS(str.c_str(), str.length())
	{
		//
	}
	
	_STRING_CLASS::_STRING_CLASS(const std::string&str) : _STRING_CLASS(str.c_str(), str.length())
	{
		//
	}
	
	_STRING_CLASS::_STRING_CLASS(const char&c)
	{
		size = 1;
		characters = (_STRING_TYPE*)std::malloc((size+1) * sizeof(_STRING_TYPE));
		if(characters == nullptr)
		{
			throw std::bad_alloc();
		}
		char src[2] = {c, NULL};
		size = (size_t)mbtowc(characters, src, 2);
		if(size == (size_t)-1)
		{
			size = 0;
		}
		_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size+1)*sizeof(_STRING_TYPE));
		if(characters_new == nullptr)
		{
			std::free(characters);
			throw std::bad_alloc();
		}
		characters = characters_new;
		characters[size] = NULL;
	}

	_STRING_CLASS::_STRING_CLASS(const char*str) : _STRING_CLASS(str, std::strlen(str))
	{
		//
	}
	
	_STRING_CLASS::_STRING_CLASS(const char*str, size_t length)
	{
		size = (length*sizeof(char));
		characters = (_STRING_TYPE*)std::calloc(size+1, sizeof(_STRING_TYPE));
		if(characters == nullptr)
		{
			throw std::bad_alloc();
		}
		size = std::mbstowcs(characters,str,size+1);
		if(size == (size_t)-1)
		{
			size = 0;
		}
		_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size+1)*sizeof(_STRING_TYPE));
		if(characters_new == nullptr)
		{
			std::free(characters);
			throw std::bad_alloc();
		}
		characters = characters_new;
		characters[size] = NULL;
	}
	
	#ifdef _WIDESTRING_STRING_ENABLED
	_STRING_CLASS::_STRING_CLASS(const String&str) : _STRING_CLASS(str.characters, str.size)
	{
		//
	}
	#endif
	
	_STRING_CLASS::operator std::wstring() const
	{
		return std::wstring(characters);
	}
	
	_STRING_CLASS::operator std::string() const
	{
		char*str = new char[(size+1)*sizeof(_STRING_TYPE)];
		size_t strSize = std::wcstombs(str,characters,size+1);
		if(strSize == (size_t)-1)
		{
			return std::string();
		}
		std::string newStr(str);
		delete[] str;
		return newStr;
	}
	
	#ifdef _WIDESTRING_STRING_ENABLED
	String _STRING_CLASS::toString() const
	{
		return String(characters, size);
	}
	#endif
	
	void _STRING_CLASS::append(const char*str, size_t length)
	{
		append(WideString(str, length));
	}
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const std::string&str)
	{
		append(str.c_str(), str.length());
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const std::wstring&str)
	{
		append(str.c_str(), str.length());
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const char&c)
	{
		char buffer[2] = {c, NULL};
		append(buffer, 1);
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const char*str)
	{
		append(str, std::strlen(str));
		return *this;
	}
	
	#ifdef _WIDESTRING_STRING_ENABLED
	_STRING_CLASS& _STRING_CLASS::operator+=(const String&str)
	{
		append(str.characters, str.size);
		return *this;
	}
	#endif
	
	void _STRING_CLASS::set(const char*str, size_t length)
	{
		size_t size_new = (length*sizeof(char));
		_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(characters_new == nullptr)
		{
			throw std::bad_alloc();
		}
		size_new = std::mbstowcs(characters,str,size_new+1);
		if(size_new == (size_t)-1)
		{
			size_new = 0;
		}
		_STRING_TYPE*characters_new_new = (_STRING_TYPE*)std::realloc(characters_new, (size_new+1)*sizeof(_STRING_TYPE));
		if(characters_new_new == nullptr)
		{
			std::free(characters_new);
			throw std::bad_alloc();
		}
		characters = characters_new_new;
		size = size_new;
		characters[size] = NULL;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const std::wstring&str)
	{
		set(str.c_str(), str.length());
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const std::string&str)
	{
		set(str.c_str(), str.length());
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const char&c)
	{
		char buffer[2] = {c, NULL};
		set(buffer, 1);
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const char*str)
	{
		set(str, std::strlen(str));
		return *this;
	}
	
	#ifdef _WIDESTRING_STRING_ENABLED
	_STRING_CLASS& _STRING_CLASS::operator=(const String&str)
	{
		set(str.characters, str.size);
		return *this;
	}
	#endif
	
	#include "StringClass.cpp.impl"
	
	_STRING_CLASS operator+(const _STRING_CLASS&left, const std::wstring& right)
	{
		_STRING_CLASS newStr;
		size_t size_new = left.size + right.length();
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
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
			newStr.characters[i] = right.at(counter);
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}
	
	_STRING_CLASS operator+(const std::wstring& left, const _STRING_CLASS&right)
	{
		_STRING_CLASS newStr;
		size_t left_size = left.length();
		size_t size_new = left_size + right.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left.at(i);
		}
		size_t counter = 0;
		for(size_t i=left_size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}
	
	_STRING_CLASS operator+(const _STRING_CLASS&left, const std::string&right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS rightStr(right);
		size_t size_new = left.size + rightStr.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
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
			newStr.characters[i] = rightStr.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}

	_STRING_CLASS operator+(const std::string&left, const _STRING_CLASS&right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS leftStr(left);
		size_t size_new = leftStr.size + right.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<leftStr.size; i++)
		{
			newStr.characters[i] = leftStr.characters[i];
		}
		size_t counter = 0;
		for(size_t i=leftStr.size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}
	
	_STRING_CLASS operator+(const _STRING_CLASS&left, const char*right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS rightStr(right);
		size_t size_new = left.size + rightStr.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
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
			newStr.characters[i] = rightStr.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}

	_STRING_CLASS operator+(const char*left, const _STRING_CLASS&right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS leftStr(left);
		size_t size_new = leftStr.size + right.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<leftStr.size; i++)
		{
			newStr.characters[i] = leftStr.characters[i];
		}
		size_t counter = 0;
		for(size_t i=leftStr.size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}
	
	_STRING_CLASS operator+(const _STRING_CLASS&left, const char&right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS rightStr(right);
		size_t size_new = left.size + rightStr.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
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
			newStr.characters[i] = rightStr.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}

	_STRING_CLASS operator+(const char&left, const _STRING_CLASS&right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS leftStr(left);
		size_t size_new = leftStr.size + right.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = size_new;
		for(size_t i=0; i<leftStr.size; i++)
		{
			newStr.characters[i] = leftStr.characters[i];
		}
		size_t counter = 0;
		for(size_t i=leftStr.size; i<size_new; i++)
		{
			newStr.characters[i] = right.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}
	
	#ifdef _WIDESTRING_STRING_ENABLED
	_STRING_CLASS operator+(const _STRING_CLASS&left, const String&right)
	{
		_STRING_CLASS newStr;
		_STRING_CLASS rightStr(right);
		size_t size_new = left.size + rightStr.size;
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new == nullptr)
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
			newStr.characters[i] = rightStr.characters[i];
			counter++;
		}
		newStr.characters[size_new] = NULL;
		return newStr;
	}
	#endif
	
	std::wostream& operator<<(std::wostream& stream, const _STRING_CLASS& str)
	{
		stream.write(str.characters, str.length());
		return stream;
	}
	
#ifndef _STRING_STANDALONE
}
#endif
