
#include "MainMenu.h"
#include "../Global.h"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(AssetManager*assetManager) : SmashBros::Menu::BaseMenuScreen(assetManager)
		{
			unsigned int itemIndex = 0;
			itemIndex = addItem(getScreenCoords(0.31f, 0.437f), new Animation(assetManager, 1, "images/menu/buttons/smash.png"));
			getItem(itemIndex)->setScale(0.65f);
			itemIndex = addItem(getScreenCoords(0.745f, 0.516f), new Animation(assetManager, 1, "images/menu/buttons/solo.png"));
			getItem(itemIndex)->setScale(0.65f);
			
			backTransition = new FadeColorTransition(Color::BLACK, 0.6f);
		}
		
		MainMenu::~MainMenu()
		{
			//
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
			}
		}
	}
}
