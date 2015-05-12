
#define _CRT_SECURE_NO_WARNINGS

#include "Dictionary.h"
#include "WideString.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <sstream>
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
		for(size_t i=0; i<keys.size() && i<values.size(); i++)
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
		for(size_t i=0; i<contents.size(); i++)
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
		for(size_t i=0; i<contents.size(); i++)
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
		for(size_t i=0; i<contents.size(); i++)
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
		for(size_t i=0; i<contents.size(); i++)
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
		for(size_t i=0; i<contents.size(); i++)
		{
			keys.set(i, contents.get(i).first);
		}
		return keys;
	}

	ArrayList<Any> Dictionary::getValues() const
	{
		ArrayList<Any> keys(contents.size());
		for(size_t i=0; i<contents.size(); i++)
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
	
	size_t Dictionary::size() const
	{
		return contents.size();
	}
	
	Pair<size_t, size_t> Dictionary_getParsePosition(const void*ptr, size_t offset);
	bool Dictionary_parse(const void*ptr, pugi::xml_node, const String&type, String*error);
	bool Dictionary_parseDictionary(const void*ptr, pugi::xml_node&node, Dictionary&dictionary, String*error);
	bool Dictionary_parseArray(const void*ptr, pugi::xml_node&node, ArrayList<Any>&arraylist, String*error);
	bool Dictionary_parseDate(const void*ptr, pugi::xml_node&node, Any&any, String*error);
	bool Dictionary_write(pugi::xml_node&node, const Any&any, String*error);
	bool Dictionary_writeDictionary(pugi::xml_node&node, const Dictionary&dictionary, String*error);
	
	template<typename T>
	bool Dictionary_writeArray(pugi::xml_node&node, const ArrayList<T>&arraylist, String*error)
	{
		pugi::xml_node newNode = node.append_child("array");
		for(size_t i=0; i<arraylist.size(); i++)
		{
			bool result = Dictionary_write(newNode, arraylist.get(i), error);
			if(!result)
			{
				return false;
			}
		}
		return true;
	}
	
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
	
	bool Dictionary::loadFromPointer(const void*ptr, size_t size, String*error)
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
	
	class xml_string_writer : public pugi::xml_writer
	{
	public:
		std::string result;
		
		virtual void write(const void* data, size_t size) override
		{
			result += std::string(static_cast<const char*>(data), size);
		}
	};
	
	bool Dictionary::saveToFile(const String&path, String*error)
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
		
		bool success = Dictionary_writeDictionary(plistNode, *this, error);
		if(success)
		{
			xml_string_writer writer;
			doc.save(writer);
			
			const char* data = writer.result.c_str();
			size_t total = writer.result.length();
			
			FILE*file = std::fopen(path, "w");
			if(file==NULL)
			{
				if(error != nullptr)
				{
					//TODO add checking of errno
					*error = "Unable to open file for writing";
				}
				return false;
			}
			
			size_t written = std::fwrite(data, sizeof(char), total, file);
			if(written != total)
			{
				if(error != nullptr)
				{
					//TODO add checking of errno
					*error = (String)"Unable to write all bytes to file stream";
				}
				return false;
			}
			
			if(std::fclose(file) == EOF)
			{
				if(error!=nullptr)
				{
					//TODO add checking of errno
					*error = "Error closing the file";
				}
				return false;
			}
			return true;
		}
		return success;
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
	
	Pair<size_t, size_t> Dictionary_getParsePosition(const void*ptr, size_t offset)
	{
		size_t currentLine = 1;
		size_t currentOffset = 0;
		char*str = (char*)ptr;
		bool didNewline = false;
		for(size_t i = 0; i < offset; i++)
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
		return Pair<size_t, size_t>(currentLine, currentOffset);
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
				size_t offset = node.offset_debug();
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
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
				size_t offset = node.offset_debug();
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
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
				size_t offset = node.offset_debug();
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
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
			size_t offset = node.offset_debug();
			Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
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
				size_t offset = node.offset_debug();
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
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
				size_t offset = node.offset_debug();
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
				if(error!=nullptr)
				{
					*error = (String)"" + doc_pos.first + ":" + doc_pos.second + ": XML dictionary value expected for key " + key + "but not found";
				}
				return false;
			}
			else if(String("key").equals(it->name()))
			{
				size_t offset = node.offset_debug();
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, offset);
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
			size_t index = arraylist.size();
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
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, node.offset_debug());
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
				Pair<size_t, size_t> doc_pos = Dictionary_getParsePosition(ptr, node.offset_debug());
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
		else if(any.is<WideString>())
		{
			pugi::xml_node newNode = node.append_child("string");
			newNode.append_child(pugi::node_pcdata).set_value((String)any.as<WideString>(false));
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
					newNode.append_child(pugi::node_pcdata).set_value(number.toString());
					return true;
				}
				else
				{
					pugi::xml_node newNode = node.append_child("real");
					newNode.append_child(pugi::node_pcdata).set_value(number.toString());
					return true;
				}
			}
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
		else if(any.is<std::vector<Any> >())
		{
			const std::vector<Any>&list = any.as<std::vector<Any> >(false);
			return Dictionary_writeArray(node, ArrayList<Any>(list), error);
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
		else if(any.is<GameLibrary::Uint64>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Uint64>(false));
			return true;
		}
		else if(any.is<GameLibrary::Uint32>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Uint32>(false));
			return true;
		}
		else if(any.is<GameLibrary::Uint16>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Uint16>(false));
			return true;
		}
		else if(any.is<GameLibrary::Uint8>())
		{
			pugi::xml_node newNode = node.append_child("integer");
			newNode.append_child(pugi::node_pcdata).set_value((String)"" + any.as<GameLibrary::Uint8>(false));
			return true;
		}
		else if(any.is<ArrayList<Dictionary> >())
		{
			const ArrayList<Dictionary>&list = any.as<ArrayList<Dictionary> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<String> >())
		{
			const ArrayList<String>&list = any.as<ArrayList<String> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<std::string> >())
		{
			const ArrayList<std::string>&list = any.as<ArrayList<std::string> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<const char*> >())
		{
			const ArrayList<const char*>&list = any.as<ArrayList<const char*> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<DateTime> >())
		{
			const ArrayList<DateTime>&list = any.as<ArrayList<DateTime> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<Number> >())
		{
			const ArrayList<Number>&list = any.as<ArrayList<Number> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<DataPacket> >())
		{
			const ArrayList<DataPacket>&list = any.as<ArrayList<DataPacket> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Int64> >())
		{
			const ArrayList<GameLibrary::Int64>&list = any.as<ArrayList<GameLibrary::Int64> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Int32> >())
		{
			const ArrayList<GameLibrary::Int32>&list = any.as<ArrayList<GameLibrary::Int32> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Int16> >())
		{
			const ArrayList<GameLibrary::Int16>&list = any.as<ArrayList<GameLibrary::Int16> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Int8> >())
		{
			const ArrayList<GameLibrary::Int8>&list = any.as<ArrayList<GameLibrary::Int8> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Uint64> >())
		{
			const ArrayList<GameLibrary::Uint64>&list = any.as<ArrayList<GameLibrary::Uint64> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Uint32> >())
		{
			const ArrayList<GameLibrary::Uint32>&list = any.as<ArrayList<GameLibrary::Uint32> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Uint16> >())
		{
			const ArrayList<GameLibrary::Uint16>&list = any.as<ArrayList<GameLibrary::Uint16> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<GameLibrary::Uint8> >())
		{
			const ArrayList<GameLibrary::Uint8>&list = any.as<ArrayList<GameLibrary::Uint8> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<long double> >())
		{
			const ArrayList<long double>&list = any.as<ArrayList<long double> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<double> >())
		{
			const ArrayList<double>&list = any.as<ArrayList<double> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else if(any.is<ArrayList<float> >())
		{
			const ArrayList<float>&list = any.as<ArrayList<float> >(false);
			return Dictionary_writeArray(node, list, error);
		}
		else
		{
			pugi::xml_node newNode = node.append_child("string");
			newNode.append_child(pugi::node_pcdata).set_value(any.toString());
			return true;
		}
	}
	
	bool Dictionary_writeDictionary(pugi::xml_node&node, const Dictionary&dictionary, String*error)
	{
		pugi::xml_node newNode = node.append_child("dict");
		const ArrayList<Pair<String, Any> >& contents = dictionary.getContents();
		for(size_t i=0; i<contents.size(); i++)
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
	
	void Dictionary_toJSON(const Any&any, String*output);
	void Dictionary_toJSON(const String&string, String*output);
	void Dictionary_toJSON(const WideString&string, String*output);
	void Dictionary_toJSON(const ArrayList<Any>&arraylist, String*output);
	void Dictionary_toJSON(const Dictionary&dict, String*output);
	void Dictionary_toJSON(const Number&number, String*output);
	
	template<typename T>
	void Dictionary_toJSON(const ArrayList<T>&arraylist, String*output)
	{
		output->append("[", 1);
		size_t size = arraylist.size();
		size_t lastIndex = size-1;
		for(size_t i=0; i<size; i++)
		{
			Dictionary_toJSON((Any)arraylist.get(i), output);
			if(i != lastIndex)
			{
				output->append(",");
			}
		}
		output->append("]", 1);
	}
	
	void Dictionary_toJSON(const Any&any, String*output)
	{
		if(any.is<Dictionary>())
		{
			Dictionary_toJSON(any.as<Dictionary>(false), output);
		}
		else if(any.is<ArrayList<Any> >())
		{
			Dictionary_toJSON(any.as<ArrayList<Any> >(false), output);
		}
		else if(any.is<String>())
		{
			Dictionary_toJSON((WideString)any.as<String>(false), output);
		}
		else if(any.is<WideString>())
		{
			Dictionary_toJSON(any.as<WideString>(false), output);
		}
		else if(any.is<Number>())
		{
			Dictionary_toJSON(any.as<Number>(false), output);
		}
		else if(any.is<DataPacket>())
		{
			Dictionary_toJSON(any.as<DataPacket>(false).toString(), output);
		}
		else if(any.is<DateTime>())
		{
			Dictionary_toJSON(any.as<DateTime>(false).toString(), output);
		}
		else if(any.is<std::string>())
		{
			Dictionary_toJSON((WideString)any.as<std::string>(false), output);
		}
		else if(any.is<const char*>())
		{
			Dictionary_toJSON((WideString)any.as<const char*>(false), output);
		}
		else if(any.is<std::vector<Any> >())
		{
			Dictionary_toJSON(ArrayList<Any>(any.as<std::vector<Any> >(false)), output);
		}
		else if(any.is<GameLibrary::Int64>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Int64>(false)), output);
		}
		else if(any.is<GameLibrary::Int32>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Int32>(false)), output);
		}
		else if(any.is<GameLibrary::Int16>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Int16>(false)), output);
		}
		else if(any.is<GameLibrary::Int8>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Int8>(false)), output);
		}
		else if(any.is<long double>())
		{
			Dictionary_toJSON(Number(any.as<long double>(false)), output);
		}
		else if(any.is<double>())
		{
			Dictionary_toJSON(Number(any.as<double>(false)), output);
		}
		else if(any.is<float>())
		{
			Dictionary_toJSON(Number(any.as<float>(false)), output);
		}
		else if(any.is<bool>())
		{
			Dictionary_toJSON(Number(any.as<bool>(false)), output);
		}
		else if(any.is<GameLibrary::Uint64>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Uint64>(false)), output);
		}
		else if(any.is<GameLibrary::Uint32>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Uint32>(false)), output);
		}
		else if(any.is<GameLibrary::Uint16>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Uint16>(false)), output);
		}
		else if(any.is<GameLibrary::Uint8>())
		{
			Dictionary_toJSON(Number(any.as<GameLibrary::Uint8>(false)), output);
		}
		else if(any.is<ArrayList<Dictionary> >())
		{
			Dictionary_toJSON(any.as<ArrayList<Dictionary> >(false), output);
		}
		else if(any.is<ArrayList<String> >())
		{
			Dictionary_toJSON(any.as<ArrayList<String> >(false), output);
		}
		else if(any.is<ArrayList<std::string> >())
		{
			Dictionary_toJSON(any.as<ArrayList<std::string> >(false), output);
		}
		else if(any.is<ArrayList<const char*> >())
		{
			Dictionary_toJSON(any.as<ArrayList<const char*> >(false), output);
		}
		else if(any.is<ArrayList<DateTime> >())
		{
			Dictionary_toJSON(any.as<ArrayList<DateTime> >(false), output);
		}
		else if(any.is<ArrayList<Number> >())
		{
			Dictionary_toJSON(any.as<ArrayList<Number> >(false), output);
		}
		else if(any.is<ArrayList<DataPacket> >())
		{
			Dictionary_toJSON(any.as<ArrayList<DataPacket> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Int64> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Int64> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Int32> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Int32> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Int16> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Int16> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Int8> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Int8> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Uint64> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Uint64> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Uint32> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Uint32> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Uint16> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Uint16> >(false), output);
		}
		else if(any.is<ArrayList<GameLibrary::Uint8> >())
		{
			Dictionary_toJSON(any.as<ArrayList<GameLibrary::Uint8> >(false), output);
		}
		else if(any.is<ArrayList<long double> >())
		{
			Dictionary_toJSON(any.as<ArrayList<long double> >(false), output);
		}
		else if(any.is<ArrayList<double> >())
		{
			Dictionary_toJSON(any.as<ArrayList<double> >(false), output);
		}
		else if(any.is<ArrayList<float> >())
		{
			Dictionary_toJSON(any.as<ArrayList<float> >(false), output);
		}
		else
		{
			Dictionary_toJSON((WideString)any.toString(), output);
		}
	}
	
	void Dictionary_toJSON(const String&string, String*output)
	{
		output->append("\"", 1);
		size_t length = string.length();
		for(size_t i=0; i<length; i++)
		{
			char c = string.charAt(i);
			unsigned int uint = (unsigned int)(*((unsigned char*)&c));
			if(uint<0x20 && uint>=0)
			{
				switch(uint)
				{
					case 0x00:
						output->append("\\0", 2);
						break;
					
					case 0x07:
						output->append("\\a", 2);
						break;

					case 0x08:
						output->append("\\b", 2);
						break;

					case 0x09:
						output->append("\\t", 2);
						break;
					
					case 0x0A:
						output->append("\\n", 2);
						break;
					
					case 0x0B:
						output->append("\\v", 2);
						break;

					case 0x0C:
						output->append("\\f", 2);
						break;
					
					case 0x0D:
						output->append("\\r", 2);
						break;

					default:
					{
						std::stringstream ss;
						ss << std::hex << uint;
						String hex = ss.str();
						while(hex.length() < 4)
						{
							hex = "0" + hex;
						}
						output->append("\\u"+hex, 6);
					}
					break;
				}
			}
			else if(c == '\\')
			{
				output->append("\\\\", 2);
			}
			else if(c == '\"')
			{
				output->append("\\\"", 2);
			}
			else
			{
				output->append(c);
			}
		}
		output->append("\"", 1);
	}
	
	void Dictionary_toJSON(const WideString&string, String*output)
	{
		output->append("\"", 1);
		size_t length = string.length();
		for(size_t i=0; i<length; i++)
		{
			wchar_t c = string.charAt(i);
			if(c<0x20 && c>=0)
			{
				switch(c)
				{
					case 0x00:
						output->append("\\0", 2);
						break;
					
					case 0x07:
						output->append("\\a", 2);
						break;

					case 0x08:
						output->append("\\b", 2);
						break;

					case 0x09:
						output->append("\\t", 2);
						break;
					
					case 0x0A:
						output->append("\\n", 2);
						break;
					
					case 0x0B:
						output->append("\\v", 2);
						break;

					case 0x0C:
						output->append("\\f", 2);
						break;
					
					case 0x0D:
						output->append("\\r", 2);
						break;

					default:
					{
						std::stringstream ss;
						ss << std::hex << ((unsigned int)c);
						String hex = ss.str();
						while(hex.length() < 4)
						{
							hex = "0" + hex;
						}
						output->append("\\u"+hex, 6);
					}
					break;
				}
			}
			else if(c == L'\\')
			{
				output->append("\\\\", 2);
			}
			else if(c == L'\"')
			{
				output->append("\\\"", 2);
			}
			else if(c > CHAR_MAX)
			{
				std::stringstream ss;
				ss << std::hex << ((unsigned int)c);
				String hex = ss.str();
				while(hex.length() < 4)
				{
					hex = "0" + hex;
				}
				output->append("\\u"+hex, 6);
			}
			else
			{
				output->append(c);
			}
		}
		output->append("\"", 1);
	}

	void Dictionary_toJSON(const ArrayList<Any>&arraylist, String*output)
	{
		output->append("[", 1);
		size_t size = arraylist.size();
		size_t lastIndex = size-1;
		for(size_t i=0; i<size; i++)
		{
			Dictionary_toJSON(arraylist.get(i), output);
			if(i != lastIndex)
			{
				output->append(",");
			}
		}
		output->append("]", 1);
	}
	
	void Dictionary_toJSON(const Dictionary&dict, String*output)
	{
		output->append("{", 1);
		const ArrayList<Pair<String, Any> >& contents = dict.getContents();
		size_t size = contents.size();
		size_t lastIndex = size-1;
		for(size_t i=0; i<size; i++)
		{
			const Pair<String, Any>& pair = contents.get(i);
			String keyString;
			Dictionary_toJSON(pair.first, &keyString);
			output->append(keyString + ":");
			Dictionary_toJSON(pair.second, output);
			if(i != lastIndex)
			{
				output->append(",");
			}
		}
		output->append("}", 1);
	}
	
	void Dictionary_toJSON(const Number&number, String*output)
	{
		output->append(number.toString());
	}
	
	String Dictionary::toJSON() const
	{
		String json;
		Dictionary_toJSON(*this, &json);
		return json;
	}
	
	String Dictionary::toString() const
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
		
		bool success = Dictionary_writeDictionary(plistNode, *this, nullptr);
		if(!success)
		{
			return "";
		}
		else
		{
			xml_string_writer writer;
			doc.save(writer);
			return writer.result;
		}
	}
}
