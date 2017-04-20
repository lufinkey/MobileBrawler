
#pragma once

#include "MenuBarValueAdjust.hpp"
#include <SmashLib/SmashLib.hpp>
#include "../MenuData/GroupSmashData.hpp"

using namespace SmashLib;

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
