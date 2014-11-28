
#include "StringOutOfBoundsException.h"

namespace GameLibrary
{
	StringOutOfBoundsException::StringOutOfBoundsException(const StringOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		length = exception.length;
	}

	StringOutOfBoundsException::StringOutOfBoundsException(unsigned int i, unsigned int l) : OutOfBoundsException((String)"index " + i + " is out of bounds in String with a length of " + l)
	{
		index = i;
		length = l;
	}

	StringOutOfBoundsException::~StringOutOfBoundsException()
	{
		//
	}
}