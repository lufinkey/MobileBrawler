
#include "PlayerInfo.hpp"

namespace SmashBros
{
	PlayerInfo::PlayerInfo()
		: mode(MODE_OFF),
		modeCycle({MODE_OFF, MODE_HUMAN, MODE_CPU}),
		modeCycleIndex(0)
	{
		//
	}
	
	PlayerInfo::PlayerInfo(const fgl::String& characterIdentifier, const fgl::String& costume, const fgl::ArrayList<PlayerInfo::Mode>& modeCycle)
		: characterIdentifier(characterIdentifier),
		characterCostume(costume),
		modeCycle(modeCycle),
		modeCycleIndex(0)
	{
		if(modeCycle.size() > 0)
		{
			mode = modeCycle.get(0);
		}
		else
		{
			mode = PlayerInfo::MODE_OFF;
		}
	}
	
	PlayerInfo::~PlayerInfo()
	{
		//
	}
	
	const fgl::String& PlayerInfo::getCharacterIdentifier() const
	{
		return characterIdentifier;
	}
	
	const fgl::String& PlayerInfo::getCostume() const
	{
		return characterCostume;
	}
	
	const PlayerInfo::Mode& PlayerInfo::getPlayerMode() const
	{
		return mode;
	}
	
	const fgl::ArrayList<PlayerInfo::Mode>& PlayerInfo::getPlayerModeCycle() const
	{
		return modeCycle;
	}
	
	void PlayerInfo::setCharacterIdentifier(const fgl::String& identifier)
	{
		characterIdentifier = identifier;
	}
	
	void PlayerInfo::setCostume(const fgl::String& costume)
	{
		characterCostume = costume;
	}
	
	void PlayerInfo::setPlayerMode(const PlayerInfo::Mode& playermode)
	{
		mode = playermode;
	}
	
	void PlayerInfo::setPlayerModeCycle(const fgl::ArrayList<PlayerInfo::Mode>& modecycle)
	{
		modeCycle = modecycle;
	}
	
	void PlayerInfo::cyclePlayerMode()
	{
		if(modeCycleIndex < modeCycle.size())
		{
			PlayerInfo::Mode newMode = modeCycle.get(modeCycleIndex);
			if(mode != newMode)
			{
				mode = newMode;
				return;
			}
		}

		modeCycleIndex++;
		if(modeCycleIndex >= modeCycle.size())
		{
			modeCycleIndex = 0;
		}
		
		if(modeCycle.size() == 0)
		{
			mode = PlayerInfo::MODE_OFF;
		}
		else
		{
			mode = modeCycle.get(modeCycleIndex);
		}
	}
	
	void PlayerInfo::turnPlayerModeOn()
	{
		if(mode == PlayerInfo::MODE_OFF)
		{
			for(unsigned int i=0; i<modeCycle.size(); i++)
			{
				cyclePlayerMode();
				if(mode != PlayerInfo::MODE_OFF)
				{
					return;
				}
			}
		}
	}
	
	void PlayerInfo::turnPlayerModeOff()
	{
		if(mode != PlayerInfo::MODE_OFF)
		{
			mode = PlayerInfo::MODE_OFF;
		}
	}
}
