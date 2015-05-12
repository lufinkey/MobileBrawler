
#pragma once

#include <climits>
//#include <initializer_list>
#include <vector>
#include <array>

#ifndef _ARRAYLIST_STANDALONE
#include "../Exception/Utilities/ArrayListOutOfBoundsException.h"
namespace GameLibrary
{
#else
	#include <exception>
	#include <string>
	
	class ArrayListOutOfBoundsException : public std::exception
	{
	private:
		std::string message;

	public:
		ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&exception) : std::exception(exception)
		{
			message = exception.message;
		}

		ArrayListOutOfBoundsException(size_t index, size_t size)
		{
			message = (std::string)"index " + std::to_string(index) + " is out of bounds in ArrayList with a size of " + std::to_string(size);
		}

		virtual ~ArrayListOutOfBoundsException()
		{
			//
		}

		virtual const char* what() const _NOEXCEPT
		{
			return message.c_str();
		}
	};
#endif

#define ARRAYLIST_NOTFOUND SIZE_MAX
	
	template <typename T>
	class ArrayList
	{
	private:
		std::vector<T> objects;
		
	public:
		ArrayList()
		{
			//
		}
		
		ArrayList(const ArrayList<T>& arr)
		{
			size_t length = arr.objects.size();
			objects.resize(length);
			for(size_t i=0; i<length; i++)
			{
				objects[i] = arr[i];
			}
		}
		
		template<size_t Size>
		ArrayList(const std::array<T, Size>& arr)
		{
			objects.resize(Size);
			for(size_t i = 0; i < Size; i++)
			{
				objects[i] = arr[i];
			}
		}
		
		ArrayList(const std::vector<T>& vect)
		{
			size_t length = vect.size();
			objects.resize(length);
			for(size_t i=0; i<length; i++)
			{
				objects[i] = vect[i];
			}
		}
		
		/*ArrayList(const std::initializer_list<T>&list)
		{
			objects.resize(list.size())
			for(int i=0; i<list.size(); i++)
			{
				objects[i] = list[i];
			}
		}*/
		
		explicit ArrayList(size_t size)
		{
			objects.resize(size);
		}
		
		ArrayList(const T*data, size_t size)
		{
			objects.resize(size);
			for(size_t i=0; i<size; i++)
			{
				objects[i] = data[i];
			}
		}
		
		~ArrayList()
		{
			//
		}

		ArrayList<T>& operator=(const ArrayList<T>& arr)
		{
			size_t length = arr.objects.size();
			objects.resize(length);
			objects.shrink_to_fit();
			for(size_t i=0; i<length; i++)
			{
				objects[i] = arr.objects[i];
			}
			return *this;
		}
		
		ArrayList<T>& operator=(const std::vector<T>& vect)
		{
			size_t length = vect.size();
			objects.resize(length);
			for(size_t i=0; i<length; i++)
			{
				objects[i] = vect[i];
			}
			return *this;
		}

		T& operator[] (size_t index)
		{
			if(index<objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		const T& operator[] (size_t index) const
		{
			if(index<objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		T& get(size_t index)
		{
			if(index < objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		const T& get(size_t index) const
		{
			if(index<objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}

		T* getData()
		{
			return objects.data();
		}

		const T* getData() const
		{
			return objects.data();
		}
		
		void set(size_t index, const T&obj)
		{
			if(index<objects.size())
			{
				objects[index] = obj;
			}
			else
			{
				throw ArrayListOutOfBoundsException(index, objects.size());
			}
		}
		
		void add(const T&obj)
		{
			size_t length = objects.size();
			objects.resize(length+1);
			objects[length] = obj;
		}
		
		void add(size_t index, const T&obj)
		{
			if(index>objects.size())
			{
				throw ArrayListOutOfBoundsException(index, objects.size());
			}
			size_t length = objects.size();
			objects.resize(length+1);
			for(size_t i=length; i>index; i--)
			{
				objects[i] = objects[i-1];
				if(i==index)
				{
					objects[index] = obj;
					return;
				}
			}
			objects[index] = obj;
		}
		
		void remove(size_t index)
		{
			if(index > objects.size())
			{
				throw ArrayListOutOfBoundsException(index, objects.size());
			}
			size_t length = objects.size();
			if(length==1)
			{
				if(index==0)
				{
					objects.resize(0);
				}
				else
				{
					throw ArrayListOutOfBoundsException(index, length);
				}
			}
			else if(index<length)
			{
				for(size_t i=(index+1); i<length; i++)
				{
					objects[i-1] = objects[i];
				}
				objects.resize(length-1);
			}
			else
			{
				throw ArrayListOutOfBoundsException(index, length);
			}
		}
		
		void clear()
		{
			objects.resize(0);
			objects.shrink_to_fit();
		}
		
		size_t size() const
		{
			return objects.size();
		}

		void resize(size_t size)
		{
			objects.resize(size);
			objects.shrink_to_fit();
		}
		
		bool contains(const T& obj) const
		{
			if(indexOf(obj) != ARRAYLIST_NOTFOUND)
			{
				return true;
			}
			return false;
		}

		size_t indexOf(const T& obj) const
		{
			size_t length = objects.size();
			for(size_t i=0; i<length; i++)
			{
				const T& cmp = (const T&)objects[i];
				if((const T&)obj==(const T&)cmp)
				{
					return i;
				}
			}
			return ARRAYLIST_NOTFOUND;
		}
	};
#ifndef _ARRAYLIST_STANDALONE
}
#endif
