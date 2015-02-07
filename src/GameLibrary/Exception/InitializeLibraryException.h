
#pragma once

#include "Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an error occurred while initializing a base Application library*/
	class InitializeLibraryException : public Exception
	{
	public:
		/*! The name of the library that threw an error*/
		String library;
		
		/*! copy constructor*/
		InitializeLibraryException(const InitializeLibraryException&);
		/*! Constructs an exception with a library name and an error message.
			\param library the name of the library that threw an error
			\param message an explanation of the error*/
		InitializeLibraryException(const String&library, const String&message);
		/*! virtual destructor*/
		virtual ~InitializeLibraryException();
		/*! assignment operator*/
		InitializeLibraryException& operator=(const InitializeLibraryException&);
	};
}
