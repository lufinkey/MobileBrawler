
#define _CRT_SECURE_NO_WARNINGS

#include "Dictionary.h"
#include <ctime>
#include <cstdlib>
#include <pugixml.hpp>
#include <base64.hpp>

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
	
	Any& Dictionary::set(const String& key, const Any& value)
	{
		for(unsigned int i=0; i<contents.size(); i++)
		{
			Pair<String, Any>& pair = contents.get(i);
			if(pair.first.equals(key))
			{
				contents.set(i, Pair<String, Any>(key, value));
				return contents.get(i).second;
			}
		}
		contents.add(Pair<String, Any>(key, value));
		return contents.get(contents.size()-1).second;
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
	
	const ArrayList<Pair<String, Any> >& Dictionary::getContents() const
	{
		return contents;
	}

	void Dictionary::clear()
	{
		contents.clear();
	}
	
	Pair<unsigned int, unsigned int> Dictionary_getParsePosition(const void*ptr, unsigned int offset);
	bool Dictionary_parse(const void*ptr, pugi::xml_node, const String&type, String*error);
	bool Dictionary_parseDictionary(const void*ptr, pugi::xml_node&node, Dictionary&dictionary, String*error);
	bool Dictionary_parseArray(const void*ptr, pugi::xml_node&node, ArrayList<Any>&arraylist, String*error);
	bool Dictionary_parseDate(const void*ptr, pugi::xml_node&node, Any&any, String*error);
	bool Dictionary_write(pugi::xml_node&node, const Any&any, String*error);
	bool Dictionary_writeDictionary(pugi::xml_node&node, const Dictionary&dictionary, String*error);
	bool Dictionary_writeArray(pugi::xml_node&node, const ArrayList<Any>&dictionary, String*error);
	
	bool Dictionary::loadFromFile(const String&path, String*error)
	{
		//load the file into memory
		FILE*file = std::fopen(path, "r");
		if (file == nullptr)
		{
			//TODO add switch for errno
			if(error!=nullptr)
			{
				*error = "Unable to load Dictionary from file";
			}
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
	
	bool Dictionary::loadFromString(const String&string, String*error)
	{
		return loadFromPointer((const char*)string, string.length(), error);
	}
	
	bool Dictionary::loadFromData(const DataPacket&data, String*error)
	{
		return loadFromPointer((const void*)data.getData(), data.size(), error);
	}
	
	bool Dictionary::loadFromPointer(const void*ptr, unsigned int size, String*error)
	{
		if(ptr == nullptr)
		{
			if(error!=nullptr)
			{
				*error = "Cannot load from null pointer";
			}
			return false;
		}
		else if(size == 0)
		{
			if(error!=nullptr)
			{
				*error = "Cannot load from empty pointer";
			}
			return false;
		}
		
		const char*str = (const char*)ptr;
		
		// infer plist type from header.  If it has the bplist00 header as first 8
		// bytes, then it's a binary plist.  Otherwise, assume it's XML
		
		if(size>8 && String(str,8).equals("bplist00"))
		{
			//binary plist
			if(error!=nullptr)
			{
				*error = "Binary plists are not yet supported";
			}
			return false;
		}
		else
		{
			//XML plist
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer(ptr, (size_t)size);
			if(!result)
			{
				if(error!=nullptr)
				{
					*error = result.description();
				}
				return false;
			}
			pugi::xml_node rootNode = doc.child("plist").first_child();
			String rootNodeName = rootNode.name();
			if(rootNodeName.equals(""))
			{
				return true;
			}
			else if(rootNodeName.equals("dict"))
			{
				return Dictionary_parseDictionary(ptr, rootNode, *this, error);
			}
			else
			{
				if(error!=nullptr)
				{
					*error = "Plist root is not a \"dict\" object";
				}
				return false;
			}
		}
	}
	
	bool Dictionary::saveToFile(const String&path, bool binary, String*error)
	{
		if(binary)
		{
			if(error!=nullptr)
			{
				*error = "This feature is not yet implemented";
			}
			return false;
		}
		else
		{
			pugi::xml_document doc;
			pugi::xml_node decNode = doc.append_child(pugi::node_declaration);
			decNode.append_attribute("version") = "1.0";
			decNode.append_attribute("encoding") = "UTF-8";
		
			// doctype node
			doc.append_child(pugi::node_doctype).set_value("plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"");
		
			// root node
			pugi::xml_node plistNode = doc.append_child("plist");
			plistNode.append_attribute("version") = "1.0";
			
			return Dictionary_writeDictionary(plistNode, *this, error);
		}
		return true;
	}
	
// plist parse functions
	
	void Dictionary_base64Decode(const char* encodedData, std::vector<char>&data)
	{
		std::insert_iterator<std::vector<char> > ii(data, data.begin());
		base64<char> b64;
		int state = 0;
		b64.get(encodedData, encodedData + strlen(encodedData), ii, state);
	}
	
	void Dictionary_base64Encode(std::string&dataEncoded, const DataPacket&data)
	{
		const char* str = (const char*)data.getData();
		std::vector<char> data_vect(str, str+data.size());
		dataEncoded.clear();
		std::insert_iterator<std::string> ii(dataEncoded, dataEncoded.begin());
		base64<char> b64;
		int state = 0;
		
		#if defined(_WIN32) || defined(_WIN64)
			b64.put(data_vect.begin(), data_vect.end(), ii, state, base64<>::crlf());
		#else
			b64.put(data_vect.begin(), data_vect.end(), ii, state , base64<>::lf());
		#endif
	}
	
	Pair<unsigned int, unsigned int> Dictionary_getParsePosition(const void*ptr, unsigned int offset)
	{
		unsigned int currentLine = 1;
		unsigned int currentOffset = 0;
		char*str = (char*)ptr;
		bool didNewline = false;
		for(unsigned int i = 0; i < offset; i++)
		{
			if(str[i]=='\n')
			{
				currentLine++;
				currentOffset = 0;
				didNewline = true;
			}
			else if(str[i] == '\r')
			{
				if(!didNewline)
				{
					currentLine++;
					currentOffset = 0;
				}
			}
			else
			{
				currentOffset++;
			}
			
			if(didNewline)
			{
				didNewline = false;
			}
		}
		return Pair<unsigned int, unsigned int>(currentLine, currentOffset);
	}
	
	bool Dictionary_parse(const void*ptr, pugi::xml_node&node, Any&any, String*error)
	{
		String type = node.name();

		if(type.equals("dict"))
		{
			any = Dictionary();
			return Dictionary_parseDictionary(ptr, node, any.as<Dictionary>(false), error);
		}
		else if(type.equals("array"))
		{
			any = ArrayList<Any>();
			return Dictionary_parseArray(ptr, node, any.as<ArrayList<Any> >(false), error);
		}
		else if(type.equals("string"))
		{
			any = String(node.first_child().value());
			return true;
		}
		else if(type.equals("data"))
		{
			const char*str = (const char*)node.first_child().value();
			std::vector<char> data_vect;
			Dictionary_base64Decode(str, data_vect);
			any = DataPacket((const void*)data_vect.data(), data_vect.size());
			return true;
		}
		else if(type.equals("date"))
		{
			return Dictionary_parseDate(ptr, node, any, error);
		}
		else if(type.equals("integer"))
		{
			try
			{
				const char* str = node.first_child().value();
				if(str[0] == '\0')
				{
					any = Number(0LL);
				}
				else
				{
					any = Number(String::asLongLong(str));
				}
			}
			catch(const NumberFormatException&e)
			{
				unsigned int offset = node.offset_debug();
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": " + e.message;
				}
				return false;
			}
			return true;
		}
		else if(type.equals("real"))
		{
			try
			{
				const char* str = node.first_child().value();
				if(str[0] == '\0')
				{
					any = Number(0.0L);
				}
				else
				{
					any = Number(String::asLongDouble(String(str)));
				}
			}
			catch(const NumberFormatException&e)
			{
				unsigned int offset = node.offset_debug();
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": " + e.message;
				}
				return false;
			}
			return true;
		}
		else if(type.equals("boolean"))
		{
			bool val = false;
			String value = node.first_child().value();
			if(value.equals("true") || value.equals("TRUE") || value.equals("yes") || value.equals("YES"))
			{
				val = true;
			}
			else if(value.equals("false") || value.equals("FALSE") || value.equals("no") || value.equals("NO"))
			{
				val = false;
			}
			else
			{
				unsigned int offset = node.offset_debug();
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": Invalid boolean value";
				}
				return false;
			}
			any = Number(val);
			return true;
		}
		else if(type.equals("true"))
		{
			any = Number(true);
			return true;
		}
		else if(type.equals("false"))
		{
			any = Number(false);
			return true;
		}
		else
		{
			unsigned int offset = node.offset_debug();
			Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
			if(error!=nullptr)
			{
				*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": Invalid tag";
			}
			return false;
		}
	}

	bool Dictionary_parseDictionary(const void*ptr, pugi::xml_node&node, Dictionary&dict, String*error)
	{
		for(pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
		{
			if(!String("key").equals(it->name()))
			{
				unsigned int offset = node.offset_debug();
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": XML dictionary key expected but not found";
				}
				return false;
			}
			
			String key(it->first_child().value());
			++it;
			
			if(it == node.end())
			{
				unsigned int offset = node.offset_debug();
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": XML dictionary value expected for key " + key + "but not found";
				}
				return false;
			}
			else if(String("key").equals(it->name()))
			{
				unsigned int offset = node.offset_debug();
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": XML dictionary value expected for key " + key + "but found another key node";
				}
				return false;
			}
			
			Any& value = dict.set(key, Any());
			bool result = Dictionary_parse(ptr, *it, value, error);
			if(!result)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Dictionary_parseArray(const void*ptr, pugi::xml_node&node, ArrayList<Any>&arraylist, String*error)
	{
		for(pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
		{
			unsigned int index = arraylist.size();
			arraylist.add(Any());
			bool result = Dictionary_parse(ptr, node, arraylist.get(index), error);
			if(!result)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Dictionary_parseDate(const void*ptr, pugi::xml_node&node, Any&any, String*error)
	{
		String datetimeStr = node.first_child().value();
		int month, day, year, hour24, minute, second;
		
		time_t _time = 0;

		// parse date string.  E.g.  2011-09-25T02:31:04Z
		sscanf(datetimeStr, "%4d-%2d-%2dT%2d:%2d:%2dZ", &year, &month, &day, &hour24, &minute, &second);
		bool UTC = true;
		
		struct tm tmTime;
		tmTime.tm_hour = hour24;
		tmTime.tm_mday = day;
		tmTime.tm_year = year - 1900;
		tmTime.tm_sec = second;
		tmTime.tm_mon = month - 1;
		tmTime.tm_min = minute;

		//get proper day light savings.

		time_t loc = std::time(NULL);
		struct tm tmLoc = *localtime(&loc);
		//std::cout<<"tmLoc.tm_isdst = "<<tmLoc.tm_isdst<<std::endl;
		tmTime.tm_isdst = tmLoc.tm_isdst;

		if(UTC)
		{
			//_time = timegm(&tmTime);

			tmTime.tm_isdst = 0;
			_time = mktime(&tmTime);
			if(_time < -1)
			{
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, node.offset_debug());
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": Invalid date format";
				}
				return false;
			}

			// don't have timegm for all systems so here's a portable way to do it.

			struct tm tmTimeTemp;
			#if defined(_WIN32) || defined(_WIN64)
				gmtime_s(&tmTimeTemp, &_time);
			#else
				gmtime_r(&_time, &tmTimeTemp);
			#endif

			time_t timeTemp = mktime(&tmTimeTemp);

			time_t diff = _time - timeTemp;
			_time += diff;
		}
		else
		{
			_time = mktime(&tmTime);
			if(_time < -1)
			{
				Pair<unsigned int, unsigned int> doc_pos = Dictionary_getParsePosition(ptr, node.offset_debug());
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": Invalid date format";
				}
				return false;
			}
		}
		
		any = DateTime(_time);
		return true;
	}
	
// plist write functions
	
	bool Dictionary_write(pugi::xml_node&node, const Any&any, String*error)
	{
		if(any.is<Dictionary>())
		{
			const Dictionary&dict = any.as<Dictionary>(false);
			return Dictionary_writeDictionary(node, dict, error);
		}
		else if(any.is<ArrayList<Any> >())
		{
			const ArrayList<Any>&list = any.as<ArrayList<Any> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<String>())
		{
			pugi::xml_node newNode = node.append_child("string");
			newNode.append_child(pugi::node_pcdata).set_value(any.as<String>(false));
			return true;
		}
		else if(any.is<std::string>())
		{
			pugi::xml_node newNode = node.append_child("string");
			newNode.append_child(pugi::node_pcdata).set_value(any.as<std::string>(false).c_str());
			return true;
		}
		else if(any.is<const char*>())
		{
			pugi::xml_node newNode = node.append_child("string");
			newNode.append_child(pugi::node_pcdata).set_value(any.as<const char*>(false));
			return true;
		}
		else if(any.is<DataPacket>())
		{
			pugi::xml_node newNode = node.append_child("data");
			const DataPacket&data = any.as<DataPacket>(false);
			std::string encodedStr;
			Dictionary_base64Encode(encodedStr, data);
			newNode.append_child(pugi::node_pcdata).set_value(encodedStr.c_str());
			return true;
		}
		else if(any.is<DateTime>())
		{
			pugi::xml_node newNode = node.append_child("date");
			const DateTime& datetime = any.as<DateTime>(false);
			String datetimeStr = datetime.toString("%Y-%m-%dT%H:%M:%SZ");
			newNode.append_child(pugi::node_pcdata).set_value(datetimeStr);
			return true;
		}
		else if(any.is<Number>())
		{
			const Number& number = any.as<Number>(false);
			Number::NumberType numberType = number.getType();
			if(numberType == Number::TYPE_NULL)
			{
				pugi::xml_node newNode = node.append_child("integer");
				newNode.append_child(pugi::node_pcdata).set_value("");
				return true;
			}
			else if(numberType == Number::TYPE_BOOL)
			{
				bool val = number.asBool();
				if(val)
				{
					node.append_child("true");
				}
				else
				{
					node.append_child("false");
				}
				return true;
			}
			else
			{
				if(number.isIntegral())
				{
					pugi::xml_node newNode = node.append_child("integer");
					newNode.append_child(pugi::node_pcdata).set_value(number.asString());
					return true;
				}
				else
				{
					pugi::xml_node newNode = node.append_child("real");
					newNode.append_child(pugi::node_pcdata).set_value(number.asString());
					return true;
				}
			}
		}
		else if(any.is<GameLibrary::Int64>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Int64>(false));
			return true;
		}
		else if(any.is<GameLibrary::Int32>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Int32>(false));
			return true;
		}
		else if(any.is<GameLibrary::Int16>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Int16>(false));
			return true;
		}
		else if(any.is<GameLibrary::Int8>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Int8>(false));
			return true;
		}
		else if(any.is<long double>())
		{
			pugi::xml_node newNode = node.append_child("real");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<long double>(false));
			return true;
		}
		else if(any.is<double>())
		{
			pugi::xml_node newNode = node.append_child("real");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<double>(false));
			return true;
		}
		else if(any.is<float>())
		{
			pugi::xml_node newNode = node.append_child("real");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<float>(false));
			return true;
		}
		else if(any.is<bool>())
		{
			bool val = any.as<bool>(false);
			if(val)
			{
				node.append_child("true");
			}
			else
			{
				node.append_child("false");
			}
			return true;
		}
		else
		{
			if(error!=nullptr)
			{
				*error = "Unknown type";
			}
			return false;
		}
	}
	
	bool Dictionary_writeDictionary(pugi::xml_node&node, const Dictionary&dictionary, String*error)
	{
		pugi::xml_node newNode = node.append_child("dict");
		const ArrayList<Pair<String, Any> >& contents = dictionary.getContents();
		for(unsigned int i=0; i<contents.size(); i++)
		{
			const Pair<String, Any>& pair = contents.get(i);
			pugi::xml_node keyNode = newNode.append_child("key");
			keyNode.append_child(pugi::node_pcdata).set_value(pair.first);
			bool result = Dictionary_write(newNode, pair.second, error);
			if(!result)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Dictionary_writeArray(pugi::xml_node&node, const ArrayList<Any>&arraylist, String*error)
	{
		pugi::xml_node newNode = node.append_child("array");
		for(unsigned int i=0; i<arraylist.size(); i++)
		{
			bool result = Dictionary_write(newNode, arraylist.get(i), error);
			if(!result)
			{
				return false;
			}
		}
		return true;
	}
}
