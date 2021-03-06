
#include "CharacterInfo.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	CharacterInfo::CharacterInfo()
	{
		//
	}
	
	CharacterInfo::CharacterInfo(const CharacterInfo& info)
	{
		path = info.path;
		name = info.name;
		creator = info.creator;
		version = info.version;
		minsmashversion = info.minsmashversion;
	}
	
	CharacterInfo::~CharacterInfo()
	{
		//
	}
	
	CharacterInfo& CharacterInfo::operator=(const CharacterInfo& info)
	{
		path = info.path;
		name = info.name;
		creator = info.creator;
		version = info.version;
		minsmashversion = info.minsmashversion;
		return *this;
	}
	
	bool CharacterInfo::loadFromPath(const String& folderpath, String* error)
	{
		Dictionary dict;
		bool success = Plist::loadFromFile(&dict, FileTools::combinePathStrings(folderpath, "Info.plist"), error);
		if(success)
		{
			Any val_name = dict.get("name", Any());
			if(val_name.empty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"name\"";
				}
				return false;
			}
			else if(!val_name.is<String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"name\". Value should be a string";
				}
				return false;
			}
			
			Any val_creator = dict.get("creator", Any());
			if(val_creator.empty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"creator\"";
				}
				return false;
			}
			else if(!val_creator.is<String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"creator\". Value should be a string";
				}
				return false;
			}
			
			Any val_version = dict.get("version", Any());
			if(val_version.empty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"version\"";
				}
				return false;
			}
			else if(!val_version.is<String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"version\". Value should be a string";
				}
				return false;
			}
			
			Any val_minsmashversion = dict.get("minsmashversion", Any());
			if(val_minsmashversion.empty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"minsmashversion\"";
				}
				return false;
			}
			else if(!val_minsmashversion.is<String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"minsmashversion\". Value should be a string";
				}
				return false;
			}
			
			ArrayList<FileTools::DirectoryEntry> entries;
			FileTools::readEntriesFromDirectory(FileTools::combinePathStrings(folderpath, "costumes"), &entries);
			for(unsigned int i = 0; i < entries.size(); i++)
			{
				//TODO do something with the costumes
			}
			
			name = val_name.as<String>(false);
			creator = val_creator.as<String>(false);
			version = val_version.as<String>(false);
			minsmashversion = val_minsmashversion.as<String>(false);
			path = folderpath;
			return true;
		}
		if(error != nullptr)
		{
			*error = (String)"Unable to load Info.plist: " + *error;
		}
		return false;
	}
	
	bool CharacterInfo::saveToPath(const String&path, String*error) const
	{
		Dictionary dict;
		dict.set("name", name);
		dict.set("creator", creator);
		dict.set("version", version);
		dict.set("minsmashversion", minsmashversion);
		return Plist::saveToFile(dict, FileTools::combinePathStrings(path, "Info.plist"), error);
	}
	
	const String& CharacterInfo::getPath() const
	{
		return path;
	}
	
	const String& CharacterInfo::getName() const
	{
		return name;
	}
	
	const String& CharacterInfo::getCreator() const
	{
		return creator;
	}
	
	const String& CharacterInfo::getMinimumSmashVersion() const
	{
		return minsmashversion;
	}
	
	void CharacterInfo::setPath(const String&folderpath)
	{
		path = folderpath;
	}
	
	void CharacterInfo::setName(const String&nm)
	{
		name = nm;
	}
	
	void CharacterInfo::setCreator(const String&creatr)
	{
		creator = creatr;
	}
	
	void CharacterInfo::setMinimumSmashVersion(const String&minver)
	{
		minsmashversion = minver;
	}
}
