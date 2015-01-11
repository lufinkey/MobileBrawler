
#include "SmashBrosMenuScreen.h"

#pragma once

namespace SmashBros
{
	namespace Menu
	{
		class MainMenu : SmashBrosMenuScreen
		{
		public:
			MainMenu();
			virtual ~MainMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
