
#include "../Exception.h"

#pragma once

namespace GameLibrary
{
	class TextureImageUpdateException : public Exception
	{
	public:
		TextureImageUpdateException(const TextureImageUpdateException&);
		TextureImageUpdateException(const String&message);
		virtual ~TextureImageUpdateException();
	};
}
