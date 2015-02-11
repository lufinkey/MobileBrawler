
#include "MainMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			AssetManager* assetManager = smashData.getMenuData()->getAssetManager();
			
			groupButton = getItem(addItem(RectF(0.03f, 0.187f, 0.53f, 0.687f), new Animation(1, assetManager, "buttons/main/group.png")));
			soloButton = getItem(addItem(RectF(0.47f, 0.266f, 0.97f, 0.766f), new Animation(1, assetManager, "buttons/main/solo.png")));
			
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
