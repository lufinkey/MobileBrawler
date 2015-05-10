
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate an error when pushing, presenting, popping, or dismissing a Screen*/
	class ScreenNavigationException : public Exception
	{
	public:
		/*! copy constructor*/
		ScreenNavigationException(const ScreenNavigationException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		explicit ScreenNavigationException(const String&message);
		/*! virtual destructor*/
		virtual ~ScreenNavigationException();
		/*! assignment operator*/
		ScreenNavigationException& operator=(const ScreenNavigationException&);
	};
}
