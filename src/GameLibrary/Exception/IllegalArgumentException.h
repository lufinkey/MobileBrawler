
#pragma once

#include "Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a function has been passed an illegal or inappropriate argument*/
	class IllegalArgumentException : public Exception
	{
	public:
		/*! default constructor*/
		IllegalArgumentException();
		/*! copy constructor*/
		IllegalArgumentException(const IllegalArgumentException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		IllegalArgumentException(const String&message);
		/*! virtual destructor*/
		virtual ~IllegalArgumentException();
		/*! assignment operator*/
		IllegalArgumentException& operator=(const IllegalArgumentException&);
	};
}