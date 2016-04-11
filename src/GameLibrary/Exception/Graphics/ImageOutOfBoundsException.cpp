
#include "ImageOutOfBoundsException.h"

namespace GameLibrary
{
	ImageOutOfBoundsException::ImageOutOfBoundsException(const ImageOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		x = exception.x;
		y = exception.y;
		size = exception.size;
		width = exception.width;
		height = exception.height;
	}

	ImageOutOfBoundsException::ImageOutOfBoundsException(unsigned int ptx, unsigned int pty, unsigned int w, unsigned int h) : OutOfBoundsException((String)"(" + ptx + ", " + pty + ") is out of bounds in Image with a size of (" + w + ", " + h + ")")
	{
		index = (w*pty)+ptx;
		x = ptx;
		y = pty;
		size = w*h;
		width = w;
		height = h;
	}

	ImageOutOfBoundsException::ImageOutOfBoundsException(unsigned int i, unsigned int w, unsigned int h) : OutOfBoundsException((String)"(" + (i%w) + ", " + ((int)(i / w)) + ") is out of bounds in Image with a size of (" + w + ", " + h + ")")
	{
		index = i;
		x = index%w;
		y = (int)(i/w);
		size = w*h;
		width = w;
		height = h;
	}

	ImageOutOfBoundsException::~ImageOutOfBoundsException()
	{
		//
	}
	
	ImageOutOfBoundsException& ImageOutOfBoundsException::operator=(const ImageOutOfBoundsException&exception)
	{
		OutOfBoundsException::operator=(exception);
		index = exception.index;
		x = exception.x;
		y = exception.y;
		size = exception.size;
		width = exception.width;
		height = exception.height;
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(ImageOutOfBoundsException)
}
