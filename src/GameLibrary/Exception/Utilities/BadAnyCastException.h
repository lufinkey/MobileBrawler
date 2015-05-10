
#pragma once

#include "../BadCastException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that casting an Any object failed*/
	class BadAnyCastException : public BadCastException
	{
	public:
		/*! copy constructor*/
		BadAnyCastException(const BadAnyCastException&);
		/*! Constructs an exception with a casted type string.
			\param casttype the type that the Any object was cast as*/
		explicit BadAnyCastException(const String&casttype);
		/*! virtual destructor*/
		virtual ~BadAnyCastException();
		/*! assignment operator*/
		BadAnyCastException& operator=(const BadAnyCastException&);
	};
}