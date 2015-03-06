
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to a BitList was out of bounds*/
	class BitListOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! The index that was out of range*/
		size_t index;
		/*! The index of the byte out of range*/
		size_t byteIndex;
		/*! The index of the bit, within the byte, that was out of range*/
		size_t bitIndex;
		/*! The size of the BitList*/
		size_t size;
		
		/*! copy constructor*/
		BitListOutOfBoundsException(const BitListOutOfBoundsException&);
		/*! Constructs an exception with a BitList index and size.
			\param index the index that was out of bounds
			\param size the size of the BitList*/
		BitListOutOfBoundsException(size_t index, size_t size);
		/*! Constructs an exception with a BitList byte index, bit index, and size.
			\param byteIndex the byte index
			\param bitIndex the bit index in the byte
			\param size the size of the BitList*/
		BitListOutOfBoundsException(size_t byteIndex, size_t bitIndex, size_t size);
		/*! virtual destructor*/
		virtual ~BitListOutOfBoundsException();
		/*! assignment operator*/
		BitListOutOfBoundsException& operator=(const BitListOutOfBoundsException&);
	};
}
