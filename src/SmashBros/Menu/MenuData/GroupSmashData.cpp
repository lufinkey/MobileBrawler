
#include "GroupSmashData.h"

namespace SmashBros
{
	GroupSmashData::GroupSmashData()
	{
		stockWinCondition = new StockWinCondition();
		timeLimitWinCondition = new TimeLimitWinCondition();
		rules = new Rules();
		rules->setPlayerCount(4);
		rules->setWinCondition(stockWinCondition);
	}
	
	GroupSmashData::~GroupSmashData()
	{
		delete rules;
		delete stockWinCondition;
		delete timeLimitWinCondition;
	}
	
	Rules* GroupSmashData::getRules() const
	{
		return rules;
	}
	
	StockWinCondition* GroupSmashData::getStockWinCondition() const
	{
		return stockWinCondition;
	}
	
	TimeLimitWinCondition* GroupSmashData::getTimeLimitWinCondition() const
	{
		return timeLimitWinCondition;
	}
}
