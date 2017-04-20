
#pragma once

#include <SmashLib/SmashLib.hpp>

using namespace SmashLib;

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
