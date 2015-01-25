
#pragma once

#include "Base/CharacterSelect/CharacterSelectScreen.h"
#include "Elements/ArrowButton.h"

namespace SmashBros
{
	namespace Menu
	{
		class GroupSmashCharacterSelectMenu : public CharacterSelectScreen
		{
		public:
			GroupSmashCharacterSelectMenu(const SmashData&smashData);
			virtual ~GroupSmashCharacterSelectMenu();
			
			virtual void updateItems(ApplicationData appData) override;
			virtual void drawItems(ApplicationData appData, Graphics graphics) const override;
		};
	}
}
