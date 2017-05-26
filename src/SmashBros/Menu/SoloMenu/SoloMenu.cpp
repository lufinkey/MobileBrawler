
#include "SoloMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		SoloMenu::SoloMenu(MenuData* menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			trainingButton = new MenuButton(menuData->getAssetManager(), "buttons/solo/training.png");
			trainingButton->setTapHandler([] {
				//TODO go to training screen
			});
			trainingButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.1, fgl::LAYOUTVALUE_RATIO);
			trainingButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.2, fgl::LAYOUTVALUE_RATIO);
			trainingButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.1, fgl::LAYOUTVALUE_RATIO);
			trainingButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.2, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(trainingButton);
		}
		
		SoloMenu::~SoloMenu()
		{
			delete trainingButton;
		}
	}
}
