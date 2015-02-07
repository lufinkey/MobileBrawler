
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to an ArrayList was out of bounds*/
	class ArrayListOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! the out of bounds index*/
		unsigned int index;
		/*! the size of the ArrayList*/
		unsigned int size;
		
		/*! copy constructor*/
		ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&);
		/*! Constructs an exception with an ArrayList index and size
			\param index the index in the ArrayList
			\param size the size of the ArrayList*/
		ArrayListOutOfBoundsException(unsigned int index, unsigned int size);
		/*! virtual destructor*/
		virtual ~ArrayListOutOfBoundsException();
		/*! assignment operator*/
		ArrayListOutOfBoundsException& operator=(const ArrayListOutOfBoundsException&);
	};
}
