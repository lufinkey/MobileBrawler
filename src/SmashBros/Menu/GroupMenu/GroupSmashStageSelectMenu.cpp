
#include "GroupSmashStageSelectMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashStageSelectMenu::GroupSmashStageSelectMenu(MenuData* menuData, GroupSmashData* groupSmashData) : StageSelectScreen(menuData, groupSmashData->getRules())
		{
			reloadIcons();
		}
	}
}
