
#pragma once

#include <climits>
#include <cstdlib>
#include <exception>
#include <new>
#include <stdexcept>

#define _STRING_USES_GAMELIBRARY

#ifdef _STRING_USES_GAMELIBRARY
namespace GameLibrary
{
#endif
	
#define STRING_NOTFOUND SIZE_MAX
	
	template<typename C>
	class BasicString
	{
	private:
		C*characters;
		size_t size;
		
	public:
		static size_t strlen(const C*str)
		{
			size_t size = 0;
			while(str[size] != 0)
			{
				size++;
			}
			return size;
		}
		
		static int compare_value(const C&c1, const C&c2)
		{
			if(c1 < c2)
			{
				return -1;
			}
			else if(c1 > c2)
			{
				return 1;
			}
			return 0;
		}
		
		BasicString()
		{
			size = 0;
			characters = (C*)std::calloc(1,sizeof(C));
			if(characters==nullptr)
			{
				throw std::bad_alloc();
			}
			characters[0] = 0;
		}
		
		BasicString(const BasicString<C>&str)
		{
			size = str.size;
			characters = (C*)std::calloc(size+1,sizeof(C));
			if(characters==nullptr)
			{
				throw std::bad_alloc();
			}
			for(size_t i=0; i<size; i++)
			{
				characters[i] = str.characters[i];
			}
			characters[total] = 0;
		}
		
		BasicString(const C*str, size_t length)
		{
			size = length;
			characters = (C*)std::calloc(size+1,sizeof(C));
			if(characters==nullptr)
			{
				throw std::bad_alloc();
			}
			for(size_t i=0; i<size; i++)
			{
				characters[i] = str[i];
			}
			characters[size] = 0;
		}
		
		BasicString(const C*str) : BasicString(str, strlen(str))
		{
			//
		}
		
		~BasicString()
		{
			if(characters!=nullptr)
			{
				std::free(characters);
			}
		}
		
		operator C*()
		{
			return characters;
		}
		
		operator const C*() const
		{
			return characters;
		}
		
		void append(const BasicString<C>&str)
		{
			size_t size_new = size + str.size;
			C*characters_new = (C*)std::realloc(characters, (size_new+1)*sizeof(C));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size_t counter = 0;
			for(size_t i=size; i<size_new; i++)
			{
				characters[i] = str.characters[counter];
				counter++;
			}
			size = size_new;
			characters[size] = 0;
		}
		
		void append(const C*str, size_t length)
		{
			size_t size_new = size + length;
			C*characters_new = (C*)std::realloc(characters, (size_new+1)*sizeof(C));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			size_t counter = 0;
			for(size_t i=size; i<size_new; i++)
			{
				characters[i] = str[counter];
				counter++;
			}
			size = size_new;
			characters[size] = 0;
		}
		
		BasicString<C>& operator+=(const BasicString<C>&str)
		{
			append(str);
			return *this;
		}
		
		BasicString<C>& operator+=(const C*str)
		{
			append(str, strlen(str));
			return *this;
		}
		
		void set(const BasicString<C>&str)
		{
			C*characters_new = (C*)std::realloc(characters, (str.size+1)*sizeof(C));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			for(size_t i=0; i<str.size; i++)
			{
				characters[i] = str.characters[i];
			}
			size = str.size;
			characters[size] = 0;
		}
		
		void set(const C*str, size_t length)
		{
			C*characters_new = (C*)std::realloc(characters, (length+1)*sizeof(C));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			for(size_t i=0; i<length; i++)
			{
				characters[i] = str[i];
			}
			size = length;
			characters[size] = 0;
		}
		
		BasicString<C>& operator=(const BasicString<C>&str)
		{
			set(str);
			return *this;
		}
		
		BasicString<C>& operator=(const C*str)
		{
			set(str, strlen(str));
			return *this;
		}
		
		int compare(const BasicString<C>&str, int(*compare_function)(const C&,const C&)) const
		{
			if(compare_function == nullptr)
			{
				throw std::invalid_argument("compare_function");
			}
			size_t minsize = (size<str.size) ? size : str.size; /*minimum between this string and other string*/
			for(size_t i=0; i<minsize; i++)
			{
				int result = compare_function(characters[i], str.characters[i]);
				if(result != 0)
				{
					return result;
				}
			}
			if(size<str.size)
			{
				return -1;
			}
			else if(size>str.size)
			{
				return 1;
			}
			return 0;
		}
		
		bool operator<(const BasicString<C>&str) const
		{
			if(compare(str, compare_value)==-1)
			{
				return true;
			}
			return false;
		}
		
		bool operator<=(const BasicString<C>&str) const
		{
			int result = compare(str, compare_value);
			if(result==-1 || result==0)
			{
				return true;
			}
			return false;
		}
		
		bool operator>(const BasicString<C>&str) const
		{
			if(compare(str, compare_value)==1)
			{
				return true;
			}
			return false;
		}
		
		bool operator>=(const BasicString<C>&str) const
		{
			int result = compare(str, compare_value);
			if(result==0 || result==1)
			{
				return true;
			}
			return false;
		}
		
		bool equals(const BasicString<C>&str) const
		{
			if(size == str.size)
			{
				for(size_t i=0; i<size; i++)
				{
					if(characters[i] != str.characters[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		
		bool equals(const C*str) const
		{
			if(size == strlen(str))
			{
				for(size_t i=0; i<size; i++)
				{
					if(characters[i] != str[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		
		bool operator==(const BasicString<C>&str) const
		{
			return equals(str)
		}
		
		bool operator==(const C*str) const
		{
			return equals(str);
		}
		
		bool operator!=(const BasicString<C>&str) const
		{
			return !equals(str);
		}
		
		bool operator!=(const C*str) const
		{
			return !equals(str);
		}
		
		void clear()
		{
			C*characters_new = (C*)std::realloc(characters,sizeof(C));
			if(characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			characters = characters_new;
			characters[0] = 0;
		}
		
		size_t length() const
		{
			return size;
		}
		
		C& charAt(size_t index)
		{
			if(index >= size)
			{
				throw std::out_of_range("index " + std::to_string(index) + " is out of bounds in string with a length of " + std::to_string(size));
			}
			return characters[index];
		}
		
		const C& charAt(size_t index) const
		{
			if(index >= size)
			{
				throw std::out_of_range("index " + std::to_string(index) + " is out of bounds in string with a length of " + std::to_string(size));
			}
			return characters[index];
		}
		
		BasicString<C> replace(C find, C replace) const
		{
			BasicString<C> replacedStr(*this);
			for(size_t i=0; i<size; i++)
			{
				if(replacedStr.characters[i] == find)
				{
					replacedStr.characters[i] = replace;
				}
			}
			return replacedStr;
		}
		
		BasicString<C> replace(const BasicString<C>&find, const BasicString<C>&rep) const
		{
			if(find.size==0)
			{
				return *this;
			}
			else if(find.size > size)
			{
				return *this;
			}
			
			std::vector<size_t> indexes;
			size_t indexesTotal = 0;
			
			size_t finish = size - find.size;
			
			for(size_t i=0; i<=finish; i++)
			{
				if(characters[i]==find.characters[0])
				{
					bool match = true;
					for(size_t j=1; j<find.size; j++)
					{
						if(characters[i+j] != find.characters[j])
						{
							match = false;
							j = find.size;
						}
					}
					
					if(match)
					{
						indexes.resize(indexesTotal+1);
						indexes[indexesTotal] = i;
						indexesTotal++;
						i += (find.size-1);
					}
				}
			}
			
			if(indexes.size()>0)
			{
				String newStr(*this);
				
				bool posDif = false;
				size_t dif;
				if(rep.size >= find.size)
				{
					posDif = true;
					dif = rep.size - find.size;
				}
				else
				{
					posDif = false;
					dif = find.size - rep.size;
				}
				
				size_t totalSize = 0;
				if(posDif)
				{
					totalSize = newStr.size + (indexes.size()*dif);
				}
				else
				{
					totalSize = newStr.size - (indexes.size()*dif);
				}
				
				if(rep.size>find.size)
				{
					C*newStr_characters_new = (C*)std::realloc(newStr.characters, (totalSize+1)*sizeof(C));
					if(newStr_characters_new == nullptr)
					{
						throw std::bad_alloc();
					}
					newStr.characters = newStr_characters_new;
					newStr.characters[totalSize] = 0;
					
					size_t counterNew = totalSize;
					size_t counterOld = newStr.size;
					size_t lastIndex = newStr.size;
					
					bool firstLoop = true;
					size_t i=(indexes.size()-1);
					while(i > 0 || (firstLoop && i == 0))
					{
						if(!firstLoop)
						{
							i--;
						}
						
						bool posOffset = false;
						size_t offset = 0;
						size_t lastIndexEnd = (indexes[i]+find.size);
						if(lastIndex >= lastIndexEnd)
						{
							posOffset = true;
							offset = lastIndex - lastIndexEnd + 1;
						}
						else
						{
							posOffset = false;
							offset = lastIndexEnd - lastIndex + 1;
						}
						
						lastIndex = indexes[i];
						if(posOffset)
						{
							for(size_t j=0; j<offset; j++)
							{
								newStr.characters[counterNew] = newStr.characters[counterOld];
								counterNew--;
								counterOld--;
							}
						}
						
						counterNew-=(rep.size-1);
						counterOld-=(find.size-1);
						
						if(i==0 && counterOld!=0)
						{
							bool firstCounterLoop = true;
							while(counterOld>0 || (firstCounterLoop && counterOld==0))
							{
								if(!firstCounterLoop)
								{
									counterNew--;
									counterOld--;
								}

								newStr.characters[counterNew] = newStr.characters[counterOld];
							
								firstCounterLoop = false;
							}
						}

						firstLoop = false;
					}
					
					newStr.size = totalSize;
				}
				else if(rep.size<find.size)
				{
					size_t counterNew = 0;
					size_t counterOld = 0;
					size_t lastIndex = 0;
					
					for(size_t i=0; i<indexes.size(); i++)
					{
						bool posOffset = false;
						size_t offset = 0;
						if(indexes[i]>=lastIndex)
						{
							posOffset = true;
							offset = indexes[i] - lastIndex;
						}
						else
						{
							posOffset = false;
							offset = lastIndex - indexes[i];
						}
						
						lastIndex = indexes[i] + find.size;
						
						if(posOffset)
						{
							for(size_t j=0; j<offset; j++)
							{
								newStr.characters[counterNew] = newStr.characters[counterOld];
								counterNew++;
								counterOld++;
							}
						}
						
						counterNew += rep.size;
						counterOld += find.size;
						
						if(i==(indexes.size()-1) && counterOld<newStr.size)
						{
							while(counterOld<size)
							{
								newStr.characters[counterNew] = newStr.characters[counterOld];
								counterNew++;
								counterOld++;
							}
						}
					}
					
					C*newStr_characters_new = (C*)std::realloc(newStr.characters, (totalSize+1)*sizeof(C));
					if(newStr_characters_new == nullptr)
					{
						throw std::bad_alloc();
					}
					newStr.characters = newStr_characters_new;
					newStr.characters[totalSize] = 0;
					newStr.size = totalSize;
				}
				
				size_t difCounter = 0;
				
				for(size_t i=0; i<indexes.size(); i++)
				{
					size_t offset = 0;
					if(posDif)
					{
						offset = indexes[i] + difCounter;
					}
					else
					{
						offset = indexes[i] - difCounter;
					}

					for(size_t j=0; j<rep.size; j++)
					{
						newStr.characters[offset+j] = rep.characters[j];
					}

					difCounter+=dif;
				}
				return newStr;
			}
			return *this;
		}
		
		BasicString<C> substring(size_t beginIndex) const
		{
			if(beginIndex>size)
			{
				throw std::out_of_range("index " + std::to_string(beginIndex) + " is out of bounds in string with a length of " + std::to_string(size));
			}
			
			BasicString<C> newStr;
			C*newStr_characters_new = (char*)std::realloc(newStr.characters, ((size-beginIndex)+1)*sizeof(C));
			if(newStr_characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			newStr.characters = newStr_characters_new;
			size_t counter = 0;
			for(size_t i=beginIndex; i<size; i++)
			{
				newStr.characters[counter] = characters[i];
				counter++;
			}
			newStr.characters[counter] = 0;
			newStr.size = counter;
			return newStr;
		}
		
		BasicString<C> substring(size_t beginIndex, size_t endIndex) const
		{
			if(beginIndex > size)
			{
				throw std::out_of_range("index " + std::to_string(beginIndex) + " is out of bounds in string with a length of " + std::to_string(size));
			}
			else if(endIndex > size)
			{
				throw std::out_of_range("index " + std::to_string(endIndex) + " is out of bounds in string with a length of " + std::to_string(size));
			}

			size_t dif = 0;
			bool goUp = true;
			if(beginIndex <= endIndex)
			{
				dif = endIndex - beginIndex;
			}
			else
			{
				goUp = false;
				dif = beginIndex - endIndex;
			}

			BasicString<C> newStr;
			C*newStr_characters_new = (C*)std::realloc(newStr.characters, (dif+1)*sizeof(C));
			if(newStr_characters_new == nullptr)
			{
				throw std::bad_alloc();
			}
			newStr.characters = newStr_characters_new;
			size_t counter = 0;
			if(goUp)
			{
				for(size_t i=beginIndex; i<endIndex; i++)
				{
					newStr.characters[counter] = characters[i];
					counter++;
				}
			}
			else
			{
				bool firstLoop = true;
				size_t i = endIndex;
				while(i > beginIndex || (firstLoop && i==beginIndex))
				{
					if(!firstLoop)
					{
						i--;
					}
					newStr.characters[counter] = characters[i];
					counter++;
					firstLoop = false;
				}
			}
			newStr.characters[counter] = 0;
			newStr.size = counter;
			return newStr;
		}
		
		size_t indexOf(C c, size_t beginIndex, size_t endIndex) const
		{
			if(beginIndex>size)
			{
				throw std::out_of_range((std::string)"beginIndex " + beginIndex + " is out of bounds in string of length " + size);
			}
			else if(endIndex>size)
			{
				throw std::out_of_range((std::string)"endIndex " + endIndex + " is out of bounds in string of length " + size);
			}
			if(size == 0 || endIndex<=beginIndex)
			{
				return STRING_NOTFOUND;
			}
			for(size_t i=beginIndex; i<endIndex; i++)
			{
				if(characters[i] == c)
				{
					return i;
				}
			}
			return STRING_NOTFOUND;
		}
		
		size_t indexOf(C c, size_t beginIndex = 0) const
		{
			return indexOf(c, beginIndex, size);
		}
		
		size_t indexOf(const BasicString<C>&str, size_t beginIndex, size_t endIndex) const
		{
			if(str.size==0 || str.size>size)
			{
				return STRING_NOTFOUND;
			}
			
			size_t finish = size - str.size;
			
			for(size_t i=0; i<=finish; i++)
			{
				if(characters[i]==str.characters[0])
				{
					bool match = true;
					for(size_t j=1; j<str.size; j++)
					{
						if(characters[i+j] != str.characters[j])
						{
							match = false;
							j = str.size;
						}
					}
					
					if(match)
					{
						return i;
					}
				}
			}
			return STRING_NOTFOUND;
		}
		
		size_t indexOf(const BasicString<C>&str, size_t beginIndex = 0) const
		{
			return indexOf(str, beginIndex, size);
		}
		
		size_t lastIndexOf(C c) const
		{
			if(size == 0)
			{
				return STRING_NOTFOUND;
			}
			for(size_t i=(size-1); i!=SIZE_MAX; i--)
			{
				if(characters[i] == c)
				{
					return i;
				}
				if(i == 0)
				{
					return STRING_NOTFOUND;
				}
			}
			return STRING_NOTFOUND;
		}
		
		size_t lastIndexOf(const BasicString<C>&str) const
		{
			if(str.size==0 || str.size>size)
			{
				return STRING_NOTFOUND;
			}
			size_t finish = (str.size-1);
			if(size>0)
			{
				for(size_t i=(size-1); i>=finish; i--)
				{
					if(characters[i]==str.characters[str.size-1])
					{
						bool match = true;
						for(size_t j=1; j<str.size; j++)
						{
							if(characters[i-j] != str.characters[(str.size-1)-j])
							{
								match = false;
								j = str.size;
							}
						}
						
						if(match)
						{
							return (i-(str.size-1));
						}
					}
					if(i == 0)
					{
						return STRING_NOTFOUND;
					}
				}
			}
			return STRING_NOTFOUND;
		}
	};
	
	template<typename C>
	BasicString<C> operator+(const BasicString<C>&left, const BasicString<C>&right)
	{
		BasicString<C> newStr;
		size_t size_new = left.size + right.size;
		C*newStr_characters_new = (char*)std::realloc(newStr.characters, (newSize+1)*sizeof(C));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = newSize;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<newSize; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[newSize] = 0;
		return newStr;
	}
	
	template<typename C>
	BasicString<C> operator+(const BasicString<C>&left, const C*right)
	{
		BasicString<C> newStr;
		size_t size_new = left.size + BasicString<C>::strlen(right);
		C*newStr_characters_new = (char*)std::realloc(newStr.characters, (newSize+1)*sizeof(C));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = newSize;
		for(size_t i=0; i<left.size; i++)
		{
			newStr.characters[i] = left.characters[i];
		}
		size_t counter = 0;
		for(size_t i=left.size; i<newSize; i++)
		{
			newStr.characters[i] = right[counter];
			counter++;
		}
		newStr.characters[newSize] = 0;
		return newStr;
	}
	
	template<typename C>
	BasicString<C> operator+(const C*left, const BasicString<C>&right)
	{
		BasicString<C> newStr;
		size_t left_size = BasicString<C>::strlen(left);
		size_t size_new = left_size + right.size;
		C*newStr_characters_new = (char*)std::realloc(newStr.characters, (newSize+1)*sizeof(C));
		if(newStr_characters_new==nullptr)
		{
			throw std::bad_alloc();
		}
		newStr.characters = newStr_characters_new;
		newStr.size = newSize;
		for(size_t i=0; i<left_size; i++)
		{
			newStr.characters[i] = left[i];
		}
		size_t counter = 0;
		for(size_t i=left_size; i<newSize; i++)
		{
			newStr.characters[i] = right.characters[counter];
			counter++;
		}
		newStr.characters[newSize] = 0;
		return newStr;
	}
	
#ifdef _STRING_USES_GAMELIBRARY
}
#endif

