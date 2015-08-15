
#include "SoloMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		SoloMenu::SoloMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			trainingButton = getItem(addItem(RectD(0.1, 0.2, 0.9, 0.8), new Animation(1, smashData.getMenuData()->getAssetManager(), "buttons/solo/training.png")));
		}
		
		SoloMenu::~SoloMenu()
		{
			//
		}
			
		void SoloMenu::onItemSelect(size_t index)
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
