
#include "RulesBar.h"

namespace SmashBros
{
	namespace Menu
	{
		RulesBar::RulesBar(float x, float y, Rules*ruleData, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&placement)
			: MenuBarValueAdjust(x, y, "Stock", "3", &value, 1, 25, 1, assetManager, placement)
		{
			rules = ruleData;
			stock = stockWinCondition;
			timeLimit = timeLimitWinCondition;
			value = 3;
			
			addAnimation("RulesBar", new Animation(1, assetManager, "elements/rules_bar.png"));
			changeAnimation("RulesBar", Animation::FORWARD);
		}
		
		RulesBar::~RulesBar()
		{
			//
		}
		
		void RulesBar::update(ApplicationData appData)
		{
			MenuBarValueAdjust::update(appData);
			if(rules->getWinCondition() == stock)
			{
				value = stock->getStock();
				setValueProperties(&value, 1, 25, 1);
				setValueLabel(value.asString() + valueLabelSuffix);
			}
			else if(rules->getWinCondition() == timeLimit)
			{
				value = timeLimit->getTimeLimit();
				setValueProperties(&value, 1, 45, 1);
				setValueLabel(value.asString() + valueLabelSuffix);
			}
		}
		
		void RulesBar::onValueChange()
		{
			setValueLabel(value.asString());
			if(rules->getWinCondition() == stock)
			{
				stock->setStock(value.asUnsignedInt());
			}
			else if(rules->getWinCondition() == timeLimit)
			{
				timeLimit->setTimeLimit(value.asUnsignedInt());
			}
		}
		
		void RulesBar::setValueLabelSuffix(const String&suffix)
		{
			valueLabelSuffix = suffix;
		}
	}
}
