
#include "../Utilities/String.h"
#include <exception>

#pragma once

namespace GameLibrary
{
	/* An class to throw when a generic error arises */
	class Exception : std::exception
	{
	public:
		String message;

		Exception();
		Exception(const Exception&);
		Exception(const String&message);
		virtual ~Exception();

		virtual const char* what() const;
	};
}