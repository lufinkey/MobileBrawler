
#include "NumberFormatException.h"

namespace GameLibrary
{
	NumberFormatException::NumberFormatException(const NumberFormatException&exception) : IllegalArgumentException(exception)
	{
		type = exception.type;
		reason = exception.reason;
	}

	NumberFormatException::NumberFormatException(const String& t, const String& r) : IllegalArgumentException("format", (String)"Unable to convert String to type " + t + ": " + r)
	{
		type = t;
		reason = r;
	}
	
	NumberFormatException::~NumberFormatException()
	{
		//
	}
	
	NumberFormatException& NumberFormatException::operator=(const NumberFormatException&exception)
	{
		IllegalArgumentException::operator=(exception);
		type = exception.type;
		reason = exception.reason;
		return *this;
	}
}
