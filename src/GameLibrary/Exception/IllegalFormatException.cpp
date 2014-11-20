
#include "IllegalFormatException.h"

namespace GameLibrary
{
	IllegalFormatException::IllegalFormatException(const String&message) : IllegalArgumentException(message)
	{
		//
	}

	IllegalFormatException::IllegalFormatException(const IllegalFormatException&exception) : IllegalArgumentException(exception)
	{
		//
	}

	IllegalFormatException::~IllegalFormatException()
	{
		//
	}
}