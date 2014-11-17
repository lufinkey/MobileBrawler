
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	class BadAnyCastException : public Exception
	{
	public:
		String type;

		BadAnyCastException(const BadAnyCastException&);
		BadAnyCastException(const String&type);
		virtual ~BadAnyCastException();
	};
}