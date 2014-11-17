
#include "BadAnyCastException.h"

namespace GameLibrary
{
	BadAnyCastException::BadAnyCastException(const BadAnyCastException&exception) : Exception(exception)
	{
		type = exception.type;
	}

	BadAnyCastException::BadAnyCastException(const String&t) : Exception((String)"Bad cast from Any to \"" + t)
	{
		type = t;
	}

	BadAnyCastException::~BadAnyCastException()
	{
		//
	}
}