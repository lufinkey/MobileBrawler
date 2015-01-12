
#pragma once

#include "../Exception.h"

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
