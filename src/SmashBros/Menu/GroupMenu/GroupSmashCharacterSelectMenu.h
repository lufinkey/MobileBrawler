
#pragma once

#include "../Base/CharacterSelect/CharacterSelectScreen.h"
#include "GroupSmashStageSelectMenu.h"
#include "../MenuData/GroupSmashData.h"
#include "../Elements/ArrowButton.h"
#include "../Elements/RulesBar.h"

namespace SmashBros
{
	namespace Menu
	{
		class GroupSmashCharacterSelectMenu : public CharacterSelectScreen
		{
		private:
			RulesBar* rulesBar;
			StockWinCondition* stockWinCondition;
			TimeLimitWinCondition* timeLimitWinCondition;
			
			GroupSmashStageSelectMenu* groupSmashStageSelectMenu;
			
		public:
			GroupSmashCharacterSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void onWillAppear(const Transition*transition) override;
			
			virtual void proceedToFight() override;
			
		protected:
			virtual void onUpdate(ApplicationData appData) override;
			virtual void onDraw(ApplicationData appData, Graphics graphics) const override;
		};
	}
}
