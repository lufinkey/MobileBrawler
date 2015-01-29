
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "../../Loader/CharacterInfo.h"

namespace BrawlerLibrary
{
	class PlayerInfo
	{
	public:
		typedef enum
		{
			MODE_OFF,
			MODE_HUMAN,
			MODE_CPU
		} Mode;
		
		PlayerInfo();
		PlayerInfo(const PlayerInfo&);
		PlayerInfo(CharacterInfo*character, const GameLibrary::String&costume, const GameLibrary::ArrayList<PlayerInfo::Mode>& modeCycle);
		~PlayerInfo();
		
		PlayerInfo& operator=(const PlayerInfo&);
		
		CharacterInfo* getCharacterInfo() const;
		const GameLibrary::String& getCostume() const;
		const PlayerInfo::Mode& getPlayerMode() const;
		const GameLibrary::ArrayList<PlayerInfo::Mode>& getPlayerModeCycle() const;
		
		void setCharacterInfo(CharacterInfo*);
		void setCostume(const GameLibrary::String&);
		void setPlayerMode(const PlayerInfo::Mode&);
		void setPlayerModeCycle(const GameLibrary::ArrayList<PlayerInfo::Mode>&modeCycle);
		void cyclePlayerMode();
		void turnPlayerModeOn();
		void turnPlayerModeOff();
		
	private:
		CharacterInfo* character_info;
		GameLibrary::String character_costume;
		
		PlayerInfo::Mode mode;
		GameLibrary::ArrayList<PlayerInfo::Mode> modeCycle;
		unsigned int modeCycleIndex;
	};
}
