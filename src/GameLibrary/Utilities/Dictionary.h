
#pragma once

#include "Any.h"
#include "ArrayList.h"
#include "DataPacket.h"
#include "Pair.h"
#include "String.h"
#include "Time/DateTime.h"

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

		void set(const String& key, const Any& value, Any**valueptr=nullptr);
		Any& get(const String& key);
		const Any& get(const String& key) const;
		bool has(const String& key) const;

		ArrayList<String> getKeys() const;
		ArrayList<Any> getValues() const;

		void clear();

		bool loadFromFile(const String&path, String&error=String());
		bool loadFromData(const DataPacket&data, String&error=String());
		bool loadFromPointer(const void*ptr, unsigned int size, String&error=String());
		bool loadFromString(const String&string, String&error=String());
		bool saveToFile(const String&path, String&error=String());
	};
}