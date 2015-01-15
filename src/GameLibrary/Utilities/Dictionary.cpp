
#define _CRT_SECURE_NO_WARNINGS

#include "Dictionary.h"
#include <Plist.hpp>
#include <PlistDate.hpp>

namespace GameLibrary
{
	static Any Dictionary_nullEntry;

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

	void Dictionary::set(const String& key, const Any& value, Any**valueptr)
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
		if(valueptr!=nullptr)
		{
			*valueptr = &contents.get(contents.size()-1).second;
		}
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
		Dictionary_nullEntry = nullptr;
		return Dictionary_nullEntry;
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
		Dictionary_nullEntry = nullptr;
		return Dictionary_nullEntry;
	}
	
	bool Dictionary::has(const String& key) const
	{
		for(unsigned int i=0; i<contents.size(); i++)
		{
			const Pair<String, Any>& pair = contents.get(i);
			if(pair.first.equals(key))
			{
				return true;
			}
		}
		return false;
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

	bool Dictionary::loadFromFile(const String&path, String&error)
	{
		//load the file into memory
		FILE*file = std::fopen(path, "r");
		if (file == nullptr)
		{
			//TODO add switch for errno
			error = "Unable to load Dictionary from file";
			return false;
		}
		std::fseek(file, 0, SEEK_END);
		long fileSize = (long)std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
		char* fileContent = (char*)std::malloc(fileSize);
		std::fread((void*)fileContent, 1, fileSize, file);
		std::fclose(file);
		
		//parse the data
		bool success = loadFromPointer((void*)fileContent, fileSize, error);
		std::free(fileContent);
		return success;
	}
	
	bool Dictionary::loadFromString(const String&string, String&error)
	{
		return loadFromPointer((const char*)string, string.length(), error);
	}
	
	bool Dictionary::loadFromData(const DataPacket&data, String&error)
	{
		return loadFromPointer((const void*)data.getData(), data.size(), error);
	}
	
	bool Dictionary_boostToAny(Any&any, const boost::any&value, String&error);
	bool Dictionary_anyToBoost(boost::any&any, const Any&value, String&error);
	
	bool Dictionary_convertFromMap(Dictionary&dictionary, std::map<std::string, boost::any>&map, String&error)
	{
		for(std::map<std::string,boost::any>::iterator it=map.begin(); it!=map.end(); ++it)
		{
			const std::string& key = it->first;
			boost::any& value = it->second;
			Any*anyptr = nullptr;
			dictionary.set(String(key), Any(), &anyptr);
			bool success = Dictionary_boostToAny(*anyptr, value, error);
			if(!success)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Dictionary_convertToMap(std::map<std::string, boost::any>&map, const Dictionary&dictionary, String&error)
	{
		error = "This feature is not yet implemented";
		return false;
	}
	
	bool Dictionary_boostToAny(Any&any, const boost::any&value, String&error)
	{
		//String
		try
		{
			String val = boost::any_cast<std::string>(value);
			any = val;
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		//Integer
		try
		{
			GameLibrary::Int64 val = boost::any_cast<GameLibrary::Int64>(value);
			any = val;
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		//Real
		try
		{
			double val = boost::any_cast<double>(value);
			any = val;
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		//Dictionary
		try
		{
			std::map<std::string, boost::any>& map = boost::any_cast<std::map<std::string, boost::any> >(value);
			any = Dictionary();
			Dictionary_convertFromMap(any.as<Dictionary>(), map, error);
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		//ArrayList
		try
		{
			std::vector<boost::any>& vals = boost::any_cast<std::vector<boost::any> >(value);
			any = ArrayList<Any>();
			ArrayList<Any>& anylist = any.as<ArrayList<Any> >();
			for(unsigned int i=0; i<vals.size(); i++)
			{
				Any val;
				anylist.add(val);
				Dictionary_boostToAny(anylist.get(i), vals.at(i), error);
			}
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		//DataPacket
		try
		{
			std::vector<char>& valdata = boost::any_cast<std::vector<char> >(value);
			any = DataPacket((byte*)valdata.data(),valdata.size());
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		//Date
		try
		{
			Plist::Date& date = boost::any_cast<Plist::Date>(value);
			any = DateTime(date.timeAsEpoch());
			return true;
		}
		catch(const boost::bad_any_cast&){}
		
		error = "Unrecognized data type";
		return false;
	}
	
	bool Dictionary_anyToBoost(boost::any&any, const Any&value, String&error)
	{
		//String
		try
		{
			const std::string&val = value.as<String>();
			any = val;
			return true;
		}
		catch(BadAnyCastException&){}
		
		//Integer
		try
		{
			GameLibrary::Int64 val = value.as<GameLibrary::Int64>();
			any = val;
			return true;
		}
		catch(const BadAnyCastException&){}
		
		//Real
		try
		{
			double val = value.as<double>();
			any = val;
			return true;
		}
		catch(const BadAnyCastException&){}
		
		//Dictionary
		try
		{
			const Dictionary&dict = value.as<Dictionary>();
			std::map<std::string, boost::any> map;
			Dictionary_convertToMap(map, dict, error);
			any = map;
			return true;
		}
		catch(const BadAnyCastException&){}
		
		//ArrayList
		try
		{
			const ArrayList<Any>& vals = value.as<ArrayList<Any> >();
			std::vector<boost::any> anylist;
			for(unsigned int i=0; i<vals.size(); i++)
			{
				boost::any val;
				anylist.resize(i+1);
				anylist[i] = val;
				Dictionary_anyToBoost(anylist.at(i), vals.get(i), error);
			}
			return true;
		}
		catch(const BadAnyCastException&){}
		
		//DataPacket
		try
		{
			const DataPacket& valdata = value.as<DataPacket>();
			const char* data = (const char*)valdata.getData();
			any = std::vector<char>(data, data+valdata.size());
			return true;
		}
		catch(const BadAnyCastException&){}
		
		//Date
		try
		{
			const DateTime& date = value.as<DateTime>();
			any = date.toTimeType();
			return true;
		}
		catch(const BadAnyCastException&){}
		
		error = "Unrecognized data type";
		return false;
	}
	
	bool Dictionary::loadFromPointer(const void*ptr, unsigned int size, String&error)
	{
		std::map<std::string, boost::any> dict;
		try
		{
			Plist::readPlist((const char*)ptr, (int64_t)size, dict);
		}
		catch(Plist::Error&e)
		{
			error = e.what();
			return false;
		}
		return Dictionary_convertFromMap(*this, dict, error);
	}

	bool Dictionary::saveToFile(const String&path, String&error)
	{
		std::map<std::string, boost::any> dict;
		bool success = Dictionary_convertToMap(dict, *this, error);
		if(!success)
		{
			return false;
		}
		try
		{
			Plist::writePlistXML(path, dict);
		}
		catch(Plist::Error&e)
		{
			error = e.what();
			return false;
		}
		return true;
	}
}
