
#include "StageInfo.hpp"

namespace SmashBros
{
	StageInfo::StageInfo()
	{
		//
	}
	
	bool StageInfo::loadFromPath(const fgl::String& folderpath, fgl::String* error)
	{
		fgl::Dictionary dict;
		bool success = fgl::Plist::loadFromPath(&dict, folderpath + "/Info.plist", error);
		if(success)
		{
			fgl::Any val_identifier = dict.get("identifier", fgl::Any());
			if(val_identifier.isEmpty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"identifier\"";
				}
				return false;
			}
			else if(!val_identifier.is<fgl::String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"identifier\". Value should be a string";
				}
				return false;
			}

			fgl::Any val_name = dict.get("name", fgl::Any());
			if(val_name.isEmpty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"name\"";
				}
				return false;
			}
			else if(!val_name.is<fgl::String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"name\". Value should be a string";
				}
				return false;
			}
			
			fgl::Any val_creator = dict.get("creator", fgl::Any());
			if(val_creator.isEmpty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"creator\"";
				}
				return false;
			}
			else if(!val_creator.is<fgl::String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"creator\". Value should be a string";
				}
				return false;
			}
			
			fgl::Any val_version = dict.get("version", fgl::Any());
			if(val_version.isEmpty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"version\"";
				}
				return false;
			}
			else if(!val_version.is<fgl::String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"version\". Value should be a string";
				}
				return false;
			}
			
			fgl::Any val_minsmashversion = dict.get("minsmashversion", fgl::Any());
			if(val_minsmashversion.isEmpty())
			{
				if(error!=nullptr)
				{
					*error = "Plist does not contain value for \"minsmashversion\"";
				}
				return false;
			}
			else if(!val_minsmashversion.is<fgl::String>())
			{
				if(error!=nullptr)
				{
					*error = "Incorrect value type for key \"minsmashversion\". Value should be a string";
				}
				return false;
			}
			
			identifier = val_identifier.as<fgl::String>();
			name = val_name.as<fgl::String>();
			creator = val_creator.as<fgl::String>();
			version = val_version.as<fgl::String>();
			minsmashversion = val_minsmashversion.as<fgl::String>();
			path = folderpath;
			return true;
		}
		if(error != nullptr)
		{
			*error = (fgl::String)"Unable to load Info.plist: " + *error;
		}
		return false;
	}
	
	const fgl::String& StageInfo::getPath() const
	{
		return path;
	}

	const fgl::String& StageInfo::getIdentifier() const
	{
		return identifier;
	}
	
	const fgl::String& StageInfo::getName() const
	{
		return name;
	}
	
	const fgl::String& StageInfo::getCreator() const
	{
		return creator;
	}
	
	const fgl::String& StageInfo::getMinimumSmashVersion() const
	{
		return minsmashversion;
	}
	
	void StageInfo::setPath(const fgl::String& path_arg)
	{
		path = path_arg;
	}

	void StageInfo::setIdentifier(const fgl::String& identifier_arg)
	{
		identifier = identifier_arg;
	}
	
	void StageInfo::setName(const fgl::String& name_arg)
	{
		name = name_arg;
	}
	
	void StageInfo::setCreator(const fgl::String& creator_arg)
	{
		creator = creator_arg;
	}
	
	void StageInfo::setMinimumSmashVersion(const fgl::String& minsmashversion_arg)
	{
		minsmashversion = minsmashversion_arg;
	}

	fgl::String StageInfo::getIconPath() const
	{
		return fgl::FileTools::combinePathStrings(path, "icon.png");
	}

	fgl::String StageInfo::getPreviewPath() const
	{
		return fgl::FileTools::combinePathStrings(path, "preview.png");
	}
}
