
#pragma once

#include "../Types.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Exception/Utilities/DataPacketOutOfBoundsException.h"

namespace GameLibrary
{
	class DataPacket
	{
	private:
		byte*data;
		size_t total;

	public:
		static int toInt(const void*data);
		static bool toBool(const void*data);
		static long toLong(const void*data);
		static float toFloat(const void*data);
		static double toDouble(const void*data);

		DataPacket();
		DataPacket(const DataPacket&);
		DataPacket(const String&);
		DataPacket(size_t size);
		DataPacket(const void*data, size_t size);
		~DataPacket();

		DataPacket& operator=(const DataPacket&);

		bool loadFromFile(const String&path, String*error=nullptr);
		bool saveToFile(const String&path, String*error=nullptr) const;

		void*getData();
		const void*getData() const;
		void setData(const void*data, size_t size);
		void setData(const DataPacket&data);
		size_t size() const;

		void resize(size_t size);
		void clear();

		void add(const void*data, size_t size);
		void add(size_t byteIndex, const void*data, size_t size);
		void remove(size_t byteIndex, size_t size);
		void set(size_t byteIndex, const void*data, size_t size);
		void*get(size_t byteIndex);
		const void*get(size_t byteIndex) const;

		void add(const DataPacket&data);
		void add(size_t byteIndex, const DataPacket&data);
		void set(size_t byteIndex, const DataPacket&data);

		void add(byte dataByte);
		void add(size_t byteIndex, byte dataByte);
		void remove(size_t byteIndex);
		void set(size_t byteIndex, byte dataByte);
		byte getByte(size_t byteIndex) const;
	};
}
