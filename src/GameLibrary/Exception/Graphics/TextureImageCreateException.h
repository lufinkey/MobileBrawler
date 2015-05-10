
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a call to TextureImage::create failed*/
	class TextureImageCreateException : public Exception
	{
	public:
		/*! copy constructor*/
		TextureImageCreateException(const TextureImageCreateException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		explicit TextureImageCreateException(const String&message);
		/*! virtual destructor*/
		virtual ~TextureImageCreateException();
		/*! assignment operator*/
		TextureImageCreateException& operator=(const TextureImageCreateException&);
	};
}
