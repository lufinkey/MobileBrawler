
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	class UnsupportedImageFormatException : public Exception
	{
	public:
		String format;

		UnsupportedImageFormatException(const UnsupportedImageFormatException&);
		UnsupportedImageFormatException(const String& format);
		virtual ~UnsupportedImageFormatException();
	};
}
