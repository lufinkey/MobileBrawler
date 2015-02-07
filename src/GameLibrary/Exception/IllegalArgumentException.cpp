
#include "IllegalArgumentException.h"

namespace GameLibrary
{
	IllegalArgumentException::IllegalArgumentException() : Exception("An illegal argument was used on a function")
	{
		//
	}

	IllegalArgumentException::IllegalArgumentException(const IllegalArgumentException&exception) : Exception(exception)
	{
		//
	}

	IllegalArgumentException::IllegalArgumentException(const String&message) : Exception(message)
	{
		//
	}

	IllegalArgumentException::~IllegalArgumentException()
	{
		//
	}
	
	IllegalArgumentException& IllegalArgumentException::operator=(const IllegalArgumentException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
}