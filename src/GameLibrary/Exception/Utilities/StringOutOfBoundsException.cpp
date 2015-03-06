
#include "StringOutOfBoundsException.h"

namespace GameLibrary
{
	StringOutOfBoundsException::StringOutOfBoundsException(const StringOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		length = exception.length;
	}

	StringOutOfBoundsException::StringOutOfBoundsException(size_t i, size_t l) : OutOfBoundsException((String)"index " + i + " is out of bounds in String with a length of " + l)
	{
		index = i;
		length = l;
	}

	StringOutOfBoundsException::~StringOutOfBoundsException()
	{
		//
	}
	
	StringOutOfBoundsException& StringOutOfBoundsException::operator=(const StringOutOfBoundsException&exception)
	{
		OutOfBoundsException::operator=(exception);
		index = exception.index;
		length = exception.length;
		return *this;
	}
}