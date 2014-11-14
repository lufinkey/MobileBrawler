
#include <vector>

#pragma once

namespace GameLibrary
{
	template <class T>
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
			for(int i=0; i<length; i++)
			{
				objects[i] = arr[i];
			}
		}
		
		//TODO implement if std::initializer_list is available
		/*ArrayList(const std::initializer_list<T>&list)
		{
			objects.resize(list.size())
			for(int i=0; i<list.size(); i++)
			{
				objects[i] = list[i];
			}
		}*/
		
		ArrayList(unsigned int size)
		{
			objects.resize(size);
		}
		
		~ArrayList()
		{
			objects.resize(0);
		}
		
		T& get(unsigned int index)
		{
			return objects[index];
		}
		
		const T& get(unsigned int index) const
		{
			return objects[index];
		}
		
		T& operator[] (unsigned int index)
		{
			return objects[index];
		}
		
		const T& operator[] (unsigned int index) const
		{
			return objects[index];
		}
		
		void set(unsigned int index, const T&obj)
		{
			objects[index] = obj;
		}
		
		void add(const T&obj)
		{
			unsigned int length = objects.size();
			objects.resize(length+1);
			objects[length] = obj;
		}
		
		void add(unsigned int index, const T&obj)
		{
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
			unsigned int length = objects.size();
			if(length==1 && index==0)
			{
				objects.resize(0);
			}
			else if(index<length && index>=0)
			{
				for(int i=(index+1); i<length; i++)
				{
					objects[i-1] = objects[i];
				}
				objects.resize(length-1);
			}
		}
		
		void clear()
		{
			objects.resize(0);
		}
		
		unsigned int size() const
		{
			return objects.size();
		}
		
		ArrayList& operator=(const ArrayList<T>& arr)
		{
			unsigned int length = arr.objects.size();
			objects.resize(length);
			for(int i=0; i<length; i++)
			{
				objects[i] = arr.objects[i];
			}
			
			return *this;
		}
		
		bool contains(const T& obj) const
		{
			unsigned int length = objects.size();
			for(int i=0; i<length; i++)
			{
				const T& cmp = (const T&)objects[i];
				if((const T&)obj==(const T&)cmp)
				{
					return true;
				}
			}
			return false;
		}
	};
}
