
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that a call to TextureImage::update failed*/
	class TextureImageUpdateException : public Exception
	{
	public:
		/*! copy constructor*/
		TextureImageUpdateException(const TextureImageUpdateException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		TextureImageUpdateException(const String&message);
		/*! virtual destructor*/
		virtual ~TextureImageUpdateException();
		/*! assignment operator*/
		TextureImageUpdateException& operator=(const TextureImageUpdateException&);
	};
}
