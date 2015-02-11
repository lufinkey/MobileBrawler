
#include "SoloMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		SoloMenu::SoloMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			trainingButton = getItem(addItem(RectF(0.1f, 0.2f, 0.9f, 0.8f), new Animation(1, smashData.getMenuData()->getAssetManager(), "buttons/solo/training.png")));
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
