
#pragma once

#include "Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a value was cast to an invalid type*/
	class BadCastException : public Exception
	{
	public:
		/*! The class or primitive type of the original value*/
		String originalType;
		/*! The cast type*/
		String castedType;
		
		/*! copy constructor*/
		BadCastException(const BadCastException&);
		/*! Constructs an exception with an original type and a cast type.
			\param originalType the class or primitive type of the original value
			\param castedType the type casted on the original value*/
		BadCastException(const String&originalType, const String&castedType);
		/*! virtual destructor*/
		virtual ~BadCastException();
		/*! assignment operator*/
		BadCastException& operator=(const BadCastException&);
		
		/*! \copydoc GameLibrary::Exception::getClassName()const*/
		virtual String getClassName() const override;
	};
}