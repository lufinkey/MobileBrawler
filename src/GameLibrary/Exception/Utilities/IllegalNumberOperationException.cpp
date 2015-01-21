
#include "IllegalNumberOperationException.h"

namespace GameLibrary
{
	IllegalNumberOperationException::IllegalNumberOperationException()
	{
		//
	}
	
	IllegalNumberOperationException::IllegalNumberOperationException(const IllegalNumberOperationException&exception) : Exception(exception)
	{
		//
	}
	
	IllegalNumberOperationException::IllegalNumberOperationException(const String&operation, const String&type, const String&side) : Exception("Cannot perform operation \"" + operation + "\" on a " + side + " side Number of type \"" + type + "\"")
	{
		//
	}
	
	IllegalNumberOperationException::IllegalNumberOperationException(const String&message) : Exception(message)
	{
		//
	}
	
	IllegalNumberOperationException::~IllegalNumberOperationException()
	{
		//
	}
}