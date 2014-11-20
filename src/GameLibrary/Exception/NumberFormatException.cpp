
#include "NumberFormatException.h"

namespace GameLibrary
{
	NumberFormatException::NumberFormatException(const NumberFormatException&exception) : IllegalArgumentException(exception)
	{
		type = exception.type;
		reason = exception.reason;
	}

	NumberFormatException::NumberFormatException(const String& t, const String& r) : IllegalArgumentException((String)"Unable to convert String to type " + t + ": " + r)
	{
		type = t;
		reason = r;
	}
	
	NumberFormatException::~NumberFormatException()
	{
		//
	}
}
