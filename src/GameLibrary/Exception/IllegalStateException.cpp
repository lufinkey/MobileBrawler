
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
	
	IllegalStateException& IllegalStateException::operator=(const IllegalStateException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
}
