
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
			GroupSmashCharacterSelectMenu(MenuData* menuData, GroupSmashData* groupSmashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void onWillAppear(const fgl::Transition* transition) override;
			
			virtual void proceedToFight() override;

		private:
			GroupSmashData* groupSmashData;

			RulesBar* rulesBar;
		};
	}
}
