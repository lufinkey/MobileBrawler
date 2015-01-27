
#pragma once

#include "MenuBarValueAdjust.h"
#include <BrawlerLibrary/BrawlerLibrary.h>
#include "../MenuData/GroupSmashData.h"

namespace SmashBros
{
	using namespace BrawlerLibrary;
	
	namespace Menu
	{
		class RulesBar : public MenuBarValueAdjust
		{
		public:
			RulesBar(float x, float y, Rules*rules, StockWinCondition*stockWinCondition, TimeLimitWinCondition*timeLimitWinCondition, AssetManager*assetManager, const Dictionary&placement);
			virtual ~RulesBar();
			
			virtual void update(ApplicationData appData) override;
			virtual void onValueChange();
			
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
