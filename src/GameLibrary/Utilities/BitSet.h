
#include "../Types.h"
#include "../Exception/Utilities/BitSetOutOfBoundsException.h"

#pragma once

namespace GameLibrary
{
	class BitSet
	{
	private:
		byte b;
		
	public:
		enum Bitmask : byte
		{
			BITMASK_1 = 0x01,
			BITMASK_2 = 0x02,
			BITMASK_3 = 0x04,
			BITMASK_4 = 0x08,
			BITMASK_5 = 0x10,
			BITMASK_6 = 0x20,
			BITMASK_7 = 0x40,
			BITMASK_8 = 0x80
		};

		BitSet();
		BitSet(const BitSet&);
		BitSet(byte b);
		BitSet(char bits[8]);
		BitSet(bool bits[8]);
		~BitSet();

		BitSet& operator=(const BitSet&bitset);
		bool operator==(const BitSet&) const;
		
		bool get(unsigned int index) const;
		void set(unsigned int index, bool toggle);
		
		const byte& getByte() const;
	};
}
