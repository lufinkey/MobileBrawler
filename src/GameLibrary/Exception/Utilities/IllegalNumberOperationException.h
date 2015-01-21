
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	class IllegalNumberOperationException : public Exception
	{
	public:
		IllegalNumberOperationException();
		IllegalNumberOperationException(const IllegalNumberOperationException&);
		IllegalNumberOperationException(const String&operation, const String&type, const String&side);
		IllegalNumberOperationException(const String&message);
		virtual ~IllegalNumberOperationException();
	};
}
