
#include "GroupSmashCharacterSelectMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashCharacterSelectMenu::GroupSmashCharacterSelectMenu(MenuData* menuData, GroupSmashData* groupSmashData)
			: CharacterSelectScreen(menuData, groupSmashData->getRules()),
			groupSmashData(groupSmashData)
		{
			setHeaderbarMode(HEADERBAR_SMALL);
			reloadCharacters();
			reloadPlayers();

			auto assetManager = menuData->getAssetManager();

			double headerbarBottom = 0.866;
			fgl::LayoutRule* headerBarBottomRule = getHeaderbarElement()->getAutoLayoutManager().getRule(fgl::LAYOUTRULE_BOTTOM);
			if(headerBarBottomRule!=nullptr && headerBarBottomRule->valueType==fgl::LAYOUTVALUE_RATIO)
			{
				headerbarBottom = headerBarBottomRule->value;
			}
			
			rulesBar = new RulesBar(assetManager,
											groupSmashData->getRules(),
											groupSmashData->getStockWinCondition(),
											groupSmashData->getTimeLimitWinCondition());
			rulesBar->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.36, fgl::LAYOUTVALUE_RATIO);
			rulesBar->setLayoutRule(fgl::LAYOUTRULE_TOP, 0, fgl::LAYOUTVALUE_RATIO);
			rulesBar->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0, fgl::LAYOUTVALUE_RATIO);
			rulesBar->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, headerbarBottom, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(rulesBar);
			
			addScreen("StageSelect", new GroupSmashStageSelectMenu(menuData, groupSmashData));
		}
		
		GroupSmashCharacterSelectMenu::~GroupSmashCharacterSelectMenu()
		{
			delete rulesBar;
		}
		
		void GroupSmashCharacterSelectMenu::onWillAppear(const fgl::Transition* transition)
		{
			CharacterSelectScreen::onWillAppear(transition);
			Rules* rules = getRules();
			if(rules->getWinCondition() == groupSmashData->getStockWinCondition())
			{
				rulesBar->getLabelElement()->setText("Man Survival Test!");
			}
			else if(rules->getWinCondition() == groupSmashData->getTimeLimitWinCondition())
			{
				rulesBar->getLabelElement()->setText("Minute Survival Test!");
			}
		}
		
		void GroupSmashCharacterSelectMenu::proceedToFight()
		{
			goToScreen("StageSelect");
		}
	}
}
