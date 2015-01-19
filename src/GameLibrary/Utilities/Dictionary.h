
#pragma once

#include "Any.h"
#include "ArrayList.h"
#include "DataPacket.h"
#include "Pair.h"
#include "String.h"
#include "Time/DateTime.h"
#include "../Exception/NumberFormatException.h"

//Dictionary loading and saving code adapted from PlistCpp. https://github.com/animetrics/PlistCpp
//All credit goes to animetrics

namespace GameLibrary
{
	class DictionaryProfile;
	
	class Dictionary
	{
	private:
		ArrayList<Pair<String, Any> > contents;

	public:
		Dictionary();
		Dictionary(const ArrayList<String>& keys, const ArrayList<Any>& values);
		virtual ~Dictionary();

		Any& set(const String& key, const Any& value);
		Any& get(const String& key);
		const Any& get(const String& key) const;
		bool has(const String& key) const;

		ArrayList<String> getKeys() const;
		ArrayList<Any> getValues() const;
		const ArrayList<Pair<String, Any> >& getContents() const;

		void clear();

		bool loadFromFile(const String&path, String*error=nullptr);
		bool loadFromData(const DataPacket&data, String*error=nullptr);
		bool loadFromPointer(const void*ptr, unsigned int size, String*error=nullptr);
		bool loadFromString(const String&string, String*error=nullptr);
		bool saveToFile(const String&path, bool binary=false, String*error=nullptr);
	};
}