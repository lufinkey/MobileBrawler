
#include "CharacterInfo.h"

namespace BrawlerLibrary
{
	CharacterInfo::CharacterInfo()
	{
		//
	}
	
	CharacterInfo::CharacterInfo(const CharacterInfo&info)
	{
		path = info.path;
		name = info.name;
		creator = info.creator;
		minsmashversion = info.minsmashversion;
	}
	
	CharacterInfo::~CharacterInfo()
	{
		//
	}
	
	CharacterInfo& CharacterInfo::operator=(const CharacterInfo&info)
	{
		path = info.path;
		name = info.name;
		creator = info.creator;
		minsmashversion = info.minsmashversion;
		return *this;
	}
	
	bool CharacterInfo::loadFromPath(const String&folderpath, String&error)
	{
		Dictionary dict;
		bool success = dict.loadFromFile(folderpath, error);
		if(success)
		{
			Any val_name = dict.get("name");
			if(val_name.empty())
			{
				error = "plist does not contain value for \"name\"";
				return false;
			}
			else if(!val_name.is<String>())
			{
				error = "incorrect value type for key \"name\"; value type should be string";
				return false;
			}
			
			Any val_creator = dict.get("creator");
			if(val_creator.empty())
			{
				error = "plist does not contain value for \"creator\"";
				return false;
			}
			else if(!val_creator.is<String>())
			{
				error = "incorrect value type for key \"creator\"; value type should be string";
				return false;
			}
			
			Any val_minsmashversion = dict.get("minsmashversion");
			if(val_minsmashversion.empty())
			{
				error = "plist does not contain value for \"minsmashversion\"";
				return false;
			}
			else if(!val_minsmashversion.is<String>())
			{
				error = "incorrect value type for key \"minsmashversion\"; value type should be string";
				return false;
			}
			
			name = val_name.as<String>(true);
			creator = val_creator.as<String>(true);
			minsmashversion = val_minsmashversion.as<String>(true);
			path = folderpath;
			return true;
		}
		return false;
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
