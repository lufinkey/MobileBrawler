
#pragma once

#include "Base/BaseMenuScreen.h"
#include "GroupSmashCharacterSelectMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		class GroupMenu : public BaseMenuScreen
		{
		private:
			Actor* smashButton;
			Actor* specialSmashButton;
			Actor* rulesButton;
			
			Rules* smashRules;
			
			GroupSmashCharacterSelectMenu* smashMenu;
			
		public:
			GroupMenu(const SmashData&smashData);
			virtual ~GroupMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
