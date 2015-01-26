
#include "RulesBar.h"

namespace SmashBros
{
	namespace Menu
	{
		RulesBar::RulesBar(float x, float y, Rules*ruleData, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&placement)
			: MenuBarValueAdjust(x, y, "Man Survival Test!", "3", &value, 1, 25, 1, assetManager, placement)
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
		
		void RulesBar::onValueChange()
		{
			setValueLabel(value.asString());
			/*if(rules->getWinCondition() == stock)
			{
				//TODO change stock value
			}
			else if(rules->getWinCondition() == timeLimit)
			{
				//TODO change time limit
			}*/
		}
	}
}
