
#pragma once

#include "../../IllegalFormatException.h"

namespace GameLibrary
{
	///Thrown to indicate that a DateTime object has been passed an illegal datetime string corresponding to a given datetime format string
	class IllegalDateTimeFormatException : public IllegalFormatException
	{
	public:
		String datestring;
		String dateformat;
		unsigned int index;

		IllegalDateTimeFormatException(const IllegalDateTimeFormatException&);
		IllegalDateTimeFormatException(const String&datestring, const String&dateformat, unsigned int index);
		virtual ~IllegalDateTimeFormatException();
	};
}