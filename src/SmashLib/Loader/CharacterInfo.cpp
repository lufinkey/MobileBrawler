
#include "CharacterInfo.hpp"

using namespace fgl;

namespace SmashLib
{
	CharacterInfo::CharacterInfo()
	{
		//
	}
	
	CharacterInfo::~CharacterInfo()
	{
		//
	}
	
	bool CharacterInfo::loadFromPath(const String& folderpath, String* error)
	{
		Dictionary dict;
		bool success = Plist::loadFromPath(&dict, FileTools::combinePathStrings(folderpath, "Info.plist"), error);
		if(success)
		{
			Any val_identifier = dict.get("identifier", Any());
			if(val_identifier.isEmpty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"identifier\"";
				}
				return false;
			}
			else if(!val_identifier.is<String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"identifier\". Value should be a string";
				}
				return false;
			}

			Any val_name = dict.get("name", Any());
			if(val_name.isEmpty())
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
			if(val_creator.isEmpty())
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
			if(val_version.isEmpty())
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
			if(val_minsmashversion.isEmpty())
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
			
			identifier = val_identifier.as<String>();
			name = val_name.as<String>();
			creator = val_creator.as<String>();
			version = val_version.as<String>();
			minsmashversion = val_minsmashversion.as<String>();
			path = folderpath;
			return true;
		}
		if(error != nullptr)
		{
			*error = (String)"Unable to load Info.plist: " + *error;
		}
		return false;
	}
	
	bool CharacterInfo::saveToPath(const String& path, String* error) const
	{
		Dictionary dict;
		dict.set("identifier", identifier);
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

	const String& CharacterInfo::getIdentifier() const
	{
		return identifier;
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
	
	void CharacterInfo::setPath(const String& path_arg)
	{
		path = path_arg;
	}

	void CharacterInfo::setIdentifier(const String& identifier_arg)
	{
		identifier = identifier_arg;
	}
	
	void CharacterInfo::setName(const String& name_arg)
	{
		name = name_arg;
	}
	
	void CharacterInfo::setCreator(const String& creator_arg)
	{
		creator = creator_arg;
	}
	
	void CharacterInfo::setMinimumSmashVersion(const String& minsmashversion_arg)
	{
		minsmashversion = minsmashversion_arg;
	}
}
