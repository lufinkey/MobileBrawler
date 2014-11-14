
#include "../Types.h"

#pragma once

namespace GameLibrary
{
#define BITMASK_1 1
#define BITMASK_2 2
#define BITMASK_3 4
#define BITMASK_4 8
#define BITMASK_5 16
#define BITMASK_6 32
#define BITMASK_7 64
#define BITMASK_8 128

	class Bitset
	{
	private:
		byte b;
		
	public:
		Bitset();
		Bitset(byte b);
		Bitset(bool bits[8]);
		~Bitset();
		
		bool get(unsigned int index) const;
		void set(unsigned int index, bool toggle);
		
		const byte& getByte() const;
		
		Bitset& operator=(const Bitset&bitset);
	};
}