
#include "Rules.h"

namespace BrawlerLibrary
{
	PlayerInfo::PlayerInfo()
	{
		character_info = nullptr;
	}
	
	PlayerInfo::PlayerInfo(const PlayerInfo&info)
	{
		character_info = info.character_info;
		character_costume = info.character_costume;
	}
	
	PlayerInfo::PlayerInfo(CharacterInfo*character, const String&costume)
	{
		character_info = character;
		character_costume = costume;
	}
	
	PlayerInfo::~PlayerInfo()
	{
		//
	}
	
	PlayerInfo& PlayerInfo::operator=(const PlayerInfo&info)
	{
		character_info = info.character_info;
		character_costume = info.character_costume;
		return *this;
	}
	
	CharacterInfo* PlayerInfo::getCharacterInfo() const
	{
		return character_info;
	}
	
	const String& PlayerInfo::getCostume() const
	{
		return character_costume;
	}
	
	void PlayerInfo::setCharacterInfo(CharacterInfo*info)
	{
		character_info = info;
	}
	
	void PlayerInfo::setCostume(const String&costume)
	{
		character_costume = costume;
	}
	
	Rules::Rules()
	{
		//
	}
	
	Rules::~Rules()
	{
		//
	}
	
	unsigned int Rules::getPlayerCount() const
	{
		return players.size();
	}
	
	void Rules::setPlayerCount(unsigned int count)
	{
		players.resize(count);
	}
}
