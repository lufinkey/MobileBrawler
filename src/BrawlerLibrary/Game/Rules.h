
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "../Loader/CharacterInfo.h"
#include "WinCondition.h"

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	class PlayerInfo
	{
	private:
		CharacterInfo* character_info;
		String character_costume;
		
	public:
		PlayerInfo();
		PlayerInfo(const PlayerInfo&);
		PlayerInfo(CharacterInfo*character, const String&costume);
		~PlayerInfo();
		
		PlayerInfo& operator=(const PlayerInfo&);
		
		CharacterInfo* getCharacterInfo() const;
		const String& getCostume() const;
		
		void setCharacterInfo(CharacterInfo*);
		void setCostume(const String&);
	};
	
	class Rules
	{
	public:
		Rules();
		~Rules();
		
		unsigned int getPlayerCount() const;
		void setPlayerCount(unsigned int count);
		
	private:
		ArrayList<PlayerInfo> players;
		WinCondition* winCondition;
	};
}
