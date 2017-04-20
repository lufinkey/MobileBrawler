
#include "StageInfo.h"

namespace BrawlerLibrary
{
	using namespace fgl;
	
	StageInfo::StageInfo()
	{
		//
	}
	
	StageInfo::StageInfo(const StageInfo&info)
	{
		path = info.path;
		name = info.name;
		creator = info.creator;
		version = info.version;
		minsmashversion = info.minsmashversion;
	}
	
	StageInfo::~StageInfo()
	{
		//
	}
	
	StageInfo& StageInfo::operator=(const StageInfo&info)
	{
		path = info.path;
		name = info.name;
		creator = info.creator;
		version = info.version;
		minsmashversion = info.minsmashversion;
		return *this;
	}
	
	bool StageInfo::loadFromPath(const String&folderpath, String*error)
	{
		Dictionary dict;
		bool success = Plist::loadFromPath(&dict, folderpath + "/Info.plist", error);
		if(success)
		{
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
	
	const String& StageInfo::getPath() const
	{
		return path;
	}
	
	const String& StageInfo::getName() const
	{
		return name;
	}
	
	const String& StageInfo::getCreator() const
	{
		return creator;
	}
	
	const String& StageInfo::getMinimumSmashVersion() const
	{
		return minsmashversion;
	}
	
	void StageInfo::setPath(const String&folderpath)
	{
		path = folderpath;
	}
	
	void StageInfo::setName(const String&nm)
	{
		name = nm;
	}
	
	void StageInfo::setCreator(const String&creatr)
	{
		creator = creatr;
	}
	
	void StageInfo::setMinimumSmashVersion(const String&minver)
	{
		minsmashversion = minver;
	}
}
