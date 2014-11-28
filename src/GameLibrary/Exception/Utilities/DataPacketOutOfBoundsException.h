
#include "../OutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	/* Thrown to indicate that an index to a DataPacket is out of range. */
	class DataPacketOutOfBoundsException : public OutOfBoundsException
	{
	public:
		unsigned int index;
		unsigned int size;
		
		DataPacketOutOfBoundsException(const DataPacketOutOfBoundsException&);
		DataPacketOutOfBoundsException(unsigned int index, unsigned int size);
		virtual ~DataPacketOutOfBoundsException();
	};
}
