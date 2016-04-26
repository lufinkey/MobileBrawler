
#include "RulesBar.h"

namespace SmashBros
{
	namespace Menu
	{
		RulesBar::RulesBar(Rules*ruleData, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&properties)
			: RulesBar(0, 0, ruleData, stockWinCondition, timeLimitWinCondition, assetManager, properties)
		{
			//
		}
		
		RulesBar::RulesBar(double x, double y, Rules*ruleData, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&properties)
			: MenuBarValueAdjust(x, y, "Stock", "3", &value, 1, 25, 1, assetManager, properties)
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
				setValueLabel(value.toString() + valueLabelSuffix);
			}
			else if(rules->getWinCondition() == timeLimit)
			{
				value = timeLimit->getTimeLimit();
				setValueProperties(&value, 1, 45, 1);
				setValueLabel(value.toString() + valueLabelSuffix);
			}
		}
		
		void RulesBar::onValueChange()
		{
			setValueLabel(value.toString());
			if(rules->getWinCondition() == stock)
			{
				stock->setStock(value.toArithmeticValue<unsigned int>());
			}
			else if(rules->getWinCondition() == timeLimit)
			{
				timeLimit->setTimeLimit(value.toArithmeticValue<unsigned int>());
			}
		}
		
		void RulesBar::setValueLabelSuffix(const String&suffix)
		{
			valueLabelSuffix = suffix;
		}
	}
}
