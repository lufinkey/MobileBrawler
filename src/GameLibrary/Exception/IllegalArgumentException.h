
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	///Thrown to indicate that a function has been passed an illegal or inappropriate argument.
	class IllegalArgumentException : public Exception
	{
	public:
		IllegalArgumentException();
		IllegalArgumentException(const IllegalArgumentException&);
		IllegalArgumentException(const String&message);
		virtual ~IllegalArgumentException();
	};
}