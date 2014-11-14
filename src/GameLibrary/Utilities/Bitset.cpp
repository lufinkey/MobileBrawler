
#include "Bitset.h"

namespace GameLibrary
{
	Bitset::Bitset()
	{
		b = 0;
	}
	
	Bitset::Bitset(byte b)
	{
		this->b = b;
	}
	
	Bitset::Bitset(bool bits[8])
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
	
	Bitset::~Bitset()
	{
		//
	}
	
	bool Bitset::get(unsigned int index) const
	{
		return ((b & (1 << index))!=0);
	}
	
	void Bitset::set(unsigned int index, bool toggle)
	{
		if(toggle)
		{
			b |= (1 << index);
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
	
	Bitset& Bitset::operator=(const Bitset&bitset)
	{
		b = bitset.b;
		return *this;
	}
}