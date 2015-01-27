
#pragma once

#include "Base/BaseMenuScreen.h"
#include "Elements/MenuBarValueAdjust.h"

namespace SmashBros
{
	namespace Menu
	{
		class GroupRulesMenu : public BaseMenuScreen
		{
		public:
			GroupRulesMenu(const SmashData&smashData);
			virtual ~GroupRulesMenu();
		};
	}
}
