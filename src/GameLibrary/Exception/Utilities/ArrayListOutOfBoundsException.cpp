
#include "ArrayListOutOfBoundsException.h"

namespace GameLibrary
{
	ArrayListOutOfBoundsException::ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		size = exception.size;
	}
	
	ArrayListOutOfBoundsException::ArrayListOutOfBoundsException(unsigned int i, unsigned int s) : OutOfBoundsException((String)"index " + i + " is out of bounds in ArrayList with a size of " + s)
	{
		index = i;
		size = s;
	}
	
	ArrayListOutOfBoundsException::~ArrayListOutOfBoundsException()
	{
		//
	}
	
	ArrayListOutOfBoundsException& ArrayListOutOfBoundsException::operator=(const ArrayListOutOfBoundsException&exception)
	{
		OutOfBoundsException::operator=(exception);
		index = exception.index;
		size = exception.size;
		return *this;
	}
}
