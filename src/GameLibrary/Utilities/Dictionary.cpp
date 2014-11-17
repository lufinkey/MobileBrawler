
#include "Dictionary.h"

namespace GameLibrary
{
	Dictionary::Dictionary()
	{
		//
	}

	Dictionary::Dictionary(const ArrayList<String>& keys, const ArrayList<Any>& values)
	{
		for(unsigned int i=0; i<keys.size() && i<values.size(); i++)
		{
			contents.add(Pair<String,Any>(keys.get(i), values.get(i)));
		}
	}

	Dictionary::~Dictionary()
	{
		//
	}

	void Dictionary::set(const String& key, const Any& value)
	{
		for(unsigned int i=0; i<contents.size(); i++)
		{
			Pair<String, Any>& pair = contents.get(i);
			if(pair.first.equals(key))
			{
				contents.set(i, Pair<String, Any>(key, value));
				return;
			}
		}
		contents.add(Pair<String, Any>(key, value));
	}

	Any& Dictionary::get(const String& key)
	{
		for(unsigned int i=0; i<contents.size(); i++)
		{
			Pair<String, Any>& pair = contents.get(i);
			if(pair.first.equals(key))
			{
				return pair.second;
			}
		}
		return Any(nullptr);
	}

	const Any& Dictionary::get(const String& key) const
	{
		for(unsigned int i=0; i<contents.size(); i++)
		{
			const Pair<String, Any>& pair = contents.get(i);
			if(pair.first.equals(key))
			{
				return pair.second;
			}
		}
		return Any(nullptr);
	}

	ArrayList<String> Dictionary::getKeys() const
	{
		ArrayList<String> keys(contents.size());
		for(unsigned int i=0; i<contents.size(); i++)
		{
			keys.set(i, contents.get(i).first);
		}
		return keys;
	}

	ArrayList<Any> Dictionary::getValues() const
	{
		ArrayList<Any> keys(contents.size());
		for(unsigned int i=0; i<contents.size(); i++)
		{
			keys.set(i, contents.get(i).second);
		}
		return keys;
	}

	void Dictionary::clear()
	{
		contents.clear();
	}

	bool Dictionary::loadFromFile(const String&path)
	{
		//TODO implement dictionary loading
		return false;
	}

	bool Dictionary::saveToFile(const String&path)
	{
		//TODO implement dictionary saving
		return false;
	}
}
