
#include "GroupSmashData.h"

namespace SmashBros
{
	GroupSmashData::GroupSmashData()
	{
		stockWinCondition = new StockWinCondition();
		timeLimitWinCondition = new TimeLimitWinCondition();
	}
	
	GroupSmashData::~GroupSmashData()
	{
		delete stockWinCondition;
		delete timeLimitWinCondition;
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
