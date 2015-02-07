
#pragma once

#include "Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index of some sort (such as to an array, to a string, or to a vector) is out of bounds*/
	class OutOfBoundsException : public Exception
	{
	public:
		/*! copy constructor*/
		OutOfBoundsException(const OutOfBoundsException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		OutOfBoundsException(const String&message);
		/*! virtual destructor*/
		virtual ~OutOfBoundsException();
		/*! assignment operator*/
		OutOfBoundsException& operator=(const OutOfBoundsException&);
	};
}