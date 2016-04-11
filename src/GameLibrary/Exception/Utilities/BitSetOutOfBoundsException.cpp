
#include "BitSetOutOfBoundsException.h"

namespace GameLibrary
{
	BitSetOutOfBoundsException::BitSetOutOfBoundsException(const BitSetOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
	}

	BitSetOutOfBoundsException::BitSetOutOfBoundsException(size_t i) : OutOfBoundsException((String)"index " + i + " is out of bounds. The max index in a BitSet is 7. All BitSet objects have a length of 8")
	{
		index = i;
	}

	BitSetOutOfBoundsException::~BitSetOutOfBoundsException()
	{
		//
	}
	
	BitSetOutOfBoundsException& BitSetOutOfBoundsException::operator=(const BitSetOutOfBoundsException&exception)
	{
		OutOfBoundsException::operator=(exception);
		index = exception.index;
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(BitSetOutOfBoundsException)
}
