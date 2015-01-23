
#include "MainMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			AssetManager* assetManager = smashData.getMenuData().getAssetManager();
			
			groupButton = getItem(addItem(smashData.getScreenCoords(0.28f, 0.437f), new Animation(1, assetManager, "buttons/main/group.png")));
			groupButton->scaleToFit(smashData.getScreenCoords(0.5f,0.5f));
			soloButton = getItem(addItem(smashData.getScreenCoords(0.72f, 0.516f), new Animation(1, assetManager, "buttons/main/solo.png")));
			soloButton->scaleToFit(smashData.getScreenCoords(0.5f,0.5f));
			
			backTransition = new FadeColorTransition(Color::BLACK, 0.6f);
			
			groupMenu = new GroupMenu(smashData);
			soloMenu = new SoloMenu(smashData);
		}
		
		MainMenu::~MainMenu()
		{
			delete backTransition;
			delete groupMenu;
			delete soloMenu;
		}
		
		void MainMenu::onItemSelect(unsigned int index)
		{
			Actor* item = getItem(index);
			ScreenManager* screenMgr = getScreenManager();
			if(screenMgr!=nullptr)
			{
				if(item == getBackButton())
				{
					screenMgr->pop(backTransition, 2000);
				}
				else if(item == groupButton)
				{
					screenMgr->push(groupMenu);
				}
				else if(item == soloButton)
				{
					screenMgr->push(soloMenu);
				}
			}
		}
	}
}
