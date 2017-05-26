
#include "GroupMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		GroupMenu::GroupMenu(MenuData* menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			auto assetManager = menuData->getAssetManager();
			
			smashButton = new MenuButton(assetManager, "buttons/group/smash.png");
			smashButton->setTapHandler([=]{
				goToScreen("Smash");
			});
			smashButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.05, fgl::LAYOUTVALUE_RATIO);
			smashButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.2, fgl::LAYOUTVALUE_RATIO);
			smashButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.45, fgl::LAYOUTVALUE_RATIO);
			smashButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.4, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(smashButton);
			
			specialSmashButton = new MenuButton(assetManager, "buttons/group/specialsmash.png");
			specialSmashButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.45, fgl::LAYOUTVALUE_RATIO);
			specialSmashButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.25, fgl::LAYOUTVALUE_RATIO);
			specialSmashButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.5, fgl::LAYOUTVALUE_RATIO);
			specialSmashButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.5, fgl::LAYOUTVALUE_RATIO);
			//getElement()->addChildElement(specialSmashButton);
			
			rulesButton = new MenuButton(assetManager, "buttons/group/rules.png");
			rulesButton->setTapHandler([=]{
				goToScreen("Rules");
			});
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.275, fgl::LAYOUTVALUE_RATIO);
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.6, fgl::LAYOUTVALUE_RATIO);
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.275, fgl::LAYOUTVALUE_RATIO);
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.1, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(rulesButton);

			groupSmashData = new GroupSmashData();

			addScreen("Smash", new GroupSmashCharacterSelectMenu(menuData, groupSmashData));
			addScreen("Rules", new GroupRulesMenu(menuData, groupSmashData));
		}
		
		GroupMenu::~GroupMenu()
		{
			delete smashButton;
			delete specialSmashButton;
			delete rulesButton;

			delete groupSmashData;
		}
	}
}
