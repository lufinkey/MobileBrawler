
#include "Exception.h"

namespace GameLibrary
{
	Exception::Exception()
	{
		message = "";
	}

	Exception::Exception(const Exception&exception) : std::exception(exception)
	{
		message = exception.message;
	}

	Exception::Exception(const String& msg)
#ifdef _MSC_VER
		: std::exception(msg)
#endif
	{
		message = msg;
	}

	Exception::~Exception()
	{
		//
	}

	const char* Exception::what() const _NOEXCEPT
	{
		return message;
	}
}