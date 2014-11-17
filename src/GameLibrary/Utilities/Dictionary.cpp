
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
}
