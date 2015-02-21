
#include "GroupSmashCharacterSelectMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashCharacterSelectMenu::GroupSmashCharacterSelectMenu(const SmashData&smashData, const GroupSmashData&groupSmashData) : CharacterSelectScreen(smashData, groupSmashData.getRules())
		{
			stockWinCondition = groupSmashData.getStockWinCondition();
			timeLimitWinCondition = groupSmashData.getTimeLimitWinCondition();
			
			setHeaderbarMode(HEADERBAR_SMALL);
			reloadIcons(smashData);
			reloadPlayerPanels(smashData);
			
			double headerbarBottom = getElement()->getAutoLayout().get(getHeaderbarElement()).bottom;
			
			rulesBar = new RulesBar(groupSmashData.getRules(),
									groupSmashData.getStockWinCondition(),
									groupSmashData.getTimeLimitWinCondition(),
									smashData.getMenuData()->getAssetManager(),
									smashData.getMenuData()->getRulesBarProperties());
			getElement()->getAutoLayout().add(RectD(0.36,0,1.0,headerbarBottom), rulesBar);
			
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
				rulesBar->setValueLabel((String)"" + stockWinCondition->getStock());
				rulesBar->setLabel("Man Survival Test!");
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				rulesBar->setValueLabel((String)"" + timeLimitWinCondition->getTimeLimit());
				rulesBar->setLabel("Minute Survival Test!");
			}
		}
		
		void GroupSmashCharacterSelectMenu::proceedToFight()
		{
			getScreenManager()->push(groupSmashStageSelectMenu);
		}
		
		void GroupSmashCharacterSelectMenu::onUpdate(ApplicationData appData)
		{
			CharacterSelectScreen::onUpdate(appData);
			rulesBar->update(appData);
		}
		
		void GroupSmashCharacterSelectMenu::onDraw(ApplicationData appData, Graphics graphics) const
		{
			CharacterSelectScreen::onDraw(appData, graphics);
			rulesBar->draw(appData, graphics);
		}
	}
}
