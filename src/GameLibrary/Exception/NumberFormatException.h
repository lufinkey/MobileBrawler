
#include "IllegalArgumentException.h"

#pragma once

namespace GameLibrary
{
	///Thrown to indicate that the application has attempted to convert a string to one of the numeric types,
	///but that the string does not have the appropriate format.
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