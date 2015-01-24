
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "../Loader/CharacterInfo.h"

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	class PlayerInfo
	{
	public:
		typedef enum
		{
			PLAYER_OFF,
			PLAYER_HUMAN,
			PLAYER_CPU
		} Mode;
		
		PlayerInfo();
		PlayerInfo(const PlayerInfo&);
		PlayerInfo(CharacterInfo*character, const String&costume);
		~PlayerInfo();
		
		PlayerInfo& operator=(const PlayerInfo&);
		
		CharacterInfo* getCharacterInfo() const;
		const String& getCostume() const;
		const PlayerInfo::Mode& getPlayerMode() const;
		
		void setCharacterInfo(CharacterInfo*);
		void setCostume(const String&);
		void setPlayerMode(const PlayerInfo::Mode&);
		
	private:
		CharacterInfo* character_info;
		String character_costume;
		PlayerInfo::Mode mode;
	};
}
