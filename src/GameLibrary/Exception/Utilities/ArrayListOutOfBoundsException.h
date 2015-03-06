
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to an ArrayList was out of bounds*/
	class ArrayListOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! the out of bounds index*/
		size_t index;
		/*! the size of the ArrayList*/
		size_t size;
		
		/*! copy constructor*/
		ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&);
		/*! Constructs an exception with an ArrayList index and size
			\param index the index in the ArrayList
			\param size the size of the ArrayList*/
		ArrayListOutOfBoundsException(size_t index, size_t size);
		/*! virtual destructor*/
		virtual ~ArrayListOutOfBoundsException();
		/*! assignment operator*/
		ArrayListOutOfBoundsException& operator=(const ArrayListOutOfBoundsException&);
	};
}
