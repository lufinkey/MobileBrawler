
#pragma once

#include "IllegalArgumentException.h"

namespace GameLibrary
{
	/* Thrown to indicate that the application has attempted to convert a String to a numeric type, but that the String does not have the appropriate format. */
	class NumberFormatException : public IllegalArgumentException
	{
	public:
		String type;
		String reason;

		NumberFormatException(const NumberFormatException&);
		NumberFormatException(const String& type, const String& reason);
		virtual ~NumberFormatException();
	};
}