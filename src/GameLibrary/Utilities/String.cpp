
#include "String.h"
#ifdef _STRING_STANDALONE
	#include <stdexcept>
#else
	#include "../Exception/NumberFormatException.h"
	#include "../Exception/Utilities/StringOutOfBoundsException.h"
#endif

#ifndef _STRING_STANDALONE
namespace GameLibrary
{
#endif
	
	void BasicStringUtils::throw_out_of_bounds(size_t index, size_t size)
	{
		#ifndef _STRING_STANDALONE
			throw StringOutOfBoundsException(index, size);
		#else
			throw std::out_of_range("index " + std::to_string(index) + " is out of bounds in string with a length of " + std::to_string(size));
		#endif
	}
	
	void BasicStringUtils::throw_number_format_error(const std::string& typeName, const std::string& reason)
	{
		#ifndef _STRING_STANDALONE
			throw NumberFormatException(typeName, reason);
		#else
			throw std::logic_error(reason);
		#endif
	}

#ifndef _STRING_STANDALONE
}
#endif
