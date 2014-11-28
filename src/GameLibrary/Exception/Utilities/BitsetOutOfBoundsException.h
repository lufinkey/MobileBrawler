
#include "../OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate that an index to a Bitset is out of range. */
	class BitsetOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;

		BitsetOutOfBoundsException(const BitsetOutOfBoundsException&);
		BitsetOutOfBoundsException(unsigned int index);
		virtual ~BitsetOutOfBoundsException();
	};
}