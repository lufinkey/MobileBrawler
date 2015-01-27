
#include "GroupRulesMenu.h"

namespace SmashBros
{
	namespace Menu
	{
#define GAMEMODE_ERROR 0U
#define GAMEMODE_STOCK 1U
#define GAMEMODE_TIME 2U

		GroupRulesMenu::GroupRulesMenu(const SmashData&smashData, const GroupSmashData&groupSmashData) : BaseMenuScreen(smashData)
		{
			listener = new MenuBarListener(this);
			rules = groupSmashData.getRules();
			stockWinCondition = groupSmashData.getStockWinCondition();
			timeLimitWinCondition = groupSmashData.getTimeLimitWinCondition();
			
			Vector2f gameTypePos = smashData.getScreenCoords(0.5f, 0.2f);
			gameMode = getGameModeValue(rules);
			gameModeBar = new MenuBarValueAdjust(gameTypePos.x, gameTypePos.y, "Rules",
													getGameModeString(rules),
													&gameMode,
													GAMEMODE_STOCK, GAMEMODE_TIME, 1,
													smashData.getMenuData()->getAssetManager(),
													smashData.getMenuData()->getMenuBarProperties());
			gameModeBar->setEventListener(listener);
			
			Vector2f gameModeValBarPos = smashData.getScreenCoords(0.5f, 0.4f);
			gameModeValueBar = new RulesBar(gameModeValBarPos.x, gameModeValBarPos.y, rules, stockWinCondition, timeLimitWinCondition,
											smashData.getMenuData()->getAssetManager(),
											smashData.getMenuData()->getMenuBarProperties());
			gameModeValueBar->changeAnimation("MenuBar", Animation::FORWARD);
			gameModeValueBar->setLabel(getGameModeLabelString(rules));
		}
		
		GroupRulesMenu::~GroupRulesMenu()
		{
			delete gameModeBar;
			delete listener;
		}
		
		void GroupRulesMenu::onWillAppear(const Transition*transition)
		{
			gameModeBar->setValueLabel(getGameModeString(rules));
		}
		
		void GroupRulesMenu::update(ApplicationData appData)
		{
			BaseMenuScreen::update(appData);
			gameModeBar->update(appData);
			gameModeValueBar->update(appData);
		}
		
		void GroupRulesMenu::draw(ApplicationData appData, Graphics graphics) const
		{
			BaseMenuScreen::draw(appData, graphics);
			gameModeBar->draw(appData, graphics);
			gameModeValueBar->draw(appData, graphics);
		}
		
		String GroupRulesMenu::getGameModeString(Rules*rules) const
		{
			if(rules->getWinCondition() == stockWinCondition)
			{
				return "Stock";
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				return "Time";
			}
			return "Error";
		}
		
		String GroupRulesMenu::getGameModeLabelString(Rules*rules) const
		{
			if(rules->getWinCondition() == stockWinCondition)
			{
				return "Stock";
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				return "Time Limit";
			}
			return "Error";
		}
		
		unsigned int GroupRulesMenu::getGameModeValue(Rules*rules) const
		{
			if(rules->getWinCondition() == stockWinCondition)
			{
				return GAMEMODE_STOCK;
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				return GAMEMODE_TIME;
			}
			return GAMEMODE_ERROR;
		}
		
		WinCondition* GroupRulesMenu::getGameModeWinCondition(unsigned int value) const
		{
			switch(value)
			{
				case GAMEMODE_STOCK:
				return stockWinCondition;
				
				case GAMEMODE_TIME:
				return timeLimitWinCondition;
			}
			return nullptr;
		}
		
		GroupRulesMenu::MenuBarListener::MenuBarListener(GroupRulesMenu*screen)
		{
			menu = screen;
		}
		
		void GroupRulesMenu::MenuBarListener::onMenuBarValueAdjustValueChanged(MenuBarValueAdjust*menuBar)
		{
			if(menuBar==menu->gameModeBar)
			{
				unsigned int gameModeVal = menu->gameMode.asUnsignedInt();
				menu->rules->setWinCondition(menu->getGameModeWinCondition(gameModeVal));
				menu->gameModeBar->setValueLabel(menu->getGameModeString(menu->rules));
				menu->gameModeValueBar->setLabel(menu->getGameModeLabelString(menu->rules));
				if(gameModeVal == GAMEMODE_TIME)
				{
					menu->gameModeValueBar->setValueLabelSuffix(":00");
				}
				else
				{
					menu->gameModeValueBar->setValueLabelSuffix("");
				}
			}
		}
	}
}
