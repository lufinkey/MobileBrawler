
#include "Rules.h"

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	Rules::Rules()
	{
		//
	}
	
	Rules::~Rules()
	{
		//
	}
	
	unsigned int Rules::getPlayerCount() const
	{
		return (unsigned int)players.size();
	}
	
	PlayerInfo& Rules::getPlayerInfo(unsigned int playerNum)
	{
		return players.get(playerNum-1);
	}
	
	const PlayerInfo& Rules::getPlayerInfo(unsigned int playerNum) const
	{
		return players.get(playerNum-1);
	}
	
	WinCondition* Rules::getWinCondition() const
	{
		return winCondition;
	}
	
	void Rules::setPlayerCount(unsigned int count)
	{
		players.resize(count);
	}
	
	void Rules::setWinCondition(WinCondition*condition)
	{
		winCondition = condition;
	}
}
