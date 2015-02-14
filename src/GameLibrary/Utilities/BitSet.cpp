
#include "BitSet.h"

namespace GameLibrary
{
	BitSet::BitSet()
	{
		b = 0;
	}

	BitSet::BitSet(const BitSet&bitset)
	{
		b = bitset.b;
	}
	
	BitSet::BitSet(byte b)
	{
		this->b = b;
	}
	
	BitSet::BitSet(char bits[8])
	{
		b = 0;
		for(int i=0; i<8; i++)
		{
			if(bits[i]=='1')
			{
				set(i, true);
			}
		}
	}

	BitSet::BitSet(bool bits[8])
	{
		b = 0;
		for(int i=0; i<8; i++)
		{
			if(bits[i])
			{
				set(i, true);
			}
		}
	}
	
	BitSet::~BitSet()
	{
		//
	}

	BitSet& BitSet::operator=(const BitSet&bitset)
	{
		b = bitset.b;
		return *this;
	}

	bool BitSet::operator==(const BitSet&bitset) const
	{
		if(b == bitset.b)
		{
			return true;
		}
		return false;
	}
	
	bool BitSet::get(size_t index) const
	{
		return ((b & (1 << index))!=0);
	}
	
	void BitSet::set(size_t index, bool toggle)
	{
		if(toggle)
		{
			b |= 1 << index;
		}
		else
		{
			b &= ~(1 << index);
		}
	}
	
	const byte& BitSet::getByte() const
	{
		return b;
	}
}
