
#include "GroupMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupMenu::GroupMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			smashButton = getItem(addItem(smashData.getScreenCoords(0.3f, 0.45f), new Animation(smashData.getMenuData().getAssetManager(), 1, "buttons/group/smash.png")));
			smashButton->scaleToFit(smashData.getScreenCoords(0.5f, 0.5f));
			specialSmashButton = nullptr;//specialSmashButton = getItem(addItem(smashData.getScreenCoords(0.7f,0.5f), new Animation(smashData.getMenuData().getAssetManager(), 1, "buttons/group/specialsmash.png"));
			//specialSmashButton->scaleToFit(smashData.getScreenCoords(0.5f, 0.5f));
			rulesButton = getItem(addItem(smashData.getScreenCoords(0.5f, 0.75f), new Animation(smashData.getMenuData().getAssetManager(), 1, "buttons/group/rules.png")));
			rulesButton->scaleToFit(smashData.getScreenCoords(0.5f, 0.5f));
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
