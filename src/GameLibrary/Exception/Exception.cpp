
#include "Exception.h"

namespace GameLibrary
{
	Exception::Exception()
	{
		message = "";
	}

	Exception::Exception(const Exception&exception)
	{
		message = exception.message;
	}

	Exception::Exception(const String& msg)
	{
		message = msg;
	}

	Exception::~Exception()
	{
		//
	}
}