
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
	
	CharacterInfo& CharacterInfo::operator=(const CharacterInfo&)
	{
		//
	}
	
	bool CharacterInfo::loadFromPath(const String&path, String&error)
	{
		error = "this feature is not yet implemented";
		return false;
	}
	
	const String& CharacterInfo::getPath() const
	{
		//
	}
	
	const String& CharacterInfo::getName() const
	{
		//
	}
	
	const String& CharacterInfo::getMinimumSmashVersion() const
	{
		//
	}
	
	void CharacterInfo::setPath(const String&path)
	{
		//
	}
	
	void CharacterInfo::setName(const String&name)
	{
		//
	}
	
	void CharacterInfo::setMinimumSmashVersion() const
	{
		//
	}
}
