
#include "TextureImageCreateException.h"

namespace GameLibrary
{
	TextureImageCreateException::TextureImageCreateException(const TextureImageCreateException&exception) : Exception(exception)
	{
		//
	}

	TextureImageCreateException::TextureImageCreateException(const String&message) : Exception(message)
	{
		//
	}

	TextureImageCreateException::~TextureImageCreateException()
	{
		//
	}

	TextureImageCreateException& TextureImageCreateException::operator=(const TextureImageCreateException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
	
	MEMBERFUNC_GETCLASSNAME(TextureImageCreateException)
}
