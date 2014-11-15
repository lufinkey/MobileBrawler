
#include "../Utilities/String.h"

#pragma once

namespace GameLibrary
{
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