
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	class StringConvertException : public Exception
	{
	public:
		StringConvertException(const StringConvertException&);
		StringConvertException(const String& type, const String& reason);
		virtual ~StringConvertException();
	};
}