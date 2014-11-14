
#include "../Types.h"

#pragma once

namespace GameEngine
{
	class Bitset
	{
	private:
		byte b;
		
	public:
		static const byte BITMASK_ONE   = 1;
		static const byte BITMASK_TWO   = 2;
		static const byte BITMASK_THREE = 4;
		static const byte BITMASK_FOUR  = 8;
		static const byte BITMASK_FIVE  = 16;
		static const byte BITMASK_SIX   = 32;
		static const byte BITMASK_SEVEN = 64;
		static const byte BITMASK_EIGHT = 128;
		
		Bitset();
		Bitset(byte b);
		Bitset(bool bits[8]);
		~Bitset();
		
		bool get(unsigned int index);
		void set(unsigned int index, bool toggle);
		
		byte&getByte();
		
		Bitset& operator=(const Bitset&bitset);
	};
}