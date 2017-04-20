
#include "GroupSmashStageSelectMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashStageSelectMenu::GroupSmashStageSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData) : StageSelectScreen(smashData, groupSmashData.getRules())
		{
			reloadIcons(smashData);
			reloadPreview(smashData);
		}
	}
}
