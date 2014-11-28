
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate an illegal cast of a value. */
	class BadCastException : public Exception
	{
	public:
		String originalType;
		String castedType;

		BadCastException(const BadCastException&);
		BadCastException(const String&originalType, const String&castedType);
		virtual ~BadCastException();
	};
}