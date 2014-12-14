
#include "../Exception.h"

#pragma once

namespace GameLibrary
{
	class TextureImageCreateException : public Exception
	{
	public:
		TextureImageCreateException(const TextureImageCreateException&);
		TextureImageCreateException(const String&message);
		virtual ~TextureImageCreateException();
	};
}
