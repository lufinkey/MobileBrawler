
#pragma once

#include "../Utilities/String.h"
#include <exception>

namespace GameLibrary
{
	/*! An exception class to throw when a generic error arises*/
	class Exception : std::exception
	{
	public:
		/*! An explanation of the error*/
		String message;
		
		/*! default constructor*/
		Exception();
		/*! copy constructor*/
		Exception(const Exception&);
		/*! Constructs an exception with an error message.
			\param message an explanation of the error*/
		explicit Exception(const String&message);
		/*! virtual destructor*/
		virtual ~Exception();
		/*! assignment operator*/
		Exception& operator=(const Exception&);
		
		/*! Gets an explanation of the error.
			\returns a const char pointer containing an error message*/
		virtual const char* what() const _NOEXCEPT;
	};
}