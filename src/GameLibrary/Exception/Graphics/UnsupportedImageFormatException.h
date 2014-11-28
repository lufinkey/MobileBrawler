
#include "../Exception.h"

#pragma once

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
