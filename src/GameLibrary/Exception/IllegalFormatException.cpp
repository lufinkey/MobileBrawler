
#include "IllegalFormatException.h"

namespace GameLibrary
{
	IllegalFormatException::IllegalFormatException(const String&message) : IllegalArgumentException("format", message)
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

	IllegalFormatException& IllegalFormatException::operator=(const IllegalFormatException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
	
	MEMBERFUNC_GETCLASSNAME(IllegalFormatException)
}