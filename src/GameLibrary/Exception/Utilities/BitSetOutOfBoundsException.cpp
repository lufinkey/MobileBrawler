
#include "BitSetOutOfBoundsException.h"

namespace GameLibrary
{
	BitSetOutOfBoundsException::BitSetOutOfBoundsException(const BitSetOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
	}

	BitSetOutOfBoundsException::BitSetOutOfBoundsException(unsigned int i) : OutOfBoundsException((String)"index " + i + " is out of bounds. The max index in a BitSet is 7. All BitSet objects have a length of 8")
	{
		index = i;
	}

	BitSetOutOfBoundsException::~BitSetOutOfBoundsException()
	{
		//
	}
}
