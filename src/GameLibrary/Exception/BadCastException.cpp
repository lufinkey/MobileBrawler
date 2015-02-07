
#include "BadCastException.h"

namespace GameLibrary
{
	BadCastException::BadCastException(const BadCastException&exception) : Exception(exception)
	{
		originalType = exception.originalType;
		castedType = exception.castedType;
	}

	BadCastException::BadCastException(const String&origType, const String&castType) : Exception((String)"Bad cast from type " + origType + " to type " + castType)
	{
		originalType = origType;
		castedType = castType;
	}

	BadCastException::~BadCastException()
	{
		//
	}
	
	BadCastException& BadCastException::operator=(const BadCastException&exception)
	{
		Exception::operator=(exception);
		originalType = exception.originalType;
		castedType = exception.castedType;
		return *this;
	}
}