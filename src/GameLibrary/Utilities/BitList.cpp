
#include "BitList.h"

namespace GameLibrary
{
	BitList::BitList()
	{
		total = 0;
		bitTotal = 0;
	}

	BitList::BitList(const BitList&bitlist)
	{
		bytes = bitlist.bytes;
		total = bitlist.total;
		bitTotal = bitlist.bitTotal;
	}

	BitList::BitList(unsigned int size)
	{
		unsigned int byteTotal = size/8;
		bitTotal = size % 8;
		if(bitTotal != 0)
		{
			byteTotal++;
		}
		bytes.resize(byteTotal);
		total = size;
	}

	BitList::~BitList()
	{
		//
	}

	BitList& BitList::operator=(const BitList&bitlist)
	{
		bytes = bitlist.bytes;
		total = bitlist.total;
		bitTotal = bitlist.bitTotal;
		return *this;
	}

	bool BitList::get(unsigned int index) const
	{
		return BitList::get(index/8, index%8);
	}

	bool BitList::get(unsigned int byteIndex, unsigned int bitIndex) const
	{
		try
		{
			if(byteIndex==(bytes.size()-1) && bitIndex>=bitTotal)
			{
				throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
			}
			return bytes.get(byteIndex).get(bitIndex);
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
		}
	}

	void BitList::set(unsigned int index, bool value)
	{
		BitList::set(index/8, index%8, value);
	}

	void BitList::set(unsigned int byteIndex, unsigned int bitIndex, bool value)
	{
		try
		{
			if(byteIndex==(bytes.size()-1) && bitIndex>=bitTotal)
			{
				throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
			}
			bytes.get(byteIndex).set(bitIndex, value);
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
		}
	}

	byte* BitList::getData()
	{
		return (byte*)bytes.getData();
	}

	const byte* BitList::getData() const
	{
		return (byte*)bytes.getData();
	}

	void BitList::add(bool value)
	{
		total++;
		if(bitTotal==8 || bitTotal==0)
		{
			bitTotal = 1;
			bytes.add(Bitset());
			bytes.get(bytes.size()-1).set(0, value);
		}
		else
		{
			bitTotal++;
			bytes.get(bytes.size()-1).set(bitTotal-1, value);
		}
	}

	void BitList::add(unsigned int index, bool value)
	{
		BitList::add(index/8, index%8, value);
	}

	void BitList::add(unsigned int byteIndex, unsigned int bitIndex, bool value)
	{
		try
		{
			if(bitIndex >= 8)
			{
				throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
			}

			if(bitTotal == 8)
			{
				if(!(byteIndex < bytes.size() || (byteIndex == bytes.size() && bitIndex == 0)))
				{
					throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
				}

				bitTotal = 1;
				bytes.add(Bitset());
			}
			else
			{
				if(byteIndex == (bytes.size() - 1))
				{
					if(bitIndex > bitTotal)
					{
						throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
					}
				}
				else if(byteIndex > bytes.size())
				{
					throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
				}
				bitTotal++;
			}

			total++;
		
			unsigned int byteIndexCounter = bytes.size()-1;
			unsigned int bitIndexCounter = 7;
			if(byteIndexCounter>0 || bitIndexCounter>0)
			{
				for(unsigned int i=(bytes.size()-1); i>=0; i--)
				{
					bitIndexCounter = 7;
					Bitset& bitset = bytes.get(i);
					if(byteIndexCounter==byteIndex)
					{
						for(unsigned int j=8; j>=1; j--)
						{
							if(bitIndexCounter==bitIndex)
							{
								bitset.set(j-1, value);
								return;
							}

							if(j==1)
							{
								Bitset& nextBitset = bytes.get(i-1);
								bitset.set(0, nextBitset.get(7));
							}
							else
							{
								bitset.set(j-1, bitset.get(j-2));
								bitIndexCounter--;
							}
						}
					}
					else
					{
						for(unsigned int j=8; j>=1; j--)
						{
							if(j==1)
							{
								Bitset& nextBitset = bytes.get(i-1);
								bitset.set(0, nextBitset.get(7));
							}
							else
							{
								bitset.set(j-1, bitset.get(j-2));
								bitIndexCounter--;
							}
						}
					}
					byteIndexCounter--;
				}
			}
			else
			{
				bytes.get(0).set(0, value);
			}
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
		}
	}

	void BitList::remove(unsigned int index)
	{
		BitList::remove(index/8, index%8);
	}

	void BitList::remove(unsigned int byteIndex, unsigned int bitIndex)
	{
		try
		{
			unsigned int lastByteIndex = bytes.size()-1;
			if(byteIndex >= bytes.size())
			{
				throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
			}
			else if(byteIndex == lastByteIndex)
			{
				if(bitIndex >= bitTotal)
				{
					throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
				}
			}
			else
			{
				if(bitIndex >= 8)
				{
					throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
				}
			}

			total--;
			bitTotal--;

			for(unsigned int i=byteIndex; i<bytes.size(); i++)
			{
				Bitset& bitset = bytes.get(i);

				unsigned int j = 0;
				if(i==byteIndex)
				{
					j = bitIndex;
				}

				if(i==lastByteIndex)
				{
					for(j=bitIndex; j<8; j++)
					{
						if(j != 7)
						{
							bitset.set(j, bitset.get(j+1));
						}
					}
				}
				else
				{
					for(j=bitIndex; j<8; j++)
					{
						if(j == 7)
						{
							Bitset& nextBitset = bytes.get(i+1);
							bitset.set(j, nextBitset.get(0));
						}
						else
						{
							bitset.set(j, bitset.get(j+1));
						}
					}
				}
			}

			if(bitTotal == 0)
			{
				bytes.remove(bytes.size()-1);
				bitTotal=8;
			}
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
		}
	}

	void BitList::clear()
	{
		bytes.clear();
		total = 0;
		bitTotal = 0;
	}

	unsigned int BitList::size() const
	{
		return total;
	}

	unsigned int BitList::sizeBytes() const
	{
		return bytes.size();
	}

	/*void resize(unsigned int size)
	{
		
	}*/
}