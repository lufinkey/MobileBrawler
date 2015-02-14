
#pragma once

#include "BitSet.h"
#include "ArrayList.h"
#include "../Exception/Utilities/BitListOutOfBoundsException.h"

namespace GameLibrary
{
	class BitList
	{
	private:
		ArrayList<BitSet> bytes;
		size_t total;
		size_t bitTotal;

	public:
		class BitAlias
		{
			friend class BitList;
		private:
			BitSet* bitset;
			byte bitIndex;

			BitAlias(BitSet*bitset, size_t bitIndex);

		public:
			BitAlias(const BitAlias&);

			BitAlias& operator=(bool);
			operator bool() const;
		};

		BitList();
		BitList(const BitList&);
		BitList(const std::vector<bool>&);

		//TODO implement if std::initializer_list is available
		//BitList(const std::initializer_list<T>&);
		
		BitList(size_t size);
		~BitList();

		BitList& operator=(const BitList&);
		BitAlias operator[](size_t index);
		const BitAlias operator[](size_t index) const;

		bool get(size_t index) const;
		bool get(size_t byteIndex, size_t bitIndex) const;
		void set(size_t index, bool value);
		void set(size_t byteIndex, size_t bitIndex, bool value);

		byte* getData();
		const byte* getData() const;

		void add(bool value);
		void add(size_t index, bool value);
		void add(size_t byteIndex, size_t bitIndex, bool value);

		void remove(size_t index);
		void remove(size_t byteIndex, size_t bitIndex);

		void clear();
		size_t size() const;
		size_t sizeBytes() const;
		void resize(size_t size);
	};
}