
#include "Exception.h"

#pragma once

namespace GameLibrary
{
	class StringConvertException : public Exception
	{
	public:
		String type;
		String reason;

		StringConvertException(const StringConvertException&);
		StringConvertException(const String& type, const String& reason);
		virtual ~StringConvertException();
	};
}