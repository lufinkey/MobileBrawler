
#include "GroupRulesMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
#define GAMEMODE_ERROR 0U
#define GAMEMODE_STOCK 1U
#define GAMEMODE_TIME 2U
		
		GroupRulesMenu::GroupRulesMenu(MenuData* menuData, GroupSmashData* groupSmashData) : BaseMenuScreen(menuData)
		{
			auto assetManager = menuData->getAssetManager();

			rules = groupSmashData->getRules();

			stockWinCondition = groupSmashData->getStockWinCondition();
			timeLimitWinCondition = groupSmashData->getTimeLimitWinCondition();
			
			gameModeBar = new MenuBarValueAdjust(assetManager, "Rules");
			gameModeBar->setMinValue(GAMEMODE_STOCK);
			gameModeBar->setMaxValue(GAMEMODE_TIME);
			gameModeBar->setValue(getGameModeValue(rules));
			gameModeBar->setValueIncrement(1);
			gameModeBar->setValueStringResolver([=](fgl::Number value) -> fgl::String {
				auto mode = value.toArithmeticValue<unsigned int>();
				if(mode == GAMEMODE_STOCK)
				{
					return "Stock";
				}
				else if(mode == GAMEMODE_TIME)
				{
					return "Time";
				}
				return "Error";
			});
			gameModeBar->setValueChangeHandler([=]{
				auto gameModeVal = gameModeBar->getValue().toArithmeticValue<unsigned int>();
				rules->setWinCondition(getGameModeWinCondition(gameModeVal));
				gameModeValueBar->getLabelElement()->setText(getGameModeLabelString(rules));
				if(gameModeVal == GAMEMODE_TIME)
				{
					gameModeValueBar->setValueLabelSuffix(":00");
				}
				else
				{
					gameModeValueBar->setValueLabelSuffix("");
				}
			});
			gameModeBar->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.14, fgl::LAYOUTVALUE_RATIO);
			gameModeBar->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.16, fgl::LAYOUTVALUE_RATIO);
			gameModeBar->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.14, fgl::LAYOUTVALUE_RATIO);
			gameModeBar->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.72, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(gameModeBar);

			gameModeValueBar = new RulesBar(assetManager, rules, stockWinCondition, timeLimitWinCondition, MenuBar::getDefaultProperties(assetManager));
			gameModeValueBar->getBackgroundElement()->setImage(assetManager->loadTexture("elements/menu_bar.png"));
			gameModeValueBar->getLabelElement()->setText(getGameModeLabelString(rules));
			gameModeValueBar->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.14, fgl::LAYOUTVALUE_RATIO);
			gameModeValueBar->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.36, fgl::LAYOUTVALUE_RATIO);
			gameModeValueBar->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.14, fgl::LAYOUTVALUE_RATIO);
			gameModeValueBar->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.52, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(gameModeValueBar);
		}
		
		GroupRulesMenu::~GroupRulesMenu()
		{
			delete gameModeBar;
			delete gameModeValueBar;
		}
		
		void GroupRulesMenu::onWillAppear(const fgl::Transition*transition)
		{
			gameModeValueBar->getLabelElement()->setText(getGameModeLabelString(rules));
			if(rules->getWinCondition() == stockWinCondition)
			{
				gameModeValueBar->setValueLabelSuffix("");
			}
			else if(rules->getWinCondition() == timeLimitWinCondition)
			{
				gameModeValueBar->setValueLabelSuffix(":00");
			}
		}
		
		fgl::String GroupRulesMenu::getGameModeLabelString(Rules*rules) const
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
	}
}
