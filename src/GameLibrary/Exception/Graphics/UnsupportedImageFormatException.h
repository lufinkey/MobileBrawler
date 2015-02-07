
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	/* Thrown to indicate that Image::saveToFile tried to use an unsupported image format
		\see Image::saveToFile(const String&,String*)const*/
	class UnsupportedImageFormatException : public Exception
	{
	public:
		/*! the unsupported image extension*/
		String format;
		
		/*! copy constructor*/
		UnsupportedImageFormatException(const UnsupportedImageFormatException&);
		/*! Constructs an exception with the unsupported image extensions.
			\param format the file extension that was unsupported by Image::saveToFile*/
		UnsupportedImageFormatException(const String& format);
		/*! virtual destructor*/
		virtual ~UnsupportedImageFormatException();
		/*! assignment operator*/
		UnsupportedImageFormatException& operator=(const UnsupportedImageFormatException&);
	};
}
