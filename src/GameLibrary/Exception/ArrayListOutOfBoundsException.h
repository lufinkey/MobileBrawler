
#include "OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
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