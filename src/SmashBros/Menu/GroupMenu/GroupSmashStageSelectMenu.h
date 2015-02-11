
#pragma once

#include "../Base/StageSelect/StageSelectScreen.h"
#include "../MenuData/GroupSmashData.h"

namespace SmashBros
{
	namespace Menu
	{
		class GroupSmashStageSelectMenu : public StageSelectScreen
		{
		public:
			GroupSmashStageSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
		};
	}
}
