
#include "../Types.h"
#include "OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class BitsetOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;

		BitsetOutOfBoundsException(unsigned int index);
		BitsetOutOfBoundsException(const BitsetOutOfBoundsException&);
		virtual ~BitsetOutOfBoundsException();
	};
}