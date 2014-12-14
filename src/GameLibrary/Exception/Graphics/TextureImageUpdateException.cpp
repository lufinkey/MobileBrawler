
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
}
