
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to a BitSet was out of bounds*/
	class BitSetOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! the out of bounds index*/
		unsigned int index;
		
		/*! copy constructor*/
		BitSetOutOfBoundsException(const BitSetOutOfBoundsException&);
		/*! Constructs an exception with the BitSet out of bounds index.
			\param index the index in the BitSet*/
		BitSetOutOfBoundsException(unsigned int index);
		/*! virtual destructor*/
		virtual ~BitSetOutOfBoundsException();
		/*! assignment operator*/
		BitSetOutOfBoundsException& operator=(const BitSetOutOfBoundsException&);
	};
}
