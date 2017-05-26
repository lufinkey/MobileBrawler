
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include <SmashBros/Module/CharacterLoader.hpp>

namespace SmashBros
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
		PlayerInfo(const fgl::String& characterIdentifier, const fgl::String& costume, const fgl::ArrayList<PlayerInfo::Mode>& modeCycle);
		~PlayerInfo();
		
		const fgl::String& getCharacterIdentifier() const;
		const fgl::String& getCostume() const;
		const PlayerInfo::Mode& getPlayerMode() const;
		const fgl::ArrayList<PlayerInfo::Mode>& getPlayerModeCycle() const;
		
		void setCharacterIdentifier(const fgl::String& identifier);
		void setCostume(const fgl::String&);
		void setPlayerMode(const PlayerInfo::Mode&);
		void setPlayerModeCycle(const fgl::ArrayList<PlayerInfo::Mode>&modeCycle);
		void cyclePlayerMode();
		void turnPlayerModeOn();
		void turnPlayerModeOff();
		
	private:
		fgl::String characterIdentifier;
		fgl::String characterCostume;
		
		PlayerInfo::Mode mode;
		fgl::ArrayList<PlayerInfo::Mode> modeCycle;
		size_t modeCycleIndex;
	};
}
