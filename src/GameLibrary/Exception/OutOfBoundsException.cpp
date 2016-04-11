
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
	
	OutOfBoundsException& OutOfBoundsException::operator=(const OutOfBoundsException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(OutOfBoundsException)
}
