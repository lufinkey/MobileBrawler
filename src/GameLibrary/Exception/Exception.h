
#include "../Utilities/String.h"

#pragma once

namespace GameLibrary
{
	/* An class to throw when a generic error arises */
	class Exception
	{
	public:
		String message;

		Exception();
		Exception(const Exception&);
		Exception(const String&message);
		virtual ~Exception();
	};
}