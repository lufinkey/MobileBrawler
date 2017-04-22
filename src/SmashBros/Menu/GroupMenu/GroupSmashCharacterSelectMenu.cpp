
#include "GroupSmashCharacterSelectMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashCharacterSelectMenu::GroupSmashCharacterSelectMenu(const SmashData& smashData, const GroupSmashData& groupSmashData) : CharacterSelectScreen(smashData, groupSmashData.getRules())
		{
			stockWinCondition = groupSmashData.getStockWinCondition();
			timeLimitWinCondition = groupSmashData.getTimeLimitWinCondition();
			
			setHeaderbarMode(HEADERBAR_SMALL);
			reloadIcons(smashData);
			reloadPlayerPanels(smashData);
			
			double headerbarBottom = 0.866;
			LayoutRule* headerBarBottomRule = getHeaderbarElement()->getAutoLayoutManager().getRule(LAYOUTRULE_BOTTOM);
			if(headerBarBottomRule!=nullptr && headerBarBottomRule->valueType==LAYOUTVALUE_RATIO)
			{
				headerbarBottom = headerBarBottomRule->value;
			}
			
			rulesBar = new RulesBar(smashData.getMenuData()->getAssetManager(),
											groupSmashData.getRules(),
											groupSmashData.getStockWinCondition(),
											groupSmashData.getTimeLimitWinCondition(),
											smashData.getMenuData()->getRulesBarProperties());
			rulesBar->setLayoutRule(LAYOUTRULE_LEFT, 0.36, LAYOUTVALUE_RATIO);
			rulesBar->setLayoutRule(LAYOUTRULE_TOP, 0, LAYOUTVALUE_RATIO);
			rulesBar->setLayoutRule(LAYOUTRULE_RIGHT, 0, LAYOUTVALUE_RATIO);
			rulesBar->setLayoutRule(LAYOUTRULE_BOTTOM, headerbarBottom, LAYOUTVALUE_RATIO);
			getElement()->addChildElement(rulesBar);
			
			groupSmashStageSelectMenu = new GroupSmashStageSelectMenu(smashData, groupSmashData);
		}
		
		GroupSmashCharacterSelectMenu::~GroupSmashCharacterSelectMenu()
		{
			delete rulesBar;
			delete groupSmashStageSelectMenu;
		}
		
		void GroupSmashCharacterSelectMenu::onWillAppear(const Transition*transition)
		{
			Rules* rules = getRules();
			if(rules->getWinCondition() == stockWinCondition)
			{
				rulesBar->getLabelElement()->setText("Man Survival Test!");
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				rulesBar->getLabelElement()->setText("Minute Survival Test!");
			}
		}
		
		void GroupSmashCharacterSelectMenu::proceedToFight()
		{
			getScreenManager()->push(groupSmashStageSelectMenu);
		}
	}
}
