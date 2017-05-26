
#pragma once

#include "../Base/BaseMenuScreen.hpp"
#include "../MenuData/GroupSmashData.hpp"
#include "GroupSmashCharacterSelectMenu.hpp"
#include "GroupRulesMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class GroupMenu : public BaseMenuScreen
		{
		public:
			explicit GroupMenu(MenuData* menuData);
			virtual ~GroupMenu();
			
		private:
			MenuButton* smashButton;
			MenuButton* specialSmashButton;
			MenuButton* rulesButton;

			GroupSmashData* groupSmashData;
		};
	}
}
