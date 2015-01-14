
#include "MainMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(const MenuData&menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			AssetManager* assetManager = menuData.getAssetManager();
			
			groupButton = getItem(addItem(Global::getScreenCoords(0.31f, 0.437f), new Animation(assetManager, 1, "assets/menu/buttons/group.png")));
			groupButton->scaleToFit(Global::getScreenCoords(0.5f,0.5f));
			soloButton = getItem(addItem(Global::getScreenCoords(0.745f, 0.516f), new Animation(assetManager, 1, "assets/menu/buttons/solo.png")));
			soloButton->scaleToFit(Global::getScreenCoords(0.5f,0.5f));
			
			backTransition = new FadeColorTransition(Color::BLACK, 0.6f);
			
			groupMenu = new GroupMenu(assetManager);
			soloMenu = new SoloMenu(assetManager);
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
