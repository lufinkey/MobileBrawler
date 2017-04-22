
#pragma once

#include "../Base/BaseMenuScreen.hpp"
#include "../Elements/MenuBarValueAdjust.hpp"
#include "../Elements/RulesBar.hpp"
#include "../MenuData/GroupSmashData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class GroupRulesMenu : public BaseMenuScreen
		{
		public:
			GroupRulesMenu(const SmashData& smashData, const GroupSmashData& groupSmashData);
			virtual ~GroupRulesMenu();
			
			virtual void onWillAppear(const Transition* transition) override;
			
		private:
			String getGameModeLabelString(Rules* rules) const;
			unsigned int getGameModeValue(Rules* rules) const;
			WinCondition* getGameModeWinCondition(unsigned int value) const;
			
			Rules* rules;
			StockWinCondition* stockWinCondition;
			TimeLimitWinCondition* timeLimitWinCondition;
			
			MenuBarValueAdjust* gameModeBar;
			RulesBar* gameModeValueBar;
		};
	}
}
