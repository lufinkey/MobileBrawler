
#pragma once

#include "Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a function has been invoked at an illegal or inappropriate time*/
	class IllegalStateException : public Exception
	{
	public:
		/*! copy constructor*/
		IllegalStateException(const IllegalStateException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		IllegalStateException(const String&message);
		/*! virtual destructor*/
		virtual ~IllegalStateException();
		/*! assignment operator*/
		IllegalStateException& operator=(const IllegalStateException&);
	};
}
