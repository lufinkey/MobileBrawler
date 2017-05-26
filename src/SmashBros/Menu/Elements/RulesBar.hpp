
#pragma once

#include "MenuBarValueAdjust.hpp"
#include "../MenuData/GroupSmashData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class RulesBar : public MenuBarValueAdjust
		{
		public:
			RulesBar(fgl::AssetManager* assetManager, Rules* rules, StockWinCondition* stockWinCondition, TimeLimitWinCondition* timeLimitWinCondition);
			RulesBar(fgl::AssetManager* assetManager, Rules* rules, StockWinCondition* stockWinCondition, TimeLimitWinCondition* timeLimitWinCondition, const fgl::Dictionary& properties);
			virtual ~RulesBar();
			
			virtual void update(fgl::ApplicationData appData) override;
			
			void setValueLabelSuffix(const fgl::String& suffix);

			static fgl::Dictionary getDefaultProperties(fgl::AssetManager* assetManager);
			
		private:
			Rules*rules;
			StockWinCondition* stock;
			TimeLimitWinCondition* timeLimit;
			fgl::String valueLabelSuffix;
		};
	}
}
