
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	class ScreenNavigationException : public Exception
	{
	public:
		ScreenNavigationException(const ScreenNavigationException&);
		ScreenNavigationException(const String&message);
		virtual ~ScreenNavigationException();
	};
}
