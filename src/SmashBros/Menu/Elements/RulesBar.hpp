
#pragma once

#include "MenuBarValueAdjust.hpp"
#include <BrawlerLibrary/BrawlerLibrary.hpp>
#include "../MenuData/GroupSmashData.hpp"

using namespace BrawlerLibrary;

namespace SmashBros
{
	namespace Menu
	{
		class RulesBar : public MenuBarValueAdjust
		{
		public:
			RulesBar(Rules*rules, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&properties);
			RulesBar(double x, double y, Rules*rules, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&properties);
			virtual ~RulesBar();
			
			virtual void update(ApplicationData appData) override;
			virtual void onValueChange() override;
			
			void setValueLabelSuffix(const String&);
			
		private:
			Rules*rules;
			Number value;
			StockWinCondition* stock;
			TimeLimitWinCondition* timeLimit;
			String valueLabelSuffix;
		};
	}
}
