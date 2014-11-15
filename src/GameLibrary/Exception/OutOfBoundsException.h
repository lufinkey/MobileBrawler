
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	class OutOfBoundsException : public Exception
	{
	public:
		OutOfBoundsException(const OutOfBoundsException&);
		OutOfBoundsException(const String&message);
		virtual ~OutOfBoundsException();
	};
}