
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
			BITMASK_1 = 0x00000001,
			BITMASK_2 = 0x00000002,
			BITMASK_3 = 0x00000004,
			BITMASK_4 = 0x00000008,
			BITMASK_5 = 0x00000010,
			BITMASK_6 = 0x00000020,
			BITMASK_7 = 0x00000040,
			BITMASK_8 = 0x00000080
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
