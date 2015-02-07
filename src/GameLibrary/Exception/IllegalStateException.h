
#pragma once

#include "Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a function has been invoked at an illegal or inappropriate time.*/
	class IllegalStateException : public Exception
	{
	public:
		IllegalStateException(const IllegalStateException&);
		IllegalStateException(const String&message);
		virtual ~IllegalStateException();
	};
}
