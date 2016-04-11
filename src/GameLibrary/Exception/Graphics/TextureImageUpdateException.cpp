
#include "TextureImageUpdateException.h"

namespace GameLibrary
{
	TextureImageUpdateException::TextureImageUpdateException(const TextureImageUpdateException&exception) : Exception(exception)
	{
		//
	}

	TextureImageUpdateException::TextureImageUpdateException(const String&message) : Exception(message)
	{
		//
	}

	TextureImageUpdateException::~TextureImageUpdateException()
	{
		//
	}
	
	TextureImageUpdateException& TextureImageUpdateException::operator=(const TextureImageUpdateException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(TextureImageUpdateException)
}
