
#include "IllegalArgumentException.h"

namespace GameLibrary
{
	IllegalArgumentException::IllegalArgumentException()
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
}