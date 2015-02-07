
#include "BadAnyCastException.h"

namespace GameLibrary
{
	BadAnyCastException::BadAnyCastException(const BadAnyCastException&exception) : BadCastException(exception)
	{
		//
	}
	
	BadAnyCastException::BadAnyCastException(const String&casttype) : BadCastException("Any", casttype)
	{
		//
	}
	
	BadAnyCastException::~BadAnyCastException()
	{
		//
	}
	
	BadAnyCastException& BadAnyCastException::operator=(const BadAnyCastException&exception)
	{
		BadCastException::operator=(exception);
		return *this;
	}
}