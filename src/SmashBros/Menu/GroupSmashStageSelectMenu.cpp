
#include "GroupSmashStageSelectMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashStageSelectMenu::GroupSmashStageSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData) : StageSelectScreen(smashData, groupSmashData.getRules())
		{
			reloadIcons(smashData);
			reloadPreviews(smashData);
		}
	}
}
