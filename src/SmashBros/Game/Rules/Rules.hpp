
#pragma once

#include "PlayerInfo.hpp"
#include "WinCondition/WinCondition.hpp"

namespace SmashBros
{
	class Rules
	{
	public:
		Rules();
		~Rules();
		
		size_t getPlayerCount() const;
		void setPlayerCount(size_t count);

		PlayerInfo& getPlayerInfo(size_t playerNum);
		const PlayerInfo& getPlayerInfo(size_t playerNum) const;

		WinCondition* getWinCondition() const;
		void setWinCondition(WinCondition* condition);
		
	private:
		fgl::ArrayList<PlayerInfo> players;
		WinCondition* winCondition;
	};
}
