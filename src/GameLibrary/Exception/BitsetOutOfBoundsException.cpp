
#include "BitsetOutOfBoundsException.h"

namespace GameLibrary
{
	BitsetOutOfBoundsException::BitsetOutOfBoundsException(const BitsetOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
	}

	BitsetOutOfBoundsException::BitsetOutOfBoundsException(unsigned int i) : OutOfBoundsException((String)"index " + i + " is out of bounds. The max index in a Bitset is 7. All Bitset objects have a length of 8")
	{
		index = i;
	}

	BitsetOutOfBoundsException::~BitsetOutOfBoundsException()
	{
		//
	}
}