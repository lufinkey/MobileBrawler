
#include "RulesBar.hpp"

namespace SmashBros
{
	namespace Menu
	{
		RulesBar::RulesBar(fgl::AssetManager* assetManager, Rules* ruleData, StockWinCondition* stockWinCondition, TimeLimitWinCondition* timeLimitWinCondition)
			: RulesBar(assetManager, ruleData, stockWinCondition, timeLimitWinCondition, getDefaultProperties(assetManager))
		{
			//
		}

		RulesBar::RulesBar(fgl::AssetManager* assetManager, Rules* ruleData, StockWinCondition* stockWinCondition, TimeLimitWinCondition* timeLimitWinCondition, const fgl::Dictionary& properties)
			: MenuBarValueAdjust(assetManager, "Stock", properties)
		{
			rules = ruleData;
			stock = stockWinCondition;
			timeLimit = timeLimitWinCondition;
			
			getBackgroundElement()->setImage(assetManager->loadTexture("elements/rules_bar.png"));
			
			setValue(3);
			setMinValue(1);
			setMaxValue(25);
			setValueIncrement(1);
			
			setValueChangeHandler([=]{
				if(rules->getWinCondition() == stock)
				{
					stock->setStock(getValue().toArithmeticValue<unsigned int>());
				}
				else if(rules->getWinCondition() == timeLimit)
				{
					timeLimit->setTimeLimit(getValue().toArithmeticValue<unsigned int>());
				}
			});
			setValueStringResolver([=](fgl::Number value) -> fgl::String {
				return value.toString() + valueLabelSuffix;
			});
		}
		
		RulesBar::~RulesBar()
		{
			//
		}

		fgl::Dictionary RulesBar::getDefaultProperties(fgl::AssetManager* assetManager)
		{
			FILE* file = assetManager->openFile("elements/rules_bar.plist", "rb");
			if(file!=nullptr)
			{
				fgl::Dictionary properties;
				fgl::Plist::loadFromFile(&properties, file);
				fgl::FileTools::closeFile(file);
				return properties;
			}
			return {};
		}
		
		void RulesBar::update(fgl::ApplicationData appData)
		{
			MenuBarValueAdjust::update(appData);
			if(rules->getWinCondition() == stock)
			{
				auto stockValue = stock->getStock();
				setMinValue(1);
				setMaxValue(25);
				setValueIncrement(1);
				setValue(stockValue);
			}
			else if(rules->getWinCondition() == timeLimit)
			{
				auto timeLimitValue = timeLimit->getTimeLimit();
				setMinValue(1);
				setMaxValue(45);
				setValueIncrement(1);
				setValue(timeLimitValue);
			}
		}
		
		void RulesBar::setValueLabelSuffix(const fgl::String& suffix)
		{
			valueLabelSuffix = suffix;
			updateValueLabelString();
		}
	}
}
