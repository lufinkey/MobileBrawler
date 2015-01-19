
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
	
	bool CharacterInfo::loadFromPath(const String&folderpath, String*error)
	{
		Dictionary dict;
		bool success = dict.loadFromFile(folderpath, error);
		if(success)
		{
			Any val_name = dict.get("name");
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
			
			Any val_creator = dict.get("creator");
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
			
			Any val_minsmashversion = dict.get("minsmashversion");
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
			
			name = val_name.as<String>(false);
			creator = val_creator.as<String>(false);
			minsmashversion = val_minsmashversion.as<String>(false);
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
