
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
		private:
			RulesBar* rulesBar;
			AutoLayoutManager rulesBarAutoLayoutMgr;
			
			StockWinCondition* stockWinCondition;
			TimeLimitWinCondition* timeLimitWinCondition;
			
			GroupSmashStageSelectMenu* groupSmashStageSelectMenu;
			
		public:
			GroupSmashCharacterSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void onSizeChange(const Vector2d& oldSize, const Vector2d& newSize) override;
			virtual void onWillAppear(const Transition*transition) override;
			
			virtual void proceedToFight() override;
			
		protected:
			virtual void onUpdate(const ApplicationData& appData) override;
			virtual void onDraw(const ApplicationData& appData, Graphics graphics) const override;
		};
	}
}