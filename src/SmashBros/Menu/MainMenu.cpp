
#include "MainMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MainMenu::MainMenu(const SmashData& smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			auto assetManager = smashData.getMenuData()->getAssetManager();

			groupButton = new MenuButton(assetManager, "buttons/main/group.png");
			groupButton->setTapHandler([=]{
				getScreenManager()->push(groupMenu);
			});
			groupButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.03, fgl::LAYOUTVALUE_RATIO);
			groupButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.187, fgl::LAYOUTVALUE_RATIO);
			groupButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.47, fgl::LAYOUTVALUE_RATIO);
			groupButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.313, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(groupButton);

			soloButton = new MenuButton(assetManager, "buttons/main/solo.png");
			soloButton->setTapHandler([=]{
				getScreenManager()->push(soloMenu);
			});
			soloButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.47, fgl::LAYOUTVALUE_RATIO);
			soloButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.266, fgl::LAYOUTVALUE_RATIO);
			soloButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.03, fgl::LAYOUTVALUE_RATIO);
			soloButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.234, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(soloButton);
			
			backTransition = new FadeColorTransition(Color::BLACK, 0.6);
			getBackButton()->setTapHandler([=]{
				getScreenManager()->pop(backTransition, 2000);
			});
			
			groupMenu = new GroupMenu(smashData);
			soloMenu = new SoloMenu(smashData);
		}
		
		MainMenu::~MainMenu()
		{
			delete groupButton;
			delete soloButton;
			delete backTransition;
			delete groupMenu;
			delete soloMenu;
		}
	}
}
