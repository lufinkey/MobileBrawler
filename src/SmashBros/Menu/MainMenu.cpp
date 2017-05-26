
#include "MainMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(MenuData* menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			auto assetManager = menuData->getAssetManager();

			groupButton = new MenuButton(assetManager, "buttons/main/group.png");
			groupButton->setTapHandler([=]{
				goToScreen("Group");
			});
			groupButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.03, fgl::LAYOUTVALUE_RATIO);
			groupButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.187, fgl::LAYOUTVALUE_RATIO);
			groupButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.47, fgl::LAYOUTVALUE_RATIO);
			groupButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.313, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(groupButton);

			soloButton = new MenuButton(assetManager, "buttons/main/solo.png");
			soloButton->setTapHandler([=]{
				goToScreen("Solo");
			});
			soloButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.47, fgl::LAYOUTVALUE_RATIO);
			soloButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.266, fgl::LAYOUTVALUE_RATIO);
			soloButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.03, fgl::LAYOUTVALUE_RATIO);
			soloButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.234, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(soloButton);
			
			backTransition = new fgl::FadeColorTransition(fgl::Color::BLACK, 0.6);
			getBackButton()->setTapHandler([=]{
				getScreenManager()->pop(backTransition, 2000);
			});
			
			addScreen("Group", new GroupMenu(menuData));
			addScreen("Solo", new SoloMenu(menuData));
		}
		
		MainMenu::~MainMenu()
		{
			delete groupButton;
			delete soloButton;
			delete backTransition;
		}
	}
}
