
#include "Any.h"
#include "ArrayList.h"
#include "Pair.h"
#include "String.h"

#pragma once

namespace GameLibrary
{
	class Dictionary
	{
	private:
		ArrayList<Pair<String, Any>> contents;

	public:
		Dictionary();
		Dictionary(const ArrayList<String>& keys, const ArrayList<Any>& values);
		~Dictionary();

		template<class T>
		void set(const String& key, const T& value)
		{
			for(unsigned int i=0; i<contents.size(); i++)
			{
				Pair<String, Any>& pair = contents.get(i);
				if(pair.first.equals(key))
				{
					contents.set(i, Pair(key, Any(value)));
					return;
				}
			}
			contents.add(Pair(key, Any(value)));
		}

		template<class T>
		T& get(const String& key)
		{
			for(unsigned int i = 0; i < contents.size(); i++)
			{
				Pair<String, Any>& pair = contents.get(i);
				if(pair.first.equals(key))
				{
					return pair.second.as<T>();
				}
			}
		}

		template<class T>
		const T& get(const String& key) const
		{
			for(unsigned int i = 0; i < contents.size(); i++)
			{
				Pair<String, Any>& pair = contents.get(i);
				if(pair.first.equals(key))
				{
					return pair.second.as<T>();
				}
			}
		}
	};
}