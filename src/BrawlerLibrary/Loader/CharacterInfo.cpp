
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
	
	bool CharacterInfo::loadFromPath(const String&path, String&error)
	{
		error = "this feature is not yet implemented";
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
	
	const String& CharacterInfo::getMinimumSmashVersion() const
	{
		return minsmashversion;
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
