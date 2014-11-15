
#include "ArrayListOutOfBoundsException.h"

namespace GameLibrary
{
	ArrayListOutOfBoundsException::ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&exception)
	{
		index = exception.index;
		size = exception.size;
	}
	
	ArrayListOutOfBoundsException::ArrayListOutOfBoundsException(unsigned int i, unsigned int s)
	{
		index = i;
		size = s;
	}
	
	ArrayListOutOfBoundsException::~ArrayListOutOfBoundsException()
	{
		//
	}
}
