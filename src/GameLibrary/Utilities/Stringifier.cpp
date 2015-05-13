
#include "Stringifier.h"

namespace GameLibrary
{
	typedef const char* string_ptr;

	template<>
	String Stringifier<string_ptr>::convertToString(const string_ptr* value)
	{
		if(value == nullptr)
		{
			return "null";
		}
		else if((*value) == nullptr)
		{
			return "";
		}
		else
		{
			return (*value);
		}
	}
	
	template<>
	String Stringifier<bool>::convertToString(const bool*value)
	{
		if(value == nullptr)
		{
			return "null";
		}
		if((*value))
		{
			return "true";
		}
		return "false";
	}
}
