
#include "StringConvertException.h"

namespace GameLibrary
{
	StringConvertException::StringConvertException(const StringConvertException&exception) : Exception(exception)
	{
		//
	}

	StringConvertException::StringConvertException(const String& str, const String& type, const String& reason) : Exception((String)"Unable to convert String \"" + str + "\" to type " + type + ": " + reason)
	{
		//
	}
	
	StringConvertException::~StringConvertException()
	{
		//
	}
}
