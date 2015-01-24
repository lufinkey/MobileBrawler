
#pragma once

#include "PlayerInfo.h"
#include "WinCondition.h"

namespace BrawlerLibrary
{
	class Rules
	{
	public:
		Rules();
		~Rules();
		
		unsigned int getPlayerCount() const;
		PlayerInfo& getPlayerInfo(unsigned int playerNum);
		const PlayerInfo& getPlayerInfo(unsigned int playerNum) const;

		void setPlayerCount(unsigned int count);
		
	private:
		ArrayList<PlayerInfo> players;
		WinCondition* winCondition;
	};
}
