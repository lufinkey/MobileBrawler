
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
			
		public:
			GroupSmashCharacterSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void updateItems(ApplicationData appData) override;
			virtual void drawItems(ApplicationData appData, Graphics graphics) const override;
		};
	}
}
