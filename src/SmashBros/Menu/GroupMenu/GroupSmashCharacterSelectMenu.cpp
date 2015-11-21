
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
			
			RectangleD frame = getFrame();
			
			double headerbarBottom = 0.134*1.1;
			LayoutRule* headerBarBottomRule = getHeaderbarElement()->getAutoLayoutManager().getRule(LAYOUTRULE_BOTTOM);
			if(headerBarBottomRule!=nullptr && headerBarBottomRule->valueType==LAYOUTVALUE_RATIO)
			{
				headerbarBottom = headerBarBottomRule->value*1.1;
			}
			
			rulesBar = new RulesBar(groupSmashData.getRules(),
									groupSmashData.getStockWinCondition(),
									groupSmashData.getTimeLimitWinCondition(),
									smashData.getMenuData()->getAssetManager(),
									smashData.getMenuData()->getRulesBarProperties());
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.36, LAYOUTVALUE_RATIO);
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_TOP, 0, LAYOUTVALUE_RATIO);
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 1.0, LAYOUTVALUE_RATIO);
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, headerbarBottom, LAYOUTVALUE_RATIO);
			rulesBar->scaleToFit(rulesBarAutoLayoutMgr.calculateFrame(rulesBar->getFrame(), frame));
			
			groupSmashStageSelectMenu = new GroupSmashStageSelectMenu(smashData, groupSmashData);
		}
		
		GroupSmashCharacterSelectMenu::~GroupSmashCharacterSelectMenu()
		{
			delete rulesBar;
			delete groupSmashStageSelectMenu;
		}
		
		void GroupSmashCharacterSelectMenu::onFrameChange(const RectangleD& oldFrame, const RectangleD& newFrame)
		{
			CharacterSelectScreen::onFrameChange(oldFrame, newFrame);
			RectangleD frame = getFrame();
			rulesBar->scaleToFit(rulesBarAutoLayoutMgr.calculateFrame(rulesBar->getFrame(), frame));
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
