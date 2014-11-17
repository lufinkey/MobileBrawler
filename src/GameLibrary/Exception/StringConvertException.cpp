
#include "StringConvertException.h"

namespace GameLibrary
{
	StringConvertException::StringConvertException(const StringConvertException&exception) : Exception(exception)
	{
		type = exception.type;
		reason = exception.reason;
	}

	StringConvertException::StringConvertException(const String& t, const String& r) : Exception((String)"Unable to convert String to type " + t + ": " + r)
	{
		type = t;
		reason = r;
	}
	
	StringConvertException::~StringConvertException()
	{
		//
	}
}
