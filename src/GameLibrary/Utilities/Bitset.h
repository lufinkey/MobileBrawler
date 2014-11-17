
#include "../Types.h"

#pragma once

namespace GameLibrary
{
	class Bitset
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

		Bitset();
		Bitset(const Bitset&);
		Bitset(byte b);
		Bitset(char bits[8]);
		Bitset(bool bits[8]);
		~Bitset();

		Bitset& operator=(const Bitset&bitset);
		bool operator==(const Bitset&) const;
		
		bool get(unsigned int index) const;
		void set(unsigned int index, bool toggle);
		
		const byte& getByte() const;
	};
}