
#include "../OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	///Thrown to indicate that an index to a String is out of range.
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