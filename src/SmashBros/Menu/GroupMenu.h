
#pragma once

#include "BaseMenuScreen.h"

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
			
		public:
			GroupMenu(const MenuData&menuData);
			virtual ~GroupMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
