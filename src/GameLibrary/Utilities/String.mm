
#ifdef __OBJC__

#include "String.h"
#include <cstdlib>

#ifndef _STRING_STANDALONE
namespace GameLibrary
#endif
{
	#define _STRING_CLASS String
	#define _STRING_TYPE char
	#define _STRING_LITERAL(str) str
	
	_STRING_CLASS::_STRING_CLASS(const NSString*&str) : _STRING_CLASS([str UTF8String], (size_t)[str length])
	{
		//
	}
	
	_STRING_CLASS::operator NSString*() const
	{
		return [NSString stringWithUTF8String:characters];
	}
	
	_STRING_CLASS& _STRING_CLASS::operator+=(const NSString*&str)
	{
		append([str UTF8String], (size_t)[str length]);
		return *this;
	}
	
	_STRING_CLASS& _STRING_CLASS::operator=(const NSString*&str)
	{
		size_t size_new = (size_t)[str length];
		_STRING_TYPE* characters_new = (_STRING_TYPE*)std::realloc(characters, (size_new+1)*sizeof(_STRING_TYPE));
		if(characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		characters = characters_new;
		const _STRING_TYPE* newChars = [str UTF8String];
		for(size_t i=0; i<size_new; i++)
		{
			characters[i] = newChars[i];
		}
		characters[size_new] = NULL;
		size = size_new;
		return *this;
	}
	
	_STRING_CLASS operator+(const _STRING_CLASS&left, const NSString*&right)
	{
		_STRING_CLASS newStr;
		size_t newStr_size_new = left.size + (size_t)[right length];
		const _STRING_TYPE* right_chars = [right UTF8String];
		_STRING_TYPE* newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (newStr_size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=(left.size+1); i<newStr_size_new; i++)
		{
			newStr.characters[i] = right_chars[counter];
			counter++;
		}
		newStr.characters[newStr_size_new] = NULL;
		newStr.size = newStr_size_new;
		return newStr;
	}
	
	_STRING_CLASS operator+(const NSString*&left, const _STRING_CLASS&right)
	{
		_STRING_CLASS newStr;
		size_t left_size = (size_t)[left length];
		size_t newStr_size_new = (size_t)[left length] + right.size;
		const _STRING_TYPE* left_chars = [left UTF8String];
		_STRING_TYPE*newStr_characters_new = (_STRING_TYPE*)std::realloc(newStr.characters, (newStr_size_new+1)*sizeof(_STRING_TYPE));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left_chars[i];
		}
		size_t counter = 0;
		for(size_t i=(left_size+1); i<newStr_size_new; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[newStr_size_new] = NULL;
		newStr.size = newStr_size_new;
		return newStr;
	}
	
#ifndef _STRING_STANDALONE
}
#endif

#endif
