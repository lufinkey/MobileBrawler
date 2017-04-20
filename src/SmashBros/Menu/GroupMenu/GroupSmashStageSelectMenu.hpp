
#pragma once

#include "../Base/StageSelect/StageSelectScreen.hpp"
#include "../MenuData/GroupSmashData.hpp"

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
