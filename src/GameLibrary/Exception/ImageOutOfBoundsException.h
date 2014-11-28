
#include "OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class ImageOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;
		unsigned int x;
		unsigned int y;

		unsigned int size;
		unsigned int width;
		unsigned int height;

		ImageOutOfBoundsException(const ImageOutOfBoundsException&);
		ImageOutOfBoundsException(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		ImageOutOfBoundsException(unsigned int index, unsigned int width, unsigned int height);
		virtual ~ImageOutOfBoundsException();
	};
}
