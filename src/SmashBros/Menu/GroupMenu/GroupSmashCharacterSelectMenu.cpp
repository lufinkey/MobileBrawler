
#include "GroupSmashCharacterSelectMenu.hpp"

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
			
			Vector2d size = getSize();
			
			double headerbarBottom = 0.866;
			LayoutRule* headerBarBottomRule = getHeaderbarElement()->getAutoLayoutManager().getRule(LAYOUTRULE_BOTTOM);
			if(headerBarBottomRule!=nullptr && headerBarBottomRule->valueType==LAYOUTVALUE_RATIO)
			{
				headerbarBottom = headerBarBottomRule->value;
			}
			
			rulesBar = new RulesBar(groupSmashData.getRules(),
									groupSmashData.getStockWinCondition(),
									groupSmashData.getTimeLimitWinCondition(),
									smashData.getMenuData()->getAssetManager(),
									smashData.getMenuData()->getRulesBarProperties());
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.36, LAYOUTVALUE_RATIO);
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_TOP, 0, LAYOUTVALUE_RATIO);
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0, LAYOUTVALUE_RATIO);
			rulesBarAutoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, headerbarBottom, LAYOUTVALUE_RATIO);
			rulesBar->scaleToFit(rulesBarAutoLayoutMgr.calculateFrame(rulesBar->getFrame(), RectangleD(0,0,size.x,size.y)));
			
			groupSmashStageSelectMenu = new GroupSmashStageSelectMenu(smashData, groupSmashData);
		}
		
		GroupSmashCharacterSelectMenu::~GroupSmashCharacterSelectMenu()
		{
			delete rulesBar;
			delete groupSmashStageSelectMenu;
		}
		
		void GroupSmashCharacterSelectMenu::onSizeChange(const Vector2d& oldSize, const Vector2d& newSize)
		{
			CharacterSelectScreen::onSizeChange(oldSize, newSize);
			Vector2d size = getSize();
			rulesBar->scaleToFit(rulesBarAutoLayoutMgr.calculateFrame(rulesBar->getFrame(), RectangleD(0,0,size.x,size.y)));
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
		
		void GroupSmashCharacterSelectMenu::onUpdate(const ApplicationData& appData)
		{
			CharacterSelectScreen::onUpdate(appData);
			rulesBar->update(appData);
		}
		
		void GroupSmashCharacterSelectMenu::onDraw(const ApplicationData& appData, Graphics graphics) const
		{
			CharacterSelectScreen::onDraw(appData, graphics);
			rulesBar->draw(appData, graphics);
		}
	}
}
