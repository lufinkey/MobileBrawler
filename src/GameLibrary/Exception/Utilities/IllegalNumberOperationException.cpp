
#include "IllegalNumberOperationException.h"

namespace GameLibrary
{
	IllegalNumberOperationException::IllegalNumberOperationException(const IllegalNumberOperationException&exception) : Exception(exception)
	{
		operatorType = exception.operatorType;
		numberType = exception.numberType;
		side = exception.side;
	}
	
	IllegalNumberOperationException::IllegalNumberOperationException(const String&operatorTp, const String&numberTp, const String&eqSide) : Exception("Cannot perform operation \"" + operatorTp + "\" on a " + eqSide + " side Number of type \"" + numberTp + "\"")
	{
		operatorType = operatorTp;
		numberType = numberTp;
		side = side;
	}
	
	IllegalNumberOperationException::~IllegalNumberOperationException()
	{
		//
	}
	
	IllegalNumberOperationException& IllegalNumberOperationException::operator=(const IllegalNumberOperationException&exception)
	{
		Exception::operator=(exception);
		operatorType = exception.operatorType;
		numberType = exception.numberType;
		side = exception.side;
		return *this;
	}
}