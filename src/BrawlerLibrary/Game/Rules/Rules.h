
#pragma once

#include "PlayerInfo.h"
#include "WinCondition/WinCondition.h"

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
		WinCondition* getWinCondition() const;

		void setPlayerCount(unsigned int count);
		void setWinCondition(WinCondition*);
		
	private:
		ArrayList<PlayerInfo> players;
		WinCondition* winCondition;
	};
}
