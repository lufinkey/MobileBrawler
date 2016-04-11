
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
			RectangleD frame = getFrame();
			
			listener = new MenuBarListener(this);
			rules = groupSmashData.getRules();
			stockWinCondition = groupSmashData.getStockWinCondition();
			timeLimitWinCondition = groupSmashData.getTimeLimitWinCondition();
			
			gameMode = getGameModeValue(rules);
			gameModeBar = new MenuBarValueAdjust("Rules",
													getGameModeString(rules),
													&gameMode,
													GAMEMODE_STOCK, GAMEMODE_TIME, 1,
													smashData.getMenuData()->getAssetManager(),
													smashData.getMenuData()->getMenuBarProperties());
			gameModeBar->setEventListener(listener);
			gameModeBarAutoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.14, LAYOUTVALUE_RATIO);
			gameModeBarAutoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.12, LAYOUTVALUE_RATIO);
			gameModeBarAutoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.86, LAYOUTVALUE_RATIO);
			gameModeBarAutoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.28, LAYOUTVALUE_RATIO);
			gameModeBar->scaleToFit(gameModeBarAutoLayoutMgr.calculateFrame(gameModeBar->getFrame(), frame));
			
			gameModeValueBar = new RulesBar(rules, stockWinCondition, timeLimitWinCondition,
											smashData.getMenuData()->getAssetManager(),
											smashData.getMenuData()->getMenuBarProperties());
			gameModeValueBar->changeAnimation("MenuBar", Animation::FORWARD);
			gameModeValueBar->setLabel(getGameModeLabelString(rules));
			gameModeValueBarAutoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.14, LAYOUTVALUE_RATIO);
			gameModeValueBarAutoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.32, LAYOUTVALUE_RATIO);
			gameModeValueBarAutoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.86, LAYOUTVALUE_RATIO);
			gameModeValueBarAutoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.48, LAYOUTVALUE_RATIO);
		}
		
		GroupRulesMenu::~GroupRulesMenu()
		{
			delete gameModeBar;
			delete listener;
		}
		
		void GroupRulesMenu::onFrameChange(const RectangleD& oldFrame, const RectangleD& newFrame)
		{
			BaseMenuScreen::onFrameChange(oldFrame, newFrame);
			RectangleD frame = getFrame();
			gameModeBar->scaleToFit(gameModeBarAutoLayoutMgr.calculateFrame(gameModeBar->getFrame(), frame));
			gameModeValueBar->scaleToFit(gameModeValueBarAutoLayoutMgr.calculateFrame(gameModeValueBar->getFrame(), frame));
		}
		
		void GroupRulesMenu::onWillAppear(const Transition*transition)
		{
			gameModeBar->setValueLabel(getGameModeString(rules));
			gameModeValueBar->setLabel(getGameModeLabelString(rules));
			if(rules->getWinCondition() == stockWinCondition)
			{
				gameModeValueBar->setValueLabel((String)"" + stockWinCondition->getStock());
				gameModeValueBar->setValueLabelSuffix("");
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				gameModeValueBar->setValueLabel((String)"" + timeLimitWinCondition->getTimeLimit());
				gameModeValueBar->setValueLabelSuffix(":00");
			}
		}
		
		void GroupRulesMenu::onUpdate(ApplicationData appData)
		{
			BaseMenuScreen::onUpdate(appData);
			gameModeBar->update(appData);
			gameModeValueBar->update(appData);
		}
		
		void GroupRulesMenu::onDraw(ApplicationData appData, Graphics graphics) const
		{
			BaseMenuScreen::onDraw(appData, graphics);
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
