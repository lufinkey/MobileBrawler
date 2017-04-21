
#include "GroupMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		GroupMenu::GroupMenu(const SmashData& smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			auto assetManager = smashData.getMenuData()->getAssetManager();
			
			smashButton = new MenuButton(assetManager, "buttons/group/smash.png");
			smashButton->setTapHandler([=]{
				getScreenManager()->push(smashMenu);
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
				getScreenManager()->push(rulesMenu);
			});
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.275, fgl::LAYOUTVALUE_RATIO);
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.6, fgl::LAYOUTVALUE_RATIO);
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.275, fgl::LAYOUTVALUE_RATIO);
			rulesButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.1, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(rulesButton);
			
			groupSmashData = new GroupSmashData();
			//TODO make the character select screen be loaded when the screen fades to black
			//(create an intermediate screen for while it's loading)
			smashMenu = new GroupSmashCharacterSelectMenu(smashData, *groupSmashData);
			rulesMenu = new GroupRulesMenu(smashData, *groupSmashData);
		}
		
		GroupMenu::~GroupMenu()
		{
			delete smashButton;
			delete specialSmashButton;
			delete rulesButton;
			
			delete smashMenu;
			delete groupSmashData;
		}
	}
}
