
#pragma once

#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace BrawlerLibrary;
	
	class GroupSmashData
	{
	private:
		StockWinCondition* stockWinCondition;
		TimeLimitWinCondition* timeLimitWinCondition;
		
	public:
		GroupSmashData();
		~GroupSmashData();
		
		StockWinCondition* getStockWinCondition() const;
		TimeLimitWinCondition* getTimeLimitWinCondition() const;
	};
}
