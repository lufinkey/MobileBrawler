
#include "../Exception.h"

#pragma once

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
