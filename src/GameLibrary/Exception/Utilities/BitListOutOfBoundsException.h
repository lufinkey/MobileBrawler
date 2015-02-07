
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to a BitList was out of bounds*/
	class BitListOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! The index that was out of range*/
		unsigned int index;
		/*! The index of the byte out of range*/
		unsigned int byteIndex;
		/*! The index of the bit, within the byte, that was out of range*/
		unsigned int bitIndex;
		/*! The size of the BitList*/
		unsigned int size;
		
		/*! copy constructor*/
		BitListOutOfBoundsException(const BitListOutOfBoundsException&);
		/*! Constructs an exception with a BitList index and size.
			\param index the index that was out of bounds
			\param size the size of the BitList*/
		BitListOutOfBoundsException(unsigned int index, unsigned int size);
		/*! Constructs an exception with a BitList byte index, bit index, and size.
			\param byteIndex the byte index
			\param bitIndex the bit index in the byte
			\param size the size of the BitList*/
		BitListOutOfBoundsException(unsigned int byteIndex, unsigned int bitIndex, unsigned int size);
		/*! virtual destructor*/
		virtual ~BitListOutOfBoundsException();
		/*! assignment operator*/
		BitListOutOfBoundsException& operator=(const BitListOutOfBoundsException&);
	};
}
