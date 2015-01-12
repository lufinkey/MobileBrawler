
#pragma once

#include "IllegalArgumentException.h"

namespace GameLibrary
{
	/* Unchecked exception thrown when a format string contains an illegal syntax or a format specifier that is incompatible with the given arguments.
	Only explicit subtypes of this exception which correspond to specific errors should be instantiated. */
	class IllegalFormatException : public IllegalArgumentException
	{
	protected:
		IllegalFormatException(const String&message);

	public:
		IllegalFormatException(const IllegalFormatException&);
		virtual ~IllegalFormatException();
	};
}