
#pragma once

#include "MenuBarValueAdjust.h"
#include <BrawlerLibrary/BrawlerLibrary.h>
#include "../MenuData/GroupSmashData.h"

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
			virtual void onValueChange();
			
			void setValueLabelSuffix(const WideString&);
			
		private:
			Rules*rules;
			Number value;
			StockWinCondition* stock;
			TimeLimitWinCondition* timeLimit;
			WideString valueLabelSuffix;
		};
	}
}
