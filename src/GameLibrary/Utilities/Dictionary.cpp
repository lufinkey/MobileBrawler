
#define _CRT_SECURE_NO_WARNINGS

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

	Any Dictionary::get(const String& key) const
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
	
	typedef enum
	{
		DICT_KEYTAG_BEGIN_OPEN,
		DICT_KEYTAG_BEGIN_NAME,
		DICT_KEYTAG_BEGIN_CLOSE,
		DICT_KEYTAG_CONTENT,
		DICT_KEYTAG_END_OPEN,
		DICT_KEYTAG_END_NAME,
		DICT_KEYTAG_END_CLOSE,
		DICT_TAG_BEGIN_OPEN,
		DICT_TAG_BEGIN_NAME,
		DICT_TAG_ATTRIBUTE_NAME,
		DICT_TAG_ATTRIBUTE_EQUALITY,
		DICT_TAG_ATTRIBUTE_DEF,
		DICT_TAG_BEGIN_CLOSE,
		DICT_TAG_END_OPEN,
		DICT_TAG_END_NAME,
		DICT_TAG_END_CLOSE
	} DictionaryParsePosition;
	
	typedef enum
	{
		PIECETYPE_TAG,
		PIECETYPE_INTERMEDIATE
	} DictionaryPieceType;
	
	typedef struct
	{
		unsigned int index;
		unsigned int size;
		DictionaryPieceType type;
	} DictionaryParsePiece;
	
	DictionaryParsePiece Dictionary_createParsePiece(unsigned int index, unsigned int size, DictionaryPieceType type)
	{
		DictionaryParsePiece piece;
		piece.index = index;
		piece.size = size;
		piece.type = type;
		return piece;
	}
	
	bool Dictionary_extractParsePieces(const char*cptr, ArrayList<DictionaryParsePiece>&parsePieces, String&error)
	{
		//TODO implement
		error = "This feature is not yet implemented";
		return false;
	}
	
	bool Dictionary_readParsePieces(const char*cptr, const ArrayList<DictionaryParsePiece>&parsePieces, ArrayList<Pair<String, Any> >&content, String&error)
	{
		//TODO implement
		error = "This feature is not yet implemented";
		return false;
	}
	
	bool Dictionary::loadFromPointer(const void*ptr, unsigned int size, String&error)
	{
		ArrayList<DictionaryParsePiece> parsePieces;
		bool success = Dictionary_extractParsePieces((const char*)ptr, parsePieces, error);
		if(!success)
		{
			return false;
		}
		return Dictionary_readParsePieces((const char*)ptr, parsePieces, contents, error);
	}

	bool Dictionary::saveToFile(const String&path, String&error)
	{
		//TODO implement dictionary saving
		return false;
	}
}
