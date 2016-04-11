
#include "IllegalArgumentException.h"

namespace GameLibrary
{
	IllegalArgumentException::IllegalArgumentException(const IllegalArgumentException&exception) : Exception(exception)
	{
		//
	}

	IllegalArgumentException::IllegalArgumentException(const String&arg, const String&reason) : Exception("argument " + arg + " is not a valid argument: " + reason)
	{
		argument = arg;
	}

	IllegalArgumentException::~IllegalArgumentException()
	{
		//
	}
	
	IllegalArgumentException& IllegalArgumentException::operator=(const IllegalArgumentException&exception)
	{
		Exception::operator=(exception);
		argument = exception.argument;
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(IllegalArgumentException)
}