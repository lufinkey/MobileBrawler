
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
		ArrayList<Pair<String, Any> > contents;

	public:
		Dictionary();
		Dictionary(const ArrayList<String>& keys, const ArrayList<Any>& values);
		~Dictionary();

		void set(const String& key, const Any& value);
		Any& get(const String& key);
		const Any& get(const String& key) const;

		ArrayList<String> getKeys() const;
		ArrayList<Any> getValues() const;

		void clear();

		bool loadFromFile(const String&path);
		bool saveToFile(const String&path);
	};
}