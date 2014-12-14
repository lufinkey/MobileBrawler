
#include "IllegalStateException.h"

namespace GameLibrary
{
	IllegalStateException::IllegalStateException(const IllegalStateException&exception) : Exception(exception)
	{
		//
	}

	IllegalStateException::IllegalStateException(const String&message) : Exception(message)
	{
		//
	}

	IllegalStateException::~IllegalStateException()
	{
		//
	}
}
