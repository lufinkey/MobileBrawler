
#include "BitSet.h"
#include "ArrayList.h"
#include "../Exception/Utilities/BitListOutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class BitList
	{
	private:
		ArrayList<BitSet> bytes;
		unsigned int total;
		unsigned int bitTotal;

	public:
		BitList();
		BitList(const BitList&);

		//TODO implement if std::initializer_list is available
		//BitList(const std::initializer_list<T>&);

		BitList(unsigned int size);
		~BitList();

		BitList& operator=(const BitList&);

		bool get(unsigned int index) const;
		bool get(unsigned int byteIndex, unsigned int bitIndex) const;
		void set(unsigned int index, bool value);
		void set(unsigned int byteIndex, unsigned int bitIndex, bool value);

		byte* getData();
		const byte* getData() const;

		void add(bool value);
		void add(unsigned int index, bool value);
		void add(unsigned int byteIndex, unsigned int bitIndex, bool value);

		void remove(unsigned int index);
		void remove(unsigned int byteIndex, unsigned int bitIndex);

		void clear();
		unsigned int size() const;
		unsigned int sizeBytes() const;
		//void resize(unsigned int size);
	};
}