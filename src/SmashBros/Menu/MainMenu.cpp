
#include "MainMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			AssetManager* assetManager = smashData.getMenuData()->getAssetManager();
			
			groupButton = getItem(addItem(RectD(0.03, 0.187, 0.53, 0.687), new Animation(1, assetManager, "buttons/main/group.png")));
			soloButton = getItem(addItem(RectD(0.47, 0.266, 0.97, 0.766), new Animation(1, assetManager, "buttons/main/solo.png")));
			
			backTransition = new FadeColorTransition(Color::BLACK, 0.6);
			
			groupMenu = new GroupMenu(smashData);
			soloMenu = new SoloMenu(smashData);
		}
		
		MainMenu::~MainMenu()
		{
			delete backTransition;
			delete groupMenu;
			delete soloMenu;
		}
		
		void MainMenu::onItemSelect(size_t index)
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
