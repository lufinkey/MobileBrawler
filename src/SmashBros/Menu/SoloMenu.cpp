
#include "SoloMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		SoloMenu::SoloMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			trainingButton = getItem(addItem(smashData.getScreenCoords(0.5f, 0.5f), new Animation(smashData.getMenuData().getAssetManager(), 1, "buttons/solo/training.png")));
			trainingButton->scaleToFit(smashData.getScreenCoords(0.8f,0.8f));
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
