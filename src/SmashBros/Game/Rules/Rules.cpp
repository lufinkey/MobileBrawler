
#include "Rules.hpp"

namespace SmashBros
{
	Rules::Rules()
	{
		//
	}
	
	Rules::~Rules()
	{
		//
	}
	
	size_t Rules::getPlayerCount() const
	{
		return players.size();
	}

	void Rules::setPlayerCount(size_t count)
	{
		players.resize(count);
	}
	
	PlayerInfo& Rules::getPlayerInfo(size_t playerIndex)
	{
		return players.get(playerIndex);
	}
	
	const PlayerInfo& Rules::getPlayerInfo(size_t playerIndex) const
	{
		return players.get(playerIndex);
	}
	
	WinCondition* Rules::getWinCondition() const
	{
		return winCondition;
	}
	
	void Rules::setWinCondition(WinCondition* condition)
	{
		winCondition = condition;
	}
}
