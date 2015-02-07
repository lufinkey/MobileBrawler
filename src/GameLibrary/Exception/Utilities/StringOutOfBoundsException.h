
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to a String was out of bounds*/
	class StringOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! The index in the string*/
		unsigned int index;
		/*! The length of the string*/
		unsigned int length;
		
		/*! copy constructor*/
		StringOutOfBoundsException(const StringOutOfBoundsException&);
		/*! Constructs an exception with a String index and length.
			\param index the index in the String
			\param length the length of the String*/
		StringOutOfBoundsException(unsigned int index, unsigned int length);
		/*! virtual destructor*/
		virtual ~StringOutOfBoundsException();
		/*! assignment operator*/
		StringOutOfBoundsException& operator=(const StringOutOfBoundsException&);
	};
}