
#include "OutOfBoundsException.h"

namespace GameLibrary
{
	OutOfBoundsException::OutOfBoundsException(const OutOfBoundsException&exception) : Exception(exception)
	{
		//
	}

	OutOfBoundsException::OutOfBoundsException(const String& message) : Exception(message)
	{
		//
	}

	OutOfBoundsException::~OutOfBoundsException()
	{
		//
	}
}
