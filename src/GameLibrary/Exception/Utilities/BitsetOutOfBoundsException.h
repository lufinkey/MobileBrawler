
#include "../OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate that an index to a BitSet is out of range. */
	class BitSetOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;

		BitSetOutOfBoundsException(const BitSetOutOfBoundsException&);
		BitSetOutOfBoundsException(unsigned int index);
		virtual ~BitSetOutOfBoundsException();
	};
}