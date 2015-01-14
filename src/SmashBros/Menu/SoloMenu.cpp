
#include "SoloMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		SoloMenu::SoloMenu(const MenuData&menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			trainingButton = getItem(addItem(Global::getScreenCoords(0.5f, 0.5f), new Animation(menuData.getAssetManager(), 1, "assets/menu/buttons/training.png")));
			trainingButton->scaleToFit(Global::getScreenCoords(0.8f,0.8f));
		}
		
		SoloMenu::~SoloMenu()
		{
			//
		}
			
		void SoloMenu::onItemSelect(unsigned int index)
		{
			BaseMenuScreen::onItemSelect(index);
			ScreenManager* screenMgr = getScreenManager();
			if(screenMgr != nullptr)
			{
				Actor* item = getItem(index);
				if(item == trainingButton)
				{
					//TODO go to training menu
				}
			}
		}
	}
}
