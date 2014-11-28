
#include "../OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate that an index to a BitList is out of range. */
	class BitListOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;
		unsigned int byteIndex;
		unsigned int bitIndex;
		unsigned int size;
		
		BitListOutOfBoundsException(const BitListOutOfBoundsException&);
		BitListOutOfBoundsException(unsigned int index, unsigned int size);
		BitListOutOfBoundsException(unsigned int byteIndex, unsigned int bitIndex, unsigned int size);
		virtual ~BitListOutOfBoundsException();
	};
}
