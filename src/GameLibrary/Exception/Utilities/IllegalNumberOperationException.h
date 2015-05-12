
#pragma once

#include "../Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an illegal operator was used on a Number object.
		\see GameLibrary::Number*/
	class IllegalNumberOperationException : public Exception
	{
	public:
		String operatorType;
		String numberType;
		String side;
		
		/*! copy constructor*/
		IllegalNumberOperationException(const IllegalNumberOperationException&);
		/*! Constructs an exception with an operator, a number type, and the equation side.
			\param operatorType the type of operator used on the Number object (+, -, +=, etc.)
			\param numberType the type of number primitive used (int, bool, float, double, etc.)
			\param side the side of the equation the number with the error was on (left or right)*/
		IllegalNumberOperationException(const String&operatorType, const String&numberType, const String&side);
		/*! virtual destructor*/
		virtual ~IllegalNumberOperationException();
		/*! assignment operator*/
		IllegalNumberOperationException& operator=(const IllegalNumberOperationException&);
		
		/*! \copydoc GameLibrary::Exception::getClassName()const*/
		virtual String getClassName() const override;
	};
}
