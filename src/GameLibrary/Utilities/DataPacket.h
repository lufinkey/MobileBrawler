
#include "../Types.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Exception/Utilities/DataPacketOutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class DataPacket
	{
	private:
		byte*data;
		unsigned int total;

	public:
		static int toInt(const void*data);
		static bool toBool(const void*data);
		static long toLong(const void*data);
		static float toFloat(const void*data);
		static double toDouble(const void*data);

		DataPacket();
		DataPacket(const DataPacket&);
		DataPacket(unsigned int size);
		DataPacket(const void*data, unsigned int size);
		~DataPacket();

		void*getData();
		const void*getData() const;
		void setData(const void*data, unsigned int size);
		unsigned int size() const;

		void resize(unsigned int size);
		void clear();

		void add(const void*data, unsigned int size);
		void add(unsigned int byteIndex, const void*data, unsigned int size);
		void remove(unsigned int byteIndex, unsigned int size);
		void set(unsigned int byteIndex, const void*data, unsigned int size);
		void*get(unsigned int byteIndex);
		const void*get(unsigned int byteIndex) const;

		void add(const DataPacket&data);
		void add(unsigned int byteIndex, const DataPacket&data);
		void set(unsigned int byteIndex, const DataPacket&data);

		void add(byte dataByte);
		void add(unsigned int byteIndex, byte dataByte);
		void remove(unsigned int byteIndex);
		void set(unsigned int byteIndex, byte dataByte);
		byte getByte(unsigned int byteIndex) const;
	};
}
