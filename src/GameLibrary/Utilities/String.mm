
#ifdef __OBJC__

#include "String.h"
#include <cstdlib>

#ifdef _STRING_USES_GAMELIBRARY
namespace GameLibrary
#endif
{
	String::String(const NSString*&str) : String([str UTF8String], (size_t)[str length])
	{
		//
	}
	
	String::operator NSString*() const
	{
		return [NSString stringWithUTF8String:characters];
	}
	
	String& String::operator+=(const NSString*&str)
	{
		append([str UTF8String], (size_t)[str length]);
		return *this;
	}
	
	String& String::operator=(const NSString*&str)
	{
		size_t total2 = (size_t)[str length];
		characters = (char*)std::realloc(characters, total2+1);
		const char* newChars = [str UTF8String];
		for(size_t i=0; i<total2; i++)
		{
			characters[i] = newChars[i];
		}
		characters[total2] = '\0';
		total = total2;
		return *this;
	}
	
	String operator+(const String&left, const NSString*&right)
	{
		String str;
		size_t total2 = left.total + (size_t)[right length];
		const char* right_chars = [right UTF8String];
		str.characters = (char*)std::realloc(str.characters, total2+1);
		for(size_t i=0; i<left.total; i++)
		{
			str.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=(left.total+1); i<total2; i++)
		{
			str.characters[i] = right_chars[counter];
			counter++;
		}
		str.characters[total2] = '\0';
		str.total = total2;
		return str;
	}
	
	String operator+(const NSString*&left, const String&right)
	{
		String str;
		size_t left_total = (size_t)[left length];
		size_t total2 = (size_t)[left length] + right.total;
		const char* left_chars = [left UTF8String];
		str.characters = (char*)std::realloc(str.characters, total2+1);
		for(size_t i=0; i<left_total; i++)
		{
			str.characters[i] = left_chars[i];
		}
		size_t counter = 0;
		for(size_t i=(left_total+1); i<total2; i++)
		{
			str.characters[i] = right.characters[counter];
			counter++;
		}
		str.characters[total2] = '\0';
		str.total = total2;
		return str;
	}
	
#ifdef _STRING_USES_GAMELIBRARY
}
#endif

#endif
