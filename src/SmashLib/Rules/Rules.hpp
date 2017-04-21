
#pragma once

#include "PlayerInfo.hpp"
#include "WinCondition/WinCondition.hpp"

namespace SmashLib
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
		fgl::ArrayList<PlayerInfo> players;
		WinCondition* winCondition;
	};
}