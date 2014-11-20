
#include "Exception.h"

#pragma once

namespace GameLibrary
{
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