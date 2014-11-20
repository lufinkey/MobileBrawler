
#include "IllegalDateTimeFormatException.h"

namespace GameLibrary
{
	IllegalDateTimeFormatException::IllegalDateTimeFormatException(const IllegalDateTimeFormatException&exception) : IllegalFormatException(exception)
	{
		datestring = exception.datestring;
		dateformat = exception.dateformat;
		index = exception.index;
	}

	IllegalDateTimeFormatException::IllegalDateTimeFormatException(const String&datestr, const String&dateform, unsigned int i) : IllegalFormatException((String)"Illegal character or end of string at index " + i + " in date string \"" + datestr + "\" with format \"" + dateform + "\"")
	{
		datestring = datestr;
		dateformat = dateform;
		index = i;
	}

	IllegalDateTimeFormatException::~IllegalDateTimeFormatException()
	{
		//
	}
}
