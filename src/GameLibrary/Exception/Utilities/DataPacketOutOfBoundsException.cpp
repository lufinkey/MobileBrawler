
#include "DataPacketOutOfBoundsException.h"

namespace GameLibrary
{
	DataPacketOutOfBoundsException::DataPacketOutOfBoundsException(const DataPacketOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		size = exception.size;
	}
	
	DataPacketOutOfBoundsException::DataPacketOutOfBoundsException(size_t i, size_t s) : OutOfBoundsException((String)"index " + i + " is out of bounds in DataPacket with a size of " + s)
	{
		index = i;
		size = s;
	}
	
	DataPacketOutOfBoundsException::~DataPacketOutOfBoundsException()
	{
		//
	}
	
	DataPacketOutOfBoundsException& DataPacketOutOfBoundsException::operator=(const DataPacketOutOfBoundsException&exception)
	{
		OutOfBoundsException::operator=(exception);
		index = exception.index;
		size = exception.size;
		return *this;
	}
	
	GAMELIB_MEMBERFUNC_GETCLASSNAME(DataPacketOutOfBoundsException)
}
