
#pragma once

#include <BrawlerLibrary/BrawlerLibrary.h>

using namespace BrawlerLibrary;

namespace SmashBros
{
	class GroupSmashData
	{
	private:
		Rules* rules;
		StockWinCondition* stockWinCondition;
		TimeLimitWinCondition* timeLimitWinCondition;
		
	public:
		GroupSmashData();
		~GroupSmashData();
		
		Rules* getRules() const;
		StockWinCondition* getStockWinCondition() const;
		TimeLimitWinCondition* getTimeLimitWinCondition() const;
	};
}
