
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate that an index of some sort (such as to an array, to a string, or to a vector) is out of range. */
	class OutOfBoundsException : public Exception
	{
	public:
		OutOfBoundsException(const OutOfBoundsException&);
		OutOfBoundsException(const String&message);
		virtual ~OutOfBoundsException();
	};
}