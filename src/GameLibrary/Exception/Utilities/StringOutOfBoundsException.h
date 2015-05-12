
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to a String was out of bounds*/
	class StringOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! The index in the string*/
		size_t index;
		/*! The length of the string*/
		size_t length;
		
		/*! copy constructor*/
		StringOutOfBoundsException(const StringOutOfBoundsException&);
		/*! Constructs an exception with a String index and length.
			\param index the index in the String
			\param length the length of the String*/
		StringOutOfBoundsException(size_t index, size_t length);
		/*! virtual destructor*/
		virtual ~StringOutOfBoundsException();
		/*! assignment operator*/
		StringOutOfBoundsException& operator=(const StringOutOfBoundsException&);
		
		/*! \copydoc GameLibrary::Exception::getClassName()const*/
		virtual String getClassName() const override;
	};
}