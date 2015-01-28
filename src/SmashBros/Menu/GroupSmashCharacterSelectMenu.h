
#pragma once

#include "Base/CharacterSelect/CharacterSelectScreen.h"
#include "Elements/ArrowButton.h"
#include "Elements/RulesBar.h"
#include "MenuData/GroupSmashData.h"

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
			
		public:
			GroupSmashCharacterSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void onWillAppear(const Transition*transition) override;
			
			virtual void onUpdate(ApplicationData appData) override;
			virtual void onDraw(ApplicationData appData, Graphics graphics) const override;
		};
	}
}
