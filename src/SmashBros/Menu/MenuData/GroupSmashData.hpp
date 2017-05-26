
#pragma once

#include <SmashBros/Game/Rules/Rules.hpp>
#include <SmashBros/Game/Rules/WinCondition/StockWinCondition.hpp>
#include <SmashBros/Game/Rules/WinCondition/TimeLimitWinCondition.hpp>

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
