
#include "Exception.h"

namespace GameLibrary
{
	Exception::Exception() : Exception("")
	{
		//
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
	
	Exception& Exception::operator=(const Exception&exception)
	{
		message = exception.message;
		return *this;
	}
	
	const char* Exception::what() const _NOEXCEPT
	{
		return message;
	}
	
	String Exception::toString() const
	{
		return what();
	}
	
	MEMBERFUNC_GETCLASSNAME(Exception)
}