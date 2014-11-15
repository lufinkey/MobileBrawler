
#include "OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class StringOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;
		unsigned int length;

		StringOutOfBoundsException(const StringOutOfBoundsException&);
		StringOutOfBoundsException(unsigned int index, unsigned int length);
		virtual ~StringOutOfBoundsException();
	};
}