
#define _CRT_SECURE_NO_WARNINGS

#include "DataPacket.h"
#include <cstdio>
#include <cstdlib>

namespace GameLibrary
{
	int DataPacket::toInt(const void*data)
	{
		const int*r = (const int*)data;
		return *r;
	}

	bool DataPacket::toBool(const void*data)
	{
		const bool*r = (const bool*)data;
		return *r;
	}
	
	long DataPacket::toLong(const void*data)
	{
		const long*r = (const long*)data;
		return *r;
	}
	
	float DataPacket::toFloat(const void*data)
	{
		const float*r = (const float*)data;
		return *r;
	}
	
	double DataPacket::toDouble(const void*data)
	{
		const double*r = (const double*)data;
		return *r;
	}

	DataPacket::DataPacket()
	{
		data = nullptr;
		total = 0;
	}

	DataPacket::DataPacket(const DataPacket&dataPacket)
	{
		if(dataPacket.data == nullptr)
		{
			data = nullptr;
			total = 0;
		}
		else
		{
			data = (byte*)std::malloc(dataPacket.total);
			for(unsigned int i=0; i<dataPacket.total; i++)
			{
				data[i] = dataPacket.data[i];
			}
			total = dataPacket.total;
		}
	}
	
	DataPacket::DataPacket(const String&str)
	{
		if(str.length()==0)
		{
			data = nullptr;
			total = 0;
		}
		{
			data = (byte*)std::malloc(str.length());
			const byte* cpyBytes = (const byte*)((const char*)str);
			for(unsigned int i = 0; i < str.length(); i++)
			{
				data[i] = cpyBytes[i];
			}
			total = str.length();
		}
	}
	
	DataPacket::DataPacket(unsigned int size)
	{
		data = (byte*)std::malloc(size);
		for(unsigned int i=0; i<size; i++)
		{
			data[i] = 0;
		}
		total = size;
	}
	
	DataPacket::DataPacket(const void*data1, unsigned int size)
	{
		if(size>0)
		{
			if(data1 == nullptr)
			{
				throw IllegalArgumentException("data argument in DataPacket(const void*data,unsigned int size) cannot be nullptr if size>0");
			}

			data = (byte*)std::malloc(size);
			const byte*copyBytes = (const byte*)data1;
			for(unsigned int i=0; i<size; i++)
			{
				data[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			data = nullptr;
			total = 0;
		}
	}
	
	DataPacket::~DataPacket()
	{
		if(data!=nullptr)
		{
			std::free(data);
			data = nullptr;
			total = 0;
		}
	}

	DataPacket& DataPacket::operator=(const DataPacket&dataPacket)
	{
		setData(dataPacket);
		return *this;
	}

	bool DataPacket::loadFromFile(const String&path, String*error)
	{
		FILE*file = std::fopen(path, "r");
		if (file == nullptr)
		{
			//TODO add switch for errno
			if(error!=nullptr)
			{
				*error = "Unable to load data from file";
			}
			return false;
		}
		
		std::fseek(file, 0, SEEK_END);
		long fileSize = (long)std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
		
		if(data == nullptr)
		{
			data = (byte*)std::malloc(fileSize);
		}
		else
		{
			data = (byte*)std::realloc(data,fileSize);
		}
		
		std::fread((void*)data, 1, fileSize, file);
		
		std::fclose(file);

		total = (unsigned int)fileSize;

		return true;
	}
	
	bool DataPacket::saveToFile(const String&path, String*error) const
	{
		FILE*file = std::fopen(path, "w");
		if(file==NULL)
		{
			if(error != nullptr)
			{
				//TODO add checking of errno
				*error = "Unable to write data to file";
			}
			return false;
		}
		
		size_t written = std::fwrite(data, 1, total, file);
		if(written != total)
		{
			if(error != nullptr)
			{
				//TODO add checking of errno
				*error = (String)"Unable to write all bytes to file stream";
			}
			return false;
		}
		
		if(std::fclose(file) == EOF)
		{
			if(error!=nullptr)
			{
				//TODO add checking of errno
				*error = "Error closing the file";
			}
			return false;
		}
		return true;
	}
	
	void*DataPacket::getData()
	{
		return (void*)data;
	}

	const void*DataPacket::getData() const
	{
		return (const void*)data;
	}

	void DataPacket::setData(const void*data1, unsigned int size)
	{
		if(size > 0)
		{
			if(data1==nullptr)
			{
				throw IllegalArgumentException("data argument in DataPacket::setData(const void*data,unsigned int size) cannot be nullptr if size>0");
			}

			if(data==nullptr)
			{
				data = (byte*)std::malloc(size);
			}
			else
			{
				data = (byte*)std::realloc(data, size);
			}

			const byte*copyBytes = (const byte*)data1;
			for(unsigned int i=0; i<size; i++)
			{
				data[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			if(data != nullptr)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
		}
	}

	void DataPacket::setData(const DataPacket&dataPacket)
	{
		if(dataPacket.total > 0)
		{
			if(data==nullptr)
			{
				data = (byte*)std::malloc(dataPacket.total);
			}
			else
			{
				data = (byte*)std::realloc(data, dataPacket.total);
			}

			for(unsigned int i=0; i<dataPacket.total; i++)
			{
				data[i] = dataPacket.data[i];
			}
			total = dataPacket.total;
		}
		else
		{
			if(data != nullptr)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
		}
	}
	
	unsigned int DataPacket::size() const
	{
		return total;
	}
	
	void DataPacket::resize(unsigned int size)
	{
		if(size > 0)
		{
			if(data==nullptr)
			{
				data = (byte*)std::malloc(size);
				for(unsigned int i=0; i<size; i++)
				{
					data[i] = 0;
				}
				total = size;
			}
			else
			{
				data = (byte*)std::realloc(data, size);
				if(size>total)
				{
					for(unsigned int i=total; i<size; i++)
					{
						data[i] = 0;
					}
				}
				total = size;
			}
		}
		else
		{
			if(data!=nullptr)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
		}
	}
	
	void DataPacket::clear()
	{
		if(data!=nullptr)
		{
			std::free(data);
			data = nullptr;
			total = 0;
		}
	}
	
	void DataPacket::add(const void*data1, unsigned int size)
	{
		if(size>0)
		{
			if(data1 == nullptr)
			{
				throw IllegalArgumentException("data argument in DataPacket::add(const void*data,unsigned int size) cannot be nullptr if size>0");
			}

			if(data == nullptr)
			{
				data = (byte*)std::malloc(size);
				const byte*copyBytes = (const byte*)data1;
				for(unsigned int i=0; i<size; i++)
				{
					data[i] = copyBytes[i];
				}
				total = size;
			}
			else
			{
				unsigned int newTotal = total + size;
				data = (byte*)std::realloc(data, newTotal);
				const byte*copyBytes = (const byte*)data1;
				unsigned int counter = 0;
				for(unsigned int i=total; i<newTotal; i++)
				{
					data[i] = copyBytes[counter];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(unsigned int byteIndex, const void*data1, unsigned int size)
	{
		if(byteIndex > total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(size>0)
		{
			if(data1 == nullptr)
			{
				throw IllegalArgumentException("data argument in DataPacket::add(unsigned int byteIndex,const void*data,unsigned int size) cannot be nullptr if size>0");
			}

			if(data == nullptr)
			{
				data = (byte*)std::malloc(size);
				const byte*copyBytes = (const byte*)data1;
				for(unsigned int i=0; i<size; i++)
				{
					data[i] = copyBytes[i];
				}
				total = size;
			}
			else
			{
				unsigned int newTotal = total+size;
				data = (byte*)std::realloc(data, newTotal);
				const byte*copyBytes = (const byte*)data1;
				unsigned int counter = (total-1);
				unsigned int endIndex = byteIndex + size;
				for(unsigned int i=(newTotal-1); i>endIndex; i--)
				{
					data[i] = data[counter];
					counter--;
				}
				counter = byteIndex;
				for(unsigned int i=0; i<size; i++)
				{
					data[counter] = copyBytes[i];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(const DataPacket&dataPacket)
	{
		if(dataPacket.total>0)
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(dataPacket.total);
				for(unsigned int i=0; i<dataPacket.total; i++)
				{
					data[i] = dataPacket.data[i];
				}
				total = dataPacket.total;
			}
			else
			{
				unsigned int newTotal = total + dataPacket.total;
				data = (byte*)std::realloc(data, newTotal);
				unsigned int counter = 0;
				for(unsigned int i=total; i<newTotal; i++)
				{
					data[i] = dataPacket.data[counter];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(unsigned int byteIndex, const DataPacket&dataPacket)
	{
		if(byteIndex > total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(dataPacket.total>0)
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(dataPacket.total);
				for(unsigned int i=0; i<dataPacket.total; i++)
				{
					data[i] = dataPacket.data[i];
				}
				total = dataPacket.total;
			}
			else
			{
				unsigned int newTotal = total+dataPacket.total;
				data = (byte*)std::realloc(data, newTotal);
				unsigned int counter = (total-1);
				unsigned int endIndex = byteIndex + dataPacket.total;
				for(unsigned int i=(newTotal-1); i>endIndex; i--)
				{
					data[i] = data[counter];
					counter--;
				}
				counter = byteIndex;
				for(unsigned int i=0; i<dataPacket.total; i++)
				{
					data[counter] = dataPacket.data[i];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(byte dataByte)
	{
		if(data == nullptr)
		{
			data = (byte*)std::malloc(1);
			data[0] = dataByte;
			total=1;
		}
		else
		{
			data = (byte*)std::realloc(data, total+1);
			data[total] = dataByte;
			total++;
		}
	}
	
	void DataPacket::add(unsigned int byteIndex, byte dataByte)
	{
		if(byteIndex > total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(1);
				data[0] = dataByte;
				total = 1;
			}
			else
			{
				unsigned int newTotal = total+1;
				data = (byte*)std::realloc(data, newTotal);
				for(unsigned int i=(newTotal-1); i>byteIndex; i--)
				{
					data[i] = data[i-1];
				}
				data[byteIndex] = dataByte;
				total = newTotal;
			}
		}
	}
	
	void DataPacket::remove(unsigned int byteIndex, unsigned int size)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(size>0)
		{
			unsigned int endOfRemove = byteIndex+size;
			unsigned int counter = byteIndex;
			for(unsigned int i=endOfRemove; i<total; i++)
			{
				data[counter] = data[i];
				counter++;
			}
			unsigned int newTotal = total - size;
			if(newTotal == 0)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
			else
			{
				data = (byte*)std::realloc(data, newTotal);
				total = newTotal;
			}
		}
	}
	
	void DataPacket::remove(unsigned int byteIndex)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			unsigned int endOfRemove = byteIndex+1;
			unsigned int counter = byteIndex;
			for(unsigned int i=endOfRemove; i<total; i++)
			{
				data[counter] = data[i];
				counter++;
			}
			unsigned int newTotal = total - 1;
			data = (byte*)std::realloc(data, newTotal);
			total = newTotal;
		}
	}
	
	void DataPacket::set(unsigned int byteIndex, const void*data1, unsigned int size)
	{
		unsigned int endIndex = byteIndex + size;
		if(endIndex>total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(size>0)
		{
			if(data1 == nullptr)
			{
				throw IllegalArgumentException("data argument in DataPacket::set(unsigned int byteIndex,const void*data,unsigned int size) cannot be nullptr if size>0");
			}

			const byte*copyBytes = (const byte*)data1;
			unsigned int counter = byteIndex;
			for(unsigned int i=0; i<size; i++)
			{
				data[counter] = copyBytes[i];
			}
		}
	}
	
	void DataPacket::set(unsigned int byteIndex, const DataPacket&dataPacket)
	{
		unsigned int endIndex = byteIndex + dataPacket.total;
		if(endIndex>total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(dataPacket.total>0)
		{
			unsigned int counter = byteIndex;
			for(unsigned int i=0; i<dataPacket.total; i++)
			{
				data[counter] = dataPacket.data[i];
			}
		}
	}
	
	void DataPacket::set(unsigned int byteIndex, byte dataByte)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			data[byteIndex] = dataByte;
		}
	}
	
	void*DataPacket::get(unsigned int byteIndex)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			return (void*)(data + byteIndex);
		}
	}

	const void*DataPacket::get(unsigned int byteIndex) const
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			return (const void*)(data + byteIndex);
		}
	}
	
	byte DataPacket::getByte(unsigned int byteIndex) const
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			return data[byteIndex];
		}
	}
}