
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "../Loader/CharacterInfo.hpp"

namespace SmashLib
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
		PlayerInfo(CharacterInfo*character, const fgl::String&costume, const fgl::ArrayList<PlayerInfo::Mode>& modeCycle);
		~PlayerInfo();
		
		PlayerInfo& operator=(const PlayerInfo&);
		
		CharacterInfo* getCharacterInfo() const;
		const fgl::String& getCostume() const;
		const PlayerInfo::Mode& getPlayerMode() const;
		const fgl::ArrayList<PlayerInfo::Mode>& getPlayerModeCycle() const;
		
		void setCharacterInfo(CharacterInfo*);
		void setCostume(const fgl::String&);
		void setPlayerMode(const PlayerInfo::Mode&);
		void setPlayerModeCycle(const fgl::ArrayList<PlayerInfo::Mode>&modeCycle);
		void cyclePlayerMode();
		void turnPlayerModeOn();
		void turnPlayerModeOff();
		
	private:
		CharacterInfo* character_info;
		fgl::String character_costume;
		
		PlayerInfo::Mode mode;
		fgl::ArrayList<PlayerInfo::Mode> modeCycle;
		unsigned int modeCycleIndex;
	};
}
