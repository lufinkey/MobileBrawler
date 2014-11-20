
#include "BadCastException.h"

#pragma once

namespace GameLibrary
{
	class BadAnyCastException : public BadCastException
	{
	public:
		BadAnyCastException(const BadAnyCastException&);
		BadAnyCastException(const String&casttype);
		virtual ~BadAnyCastException();
	};
}