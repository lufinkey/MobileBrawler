
#include "BitList.h"

namespace GameLibrary
{
	BitList::BitAlias::BitAlias(const BitAlias&bitalias)
	{
		bitset = bitalias.bitset;
		bitIndex = bitalias.bitIndex;
	}

	BitList::BitAlias::BitAlias(BitSet*bs, size_t bi)
	{
		bitset = bs;
		bitIndex = (byte)bi;
	}

	BitList::BitAlias& BitList::BitAlias::operator=(bool value)
	{
		bitset->set((size_t)bitIndex, value);
		return *this;
	}

	BitList::BitAlias::operator bool() const
	{
		return bitset->get((size_t)bitIndex);
	}

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
	
	BitList::BitList(const std::vector<bool>&boolvect)
	{
		bitTotal = 0;
		total = 0;
		for(size_t i = 0; i < boolvect.size(); i++)
		{
			total++;
			if(bitTotal==8 || bitTotal==0)
			{
				bitTotal = 1;
				bytes.add(BitSet());
				bytes.get(bytes.size()-1).set(0, boolvect.at(i));
			}
			else
			{
				bitTotal++;
				bytes.get(bytes.size()-1).set(bitTotal-1, boolvect.at(i));
			}
		}
	}

	BitList::BitList(size_t size)
	{
		size_t byteTotal = size/8;
		bitTotal = size % 8;
		if(bitTotal == 0)
		{
			if(byteTotal > 0)
			{
				bitTotal = 8;
			}
		}
		else
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

	BitList::BitAlias BitList::operator[](size_t index)
	{
		return BitAlias(&bytes.get(index/8), index%8);
	}

	const BitList::BitAlias BitList::operator[](size_t index) const
	{
		return BitAlias((BitSet*)(&bytes.get(index/8)), index%8);
	}

	bool BitList::get(size_t index) const
	{
		return BitList::get(index/8, index%8);
	}

	bool BitList::get(size_t byteIndex, size_t bitIndex) const
	{
		if(bitIndex > 7)
		{
			throw BitSetOutOfBoundsException(bitIndex);
		}
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

	void BitList::set(size_t index, bool value)
	{
		BitList::set(index/8, index%8, value);
	}

	void BitList::set(size_t byteIndex, size_t bitIndex, bool value)
	{
		if(bitIndex > 7)
		{
			throw BitSetOutOfBoundsException(bitIndex);
		}
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
			bytes.add(BitSet());
			bytes.get(bytes.size()-1).set(0, value);
		}
		else
		{
			bitTotal++;
			bytes.get(bytes.size()-1).set(bitTotal-1, value);
		}
	}

	void BitList::add(size_t index, bool value)
	{
		BitList::add(index/8, index%8, value);
	}

	void BitList::add(size_t byteIndex, size_t bitIndex, bool value)
	{
		if(bitIndex > 7)
		{
			throw BitSetOutOfBoundsException(bitIndex);
		}
		try
		{
			if(bitTotal == 8)
			{
				if(!(byteIndex < bytes.size() || (byteIndex == bytes.size() && bitIndex == 0)))
				{
					throw BitListOutOfBoundsException(byteIndex, bitIndex, total);
				}

				bitTotal = 1;
				bytes.add(BitSet());
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
		
			size_t byteIndexCounter = bytes.size()-1;
			size_t bitIndexCounter = 7;
			if(byteIndexCounter>0 || bitIndexCounter>0)
			{
				for(size_t i=(bytes.size()-1); i!=UINT_MAX; i--)
				{
					bitIndexCounter = 7;
					BitSet& bitset = bytes.get(i);
					if(byteIndexCounter==byteIndex)
					{
						for(size_t j=8; j>=1; j--)
						{
							if(bitIndexCounter==bitIndex)
							{
								bitset.set(j-1, value);
								return;
							}

							if(j==1)
							{
								BitSet& nextBitSet = bytes.get(i-1);
								bitset.set(0, nextBitSet.get(7));
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
						for(size_t j=8; j>=1; j--)
						{
							if(j==1)
							{
								BitSet& nextBitSet = bytes.get(i-1);
								bitset.set(0, nextBitSet.get(7));
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

	void BitList::remove(size_t index)
	{
		BitList::remove(index/8, index%8);
	}

	void BitList::remove(size_t byteIndex, size_t bitIndex)
	{
		if(bitIndex > 7)
		{
			throw BitSetOutOfBoundsException(bitIndex);
		}
		try
		{
			size_t lastByteIndex = bytes.size()-1;
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

			total--;
			bitTotal--;

			for(size_t i=byteIndex; i<bytes.size(); i++)
			{
				BitSet& bitset = bytes.get(i);

				size_t startBitIndex = 0;
				if(i==byteIndex)
				{
					startBitIndex = bitIndex;
				}

				if(i==lastByteIndex)
				{
					for(size_t j=startBitIndex; j<8; j++)
					{
						if(j != 7)
						{
							bitset.set(j, bitset.get(j+1));
						}
					}
				}
				else
				{
					for(size_t j=startBitIndex; j<8; j++)
					{
						if(j == 7)
						{
							BitSet& nextBitSet = bytes.get(i+1);
							bitset.set(j, nextBitSet.get(0));
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

	size_t BitList::size() const
	{
		return total;
	}

	size_t BitList::sizeBytes() const
	{
		return bytes.size();
	}

	void BitList::resize(size_t size)
	{
		size_t oldByteTotal = bytes.size();
		size_t oldBitTotal = bitTotal;

		size_t byteTotal = size/8;
		bitTotal = size % 8;
		if(bitTotal == 0)
		{
			if(byteTotal > 0)
			{
				bitTotal = 7;
			}
		}
		else
		{
			byteTotal++;
		}
		bytes.resize(byteTotal);
		total = size;

		if(oldByteTotal!=0)
		{
			if((byteTotal==oldByteTotal && bitTotal>oldBitTotal) || byteTotal>oldByteTotal)
			{
				size_t byteStartIndex = oldByteTotal-1;
				size_t bitStartIndex = oldBitTotal;
				if(bitStartIndex == 8)
				{
					bitStartIndex = 0;
					byteStartIndex++;
				}
				for(size_t i=byteStartIndex; i<byteTotal; i++)
				{
					BitSet& bitset = bytes.get(i);
					size_t startIndex = 0;
					if(i==byteStartIndex)
					{
						startIndex = bitStartIndex;
					}
					for(size_t j=startIndex; j<8; j++)
					{
						bitset.set(j, false);
					}
				}
			}
		}
	}
}