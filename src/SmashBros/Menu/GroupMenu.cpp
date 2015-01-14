
#include "GroupMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupMenu::GroupMenu(AssetManager*assetManager) : SmashBros::Menu::BaseMenuScreen(assetManager)
		{
			smashButton = getItem(addItem(getScreenCoords(0.3f, 0.45f), new Animation(assetManager, 1, "assets/menu/buttons/smash.png")));
			smashButton->scaleToFit(getScreenCoords(0.5f, 0.5f));
			specialSmashButton = nullptr;//specialSmashButton = getItem(addItem(getScreenCoords(0.7f,0.5f), new Animation(assetManager, 1, "assets/menu/buttons/specialsmash.png"));
			//specialSmashButton->scaleToFit(getScreenCoords(0.5f, 0.5f));
			rulesButton = getItem(addItem(getScreenCoords(0.5f, 0.75f), new Animation(assetManager, 1, "assets/menu/buttons/rules.png")));
			rulesButton->scaleToFit(getScreenCoords(0.5f, 0.5f));
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
