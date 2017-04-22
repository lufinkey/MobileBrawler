
#pragma once

#include "../Base/CharacterSelect/CharacterSelectScreen.hpp"
#include "GroupSmashStageSelectMenu.hpp"
#include "../MenuData/GroupSmashData.hpp"
#include "../Elements/ArrowButton.hpp"
#include "../Elements/RulesBar.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class GroupSmashCharacterSelectMenu : public CharacterSelectScreen
		{
		public:
			GroupSmashCharacterSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void onWillAppear(const Transition*transition) override;
			
			virtual void proceedToFight() override;

		private:
			RulesBar* rulesBar;
			AutoLayoutManager rulesBarAutoLayoutMgr;

			StockWinCondition* stockWinCondition;
			TimeLimitWinCondition* timeLimitWinCondition;

			GroupSmashStageSelectMenu* groupSmashStageSelectMenu;
		};
	}
}
