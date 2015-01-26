
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "../../Loader/CharacterInfo.h"

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
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
		PlayerInfo(CharacterInfo*character, const String&costume, const ArrayList<PlayerInfo::Mode>& modeCycle);
		~PlayerInfo();
		
		PlayerInfo& operator=(const PlayerInfo&);
		
		CharacterInfo* getCharacterInfo() const;
		const String& getCostume() const;
		const PlayerInfo::Mode& getPlayerMode() const;
		const ArrayList<PlayerInfo::Mode>& getPlayerModeCycle() const;
		
		void setCharacterInfo(CharacterInfo*);
		void setCostume(const String&);
		void setPlayerMode(const PlayerInfo::Mode&);
		void setPlayerModeCycle(const ArrayList<PlayerInfo::Mode>&modeCycle);
		void cyclePlayerMode();
		void turnPlayerModeOn();
		void turnPlayerModeOff();
		
	private:
		CharacterInfo* character_info;
		String character_costume;
		
		PlayerInfo::Mode mode;
		ArrayList<PlayerInfo::Mode> modeCycle;
		unsigned int modeCycleIndex;
	};
}
