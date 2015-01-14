
#include "GroupMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupMenu::GroupMenu(const MenuData&menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			smashButton = getItem(addItem(Global::getScreenCoords(0.3f, 0.45f), new Animation(menuData.getAssetManager(), 1, "assets/menu/buttons/smash.png")));
			smashButton->scaleToFit(Global::getScreenCoords(0.5f, 0.5f));
			specialSmashButton = nullptr;//specialSmashButton = getItem(addItem(Global::getScreenCoords(0.7f,0.5f), new Animation(menuData.getAssetManager(), 1, "assets/menu/buttons/specialsmash.png"));
			//specialSmashButton->scaleToFit(getScreenCoords(0.5f, 0.5f));
			rulesButton = getItem(addItem(Global::getScreenCoords(0.5f, 0.75f), new Animation(menuData.getAssetManager(), 1, "assets/menu/buttons/rules.png")));
			rulesButton->scaleToFit(Global::getScreenCoords(0.5f, 0.5f));
		}
		
		GroupMenu::~GroupMenu()
		{
			//
		}
		
		void GroupMenu::onItemSelect(unsigned int index)
		{
			BaseMenuScreen::onItemSelect(index);
			ScreenManager* screenMgr = getScreenManager();
			if(screenMgr != nullptr)
			{
				Actor* item = getItem(index);
				if(item == smashButton)
				{
					//
				}
				else if(item == specialSmashButton)
				{
					//
				}
				else if(item == rulesButton)
				{
					//
				}
			}
		}
	}
}
