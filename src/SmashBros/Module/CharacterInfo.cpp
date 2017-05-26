
#include "CharacterInfo.hpp"

namespace SmashBros
{
	CharacterInfo::CharacterInfo()
	{
		//
	}
	
	CharacterInfo::~CharacterInfo()
	{
		//
	}
	
	bool CharacterInfo::loadFromPath(const fgl::String& folderpath, fgl::String* error)
	{
		fgl::Dictionary dict;
		bool success = fgl::Plist::loadFromPath(&dict, fgl::FileTools::combinePathStrings(folderpath, "Info.plist"), error);
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
			
			fgl::ArrayList<fgl::FileTools::DirectoryEntry> entries;
			fgl::FileTools::readEntriesFromDirectory(fgl::FileTools::combinePathStrings(folderpath, "costumes"), &entries);
			for(unsigned int i = 0; i < entries.size(); i++)
			{
				//TODO do something with the costumes
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
	
	bool CharacterInfo::saveToPath(const fgl::String& path, fgl::String* error) const
	{
		fgl::Dictionary dict;
		dict.set("identifier", identifier);
		dict.set("name", name);
		dict.set("creator", creator);
		dict.set("version", version);
		dict.set("minsmashversion", minsmashversion);
		return fgl::Plist::saveToFile(dict, fgl::FileTools::combinePathStrings(path, "Info.plist"), error);
	}
	
	const fgl::String& CharacterInfo::getPath() const
	{
		return path;
	}

	const fgl::String& CharacterInfo::getIdentifier() const
	{
		return identifier;
	}
	
	const fgl::String& CharacterInfo::getName() const
	{
		return name;
	}
	
	const fgl::String& CharacterInfo::getCreator() const
	{
		return creator;
	}
	
	const fgl::String& CharacterInfo::getMinimumSmashVersion() const
	{
		return minsmashversion;
	}
	
	void CharacterInfo::setPath(const fgl::String& path_arg)
	{
		path = path_arg;
	}

	void CharacterInfo::setIdentifier(const fgl::String& identifier_arg)
	{
		identifier = identifier_arg;
	}
	
	void CharacterInfo::setName(const fgl::String& name_arg)
	{
		name = name_arg;
	}
	
	void CharacterInfo::setCreator(const fgl::String& creator_arg)
	{
		creator = creator_arg;
	}
	
	void CharacterInfo::setMinimumSmashVersion(const fgl::String& minsmashversion_arg)
	{
		minsmashversion = minsmashversion_arg;
	}

	fgl::String CharacterInfo::getIconPath() const
	{
		return fgl::FileTools::combinePathStrings(path, "icon.png");
	}

	fgl::String CharacterInfo::getPortraitPath() const
	{
		return fgl::FileTools::combinePathStrings(path, "portrait.png");
	}
}
