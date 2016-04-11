
#include "BitListOutOfBoundsException.h"

namespace GameLibrary
{
	BitListOutOfBoundsException::BitListOutOfBoundsException(const BitListOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		byteIndex = exception.byteIndex;
		bitIndex = exception.bitIndex;
		size = exception.size;
	}
	
	BitListOutOfBoundsException::BitListOutOfBoundsException(size_t i, size_t s) : OutOfBoundsException((String)"index " + i + " is out of bounds in BitList with a size of " + s + ". (byteIndex=" + (i/8) + ", bitIndex=" + (i%8) + ")")
	{
		index = i;
		byteIndex = i/8;
		bitIndex = i%8;
		size = s;
	}

	BitListOutOfBoundsException::BitListOutOfBoundsException(size_t byteIndx, size_t bitIndx, size_t s) : OutOfBoundsException((String)"index " + ((byteIndx*8)+bitIndx) + " is out of bounds in BitList with a size of " + s + ". (byteIndex=" + byteIndx + ", bitIndex=" + bitIndx + ")")
	{
		index = (byteIndx*8) + bitIndx;
		byteIndex = byteIndx;
		bitIndex = bitIndx;
		size = s;
	}
	
	BitListOutOfBoundsException::~BitListOutOfBoundsException()
	{
		//
	}
	
	BitListOutOfBoundsException& BitListOutOfBoundsException::operator=(const BitListOutOfBoundsException&exception)
	{
		OutOfBoundsException::operator=(exception);
		index = exception.index;
		byteIndex = exception.byteIndex;
		bitIndex = exception.bitIndex;
		size = exception.size;
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(BitListOutOfBoundsException)
}
