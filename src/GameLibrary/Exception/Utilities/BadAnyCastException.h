
#include "../BadCastException.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate failed Any::as cast of an Any value. */
	class BadAnyCastException : public BadCastException
	{
	public:
		BadAnyCastException(const BadAnyCastException&);
		BadAnyCastException(const String&casttype);
		virtual ~BadAnyCastException();
	};
}