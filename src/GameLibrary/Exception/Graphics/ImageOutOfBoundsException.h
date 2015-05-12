
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a call to Image::getPixel, Image::setPixel, or TextureImage::checkPixel is out of bounds*/
	class ImageOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! The out of bounds index*/
		unsigned int index;
		/*! the x pixel*/
		unsigned int x;
		/*! the y pixel*/
		unsigned int y;
		
		/*! the size of the image (width * height)*/
		unsigned int size;
		/*! the width of the image*/
		unsigned int width;
		/*! the height of the image*/
		unsigned int height;
		
		/*! copy constructor*/
		ImageOutOfBoundsException(const ImageOutOfBoundsException&);
		/*! Constructs an exception for an x,y coordinate, and a width and height of an image.
			\param x the x pixel
			\param y the y pixel
			\param width the width of the image
			\param height the height of the image*/
		ImageOutOfBoundsException(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		/*! Constructs an exception for the pixel index and a width and height of an image.
			\param index the pixel index
			\param width the width of the image
			\param height the height of the image*/
		ImageOutOfBoundsException(unsigned int index, unsigned int width, unsigned int height);
		/*! virtual destruction*/
		virtual ~ImageOutOfBoundsException();
		/*! assignment operator*/
		ImageOutOfBoundsException& operator=(const ImageOutOfBoundsException&);
		
		/*! \copydoc GameLibrary::Exception::getClassName()const*/
		virtual String getClassName() const override;
	};
}
