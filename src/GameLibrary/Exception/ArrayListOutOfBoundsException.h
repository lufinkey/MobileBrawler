
#include "OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	///Thrown to indicate that an index to an ArrayList is out of range.
	class ArrayListOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;
		unsigned int size;
		
		ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&);
		ArrayListOutOfBoundsException(unsigned int index, unsigned int size);
		virtual ~ArrayListOutOfBoundsException();
	};
}