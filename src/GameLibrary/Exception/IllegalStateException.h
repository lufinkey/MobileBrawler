
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	class IllegalStateException : public Exception
	{
	public:
		IllegalStateException(const IllegalStateException&);
		IllegalStateException(const String&message);
		virtual ~IllegalStateException();
	};
}
