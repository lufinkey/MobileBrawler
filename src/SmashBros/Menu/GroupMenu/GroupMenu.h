
#pragma once

#include "../Base/BaseMenuScreen.h"
#include "../MenuData/GroupSmashData.h"
#include "GroupSmashCharacterSelectMenu.h"
#include "GroupRulesMenu.h"

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
			
			GroupSmashData* groupSmashData;
			
			GroupSmashCharacterSelectMenu* smashMenu;
			GroupRulesMenu* rulesMenu;
			
		public:
			explicit GroupMenu(const SmashData&smashData);
			virtual ~GroupMenu();
			
			virtual void onItemSelect(size_t index) override;
		};
	}
}
