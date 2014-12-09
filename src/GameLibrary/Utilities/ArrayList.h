
#include <climits>
#include <initializer_list>
#include <vector>

#pragma once

#define ARRAYLIST_USES_GAMELIBRARY

#ifdef ARRAYLIST_USES_GAMELIBRARY
#include "../Exception/Utilities/ArrayListOutOfBoundsException.h"
namespace GameLibrary
{
#else
	#include <exception>
	
	class ArrayListOutOfBoundsException : public std::exception
	{
	private:
		std::string message;

	public:
		ArrayListOutOfBoundsException(const ArrayListOutOfBoundsException&exception) : std::exception(exception)
		{
			message = exception.message;
		}

		ArrayListOutOfBoundsException(unsigned int index, unsigned int size)
		{
			message = (std::string)"index " + index + " is out of bounds in ArrayList with a size of " + size);
		}

		virtual ~ArrayListOutOfBoundsException()
		{
			//
		}

		virtual const char* what() const
		{
			return message.c_str();
		}
	};
#endif

#define ARRAYLIST_NOTFOUND UINT_MAX
	
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
			unsigned int length = arr.objects.size();
			objects.resize(length);
			for(unsigned int i=0; i<length; i++)
			{
				objects[i] = arr[i];
			}
		}
		
		ArrayList(const std::initializer_list<T>&list)
		{
			objects.resize(list.size())
			for(int i=0; i<list.size(); i++)
			{
				objects[i] = list[i];
			}
		}
		
		ArrayList(unsigned int size)
		{
			objects.resize(size);
		}
		
		~ArrayList()
		{
			//
		}

		ArrayList<T>& operator=(const ArrayList<T>& arr)
		{
			unsigned int length = arr.objects.size();
			objects.resize(length);
			objects.shrink_to_fit();
			for(unsigned int i=0; i<length; i++)
			{
				objects[i] = arr.objects[i];
			}
			
			return *this;
		}

		T& operator[] (unsigned int index)
		{
			if(index<objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		const T& operator[] (unsigned int index) const
		{
			if(index<objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		T& get(unsigned int index)
		{
			if(index < objects.size())
			{
				return objects[index];
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		const T& get(unsigned int index) const
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
		
		void set(unsigned int index, const T&obj)
		{
			if(index<objects.size())
			{
				objects[index] = obj;
			}
			throw ArrayListOutOfBoundsException(index, objects.size());
		}
		
		void add(const T&obj)
		{
			unsigned int length = objects.size();
			objects.resize(length+1);
			objects[length] = obj;
		}
		
		void add(unsigned int index, const T&obj)
		{
			if(index>objects.size())
			{
				throw ArrayListOutOfBoundsException(index, objects.size());
			}
			unsigned int length = objects.size();
			objects.resize(length+1);
			for(unsigned int i=length; i>index; i--)
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
		
		void remove(unsigned int index)
		{
			if(index > objects.size())
			{
				throw ArrayListOutOfBoundsException(index, objects.size());
			}
			unsigned int length = objects.size();
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
				for(unsigned int i=(index+1); i<length; i++)
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
		
		unsigned int size() const
		{
			return objects.size();
		}

		void resize(unsigned int size)
		{
			objects.resize(size);
			objects.shrink_to_fit();
		}
		
		bool contains(const T& obj) const
		{
			unsigned int length = objects.size();
			for(unsigned int i=0; i<length; i++)
			{
				const T& cmp = (const T&)objects[i];
				if((const T&)obj==(const T&)cmp)
				{
					return true;
				}
			}
			return false;
		}

		unsigned int indexOf(const T& obj) const
		{
			unsigned int length = objects.size();
			for(unsigned int i=0; i<length; i++)
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
}
