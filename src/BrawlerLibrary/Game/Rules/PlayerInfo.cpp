
#include "PlayerInfo.h"

namespace BrawlerLibrary
{
	using namespace fgl;
	
	PlayerInfo::PlayerInfo()
	{
		character_info = nullptr;
		
		mode = PlayerInfo::MODE_OFF;
		modeCycle.add(PlayerInfo::MODE_OFF);
		modeCycle.add(PlayerInfo::MODE_HUMAN);
		modeCycle.add(PlayerInfo::MODE_CPU);
		modeCycleIndex = 0;
	}
	
	PlayerInfo::PlayerInfo(const PlayerInfo&info)
	{
		character_info = info.character_info;
		character_costume = info.character_costume;
		
		mode = info.mode;
		modeCycle = info.modeCycle;
		modeCycleIndex = info.modeCycleIndex;
	}
	
	PlayerInfo::PlayerInfo(CharacterInfo*character, const String&costume, const ArrayList<PlayerInfo::Mode>& modecycle)
	{
		character_info = character;
		character_costume = costume;
		modeCycle = modecycle;
		modeCycleIndex = 0;
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
	
	PlayerInfo& PlayerInfo::operator=(const PlayerInfo&info)
	{
		character_info = info.character_info;
		character_costume = info.character_costume;
		
		mode = info.mode;
		modeCycle = info.modeCycle;
		modeCycleIndex = info.modeCycleIndex;

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
	
	const PlayerInfo::Mode& PlayerInfo::getPlayerMode() const
	{
		return mode;
	}
	
	const ArrayList<PlayerInfo::Mode>& PlayerInfo::getPlayerModeCycle() const
	{
		return modeCycle;
	}
	
	void PlayerInfo::setCharacterInfo(CharacterInfo*info)
	{
		character_info = info;
	}
	
	void PlayerInfo::setCostume(const String&costume)
	{
		character_costume = costume;
	}
	
	void PlayerInfo::setPlayerMode(const PlayerInfo::Mode&playermode)
	{
		mode = playermode;
	}
	
	void PlayerInfo::setPlayerModeCycle(const ArrayList<PlayerInfo::Mode>& modecycle)
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
