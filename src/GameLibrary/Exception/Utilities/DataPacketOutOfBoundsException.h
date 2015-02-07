
#pragma once

#include "../OutOfBoundsException.h"

namespace GameLibrary
{
	/*! Thrown to indicate that an index to a DataPacket was out of bounds*/
	class DataPacketOutOfBoundsException : public OutOfBoundsException
	{
	public:
		/*! The out of bounds index*/
		unsigned int index;
		/*! The size of the DataPacket*/
		unsigned int size;
		
		/*! copy constructor*/
		DataPacketOutOfBoundsException(const DataPacketOutOfBoundsException&);
		/*! Constructs an exception with a DataPacket index and size.
			\param index the index in the DataPacket
			\param size the size of the DataPacket*/
		DataPacketOutOfBoundsException(unsigned int index, unsigned int size);
		/*! virtual destructor*/
		virtual ~DataPacketOutOfBoundsException();
		/*! assignment operator*/
		DataPacketOutOfBoundsException& operator=(const DataPacketOutOfBoundsException&);
	};
}
