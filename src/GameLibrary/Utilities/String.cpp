
#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <cmath>
#include <cstdlib>
#include <new>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#ifndef _STRING_STANDALONE
	#include "../Exception/NumberFormatException.h"
	#include "../Exception/Utilities/StringOutOfBoundsException.h"
#endif

#ifndef _STRING_STANDALONE
namespace GameLibrary
{
#endif
	
	#define _STRING_CLASS String
	#define _STRING_TYPE char
	#define _STRING_EXCEPTION_NUMBERFORMAT NumberFormatException
	#define _STRING_EXCEPTION_OUTOFBOUNDS StringOutOfBoundsException
	#define _STRING_LITERAL(str) str

	_STRING_CLASS::_STRING_CLASS(const std::string&str) : _STRING_CLASS(str.c_str(), str.length())
	{
		//
	}

	_STRING_CLASS::_STRING_CLASS(const std::wstring&str) : _STRING_CLASS(str.c_str(), str.length())
	{
		//
	}
	
	_STRING_CLASS::_STRING_CLASS(const wchar_t&c)
	{
		_STRING_TYPE buffer[10];
		size = (size_t)wctomb(buffer,c);
		if(size == (size_t)-1)
		{
			size = 0;
		}
		characters = (_STRING_TYPE*)std::calloc(size+1, sizeof(_STRING_TYPE));
		if(characters == nullptr)
		{
			throw std::bad_alloc();
		}
		for(size_t i=0; i<size; i++)
		{
			characters[i] = buffer[i];
		}
		characters[size] = NULL;
	}

	_STRING_CLASS::_STRING_CLASS(const wchar_t*str) : _STRING_CLASS(str, std::wcslen(str))
	{
		//
	}
	
	_STRING_CLASS::_STRING_CLASS(const wchar_t*str, size_t length)
	{
		size = (length*4);
		characters = (_STRING_TYPE*)std::calloc(size+1, sizeof(_STRING_TYPE));
		if(characters == nullptr)
		{
			throw std::bad_alloc();
		}
		size = std::wcstombs(characters,str,size+1);
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
	
	_STRING_CLASS::operator std::string() const
	{
		return std::string(characters);
	}
	
	_STRING_CLASS::operator std::wstring() const
	{
		wchar_t*str = new wchar_t[size+1];
		size_t strSize = std::mbstowcs(str,characters,size+1);
		if(strSize == (size_t)-1)
		{
			return std::wstring();
		}
		std::wstring newStr(str);
		delete[] str;
		return newStr;
	}
	
	void _STRING_CLASS::append(const wchar_t*str, size_t length)
	{
		append(String(str, length));
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
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const wchar_t&c)
	{
		wchar_t buffer[2] = {c, NULL};
		append(buffer, 1);
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const wchar_t*str)
	{
		append(str, std::wcslen(str));
		return *this;
	}
	
	void _STRING_CLASS::set(const wchar_t*str, size_t length)
	{
		size_t size_new = (length*4);
		_STRING_TYPE*characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(characters_new == nullptr)
		{
			throw std::bad_alloc();
		}
		size_new = std::wcstombs(characters,str,size_new+1);
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
	
	_STRING_CLASS& _STRING_CLASS::operator=(const std::string&str)
	{
		set(str.c_str(), str.length());
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const std::wstring&str)
	{
		set(str.c_str(), str.length());
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const wchar_t&c)
	{
		wchar_t buffer[2] = {c, NULL};
		set(buffer, 1);
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const wchar_t*str)
	{
		set(str, std::wcslen(str));
		return *this;
	}
	
	#include "StringClass.cpp.impl"
	
#ifndef _STRING_STANDALONE
}
#endif
