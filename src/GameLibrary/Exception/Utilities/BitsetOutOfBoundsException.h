
#include "../OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class BitsetOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;

		BitsetOutOfBoundsException(const BitsetOutOfBoundsException&);
		BitsetOutOfBoundsException(unsigned int index);
		virtual ~BitsetOutOfBoundsException();
	};
}