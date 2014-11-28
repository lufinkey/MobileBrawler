
#include "DataPacketOutOfBoundsException.h"

namespace GameLibrary
{
	DataPacketOutOfBoundsException::DataPacketOutOfBoundsException(const DataPacketOutOfBoundsException&exception) : OutOfBoundsException(exception)
	{
		index = exception.index;
		size = exception.size;
	}
	
	DataPacketOutOfBoundsException::DataPacketOutOfBoundsException(unsigned int i, unsigned int s) : OutOfBoundsException((String)"index " + i + " is out of bounds in DataPacket with a size of " + s)
	{
		index = i;
		size = s;
	}
	
	DataPacketOutOfBoundsException::~DataPacketOutOfBoundsException()
	{
		//
	}
}
