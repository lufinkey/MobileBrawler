
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
			
			Vector2f rulesBar_topleft = smashData.getScreenCoords(0.36f, 0);
			Vector2f rulesBar_bottomright = smashData.getScreenCoords(1.0f, 0.162f);
			RectangleF rulesBar_frame = RectangleF(rulesBar_topleft.x, //x
													rulesBar_topleft.y, //y
													rulesBar_bottomright.x-rulesBar_topleft.x, //width
													getHeaderbarElement()->getFrame().height); //height
			rulesBar = new RulesBar(rulesBar_frame.x+(rulesBar_frame.width/2),
									rulesBar_frame.y+(rulesBar_frame.height/2),
									groupSmashData.getRules(),
									groupSmashData.getStockWinCondition(),
									groupSmashData.getTimeLimitWinCondition(),
									smashData.getMenuData()->getAssetManager(),
									smashData.getMenuData()->getRulesBarProperties());
			rulesBar->Actor::scaleToFit(Vector2f(rulesBar_frame.width, rulesBar_frame.height));
			
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
