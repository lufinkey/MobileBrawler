
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	class InitializeLibraryException : public Exception
	{
	public:
		String library;

		InitializeLibraryException(const InitializeLibraryException&);
		InitializeLibraryException(const String&library, const String&message);
		virtual ~InitializeLibraryException();
	};
}
