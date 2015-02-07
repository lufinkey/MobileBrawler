
#pragma once

#include "IllegalArgumentException.h"

namespace GameLibrary
{
	/*! Thrown to indicate a format string contains an illegal syntax or a format specifier that is incompatible with the given arguments.
	Only explicit subtypes of this exception which correspond to specific errors should be instantiated.*/
	class IllegalFormatException : public IllegalArgumentException
	{
	protected:
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		IllegalFormatException(const String&message);
		
	public:
		/*! copy constructor*/
		IllegalFormatException(const IllegalFormatException&);
		/*! virtual destructor*/
		virtual ~IllegalFormatException();
		/*! assignment operator*/
		IllegalFormatException& operator=(const IllegalFormatException&);
	};
}