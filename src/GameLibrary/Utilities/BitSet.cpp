
#include "Bitset.h"

namespace GameLibrary
{
	Bitset::Bitset()
	{
		b = 0;
	}

	Bitset::Bitset(const Bitset&bitset)
	{
		b = bitset.b;
	}
	
	Bitset::Bitset(byte b)
	{
		this->b = b;
	}
	
	Bitset::Bitset(char bits[8])
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

	Bitset::Bitset(bool bits[8])
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
	
	Bitset::~Bitset()
	{
		//
	}

	Bitset& Bitset::operator=(const Bitset&bitset)
	{
		b = bitset.b;
		return *this;
	}

	bool Bitset::operator==(const Bitset&bitset) const
	{
		if(b == bitset.b)
		{
			return true;
		}
		return false;
	}
	
	bool Bitset::get(unsigned int index) const
	{
		return ((b & (1 << index))!=0);
	}
	
	void Bitset::set(unsigned int index, bool toggle)
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
	
	const byte& Bitset::getByte() const
	{
		return b;
	}
}
