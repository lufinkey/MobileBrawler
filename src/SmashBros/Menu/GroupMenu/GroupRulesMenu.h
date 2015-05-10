
#pragma once

#include "../Base/BaseMenuScreen.h"
#include "../Elements/MenuBarValueAdjust.h"
#include "../Elements/RulesBar.h"
#include "../MenuData/GroupSmashData.h"

namespace SmashBros
{
	namespace Menu
	{
		class GroupRulesMenu : public BaseMenuScreen
		{
		public:
			GroupRulesMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupRulesMenu();
			
			virtual void onFrameChange() override;
			
			virtual void onWillAppear(const Transition*transition) override;
			
		protected:
			virtual void onUpdate(ApplicationData appData) override;
			virtual void onDraw(ApplicationData appData, Graphics graphics) const override;
			
		private:
			class MenuBarListener : public MenuBarValueAdjustEventListener
			{
			private:
				GroupRulesMenu* menu;
			public:
				MenuBarListener(GroupRulesMenu*menu);
				virtual void onMenuBarValueAdjustValueChanged(MenuBarValueAdjust*menuBarValueAdjust) override;
			};
			
			String getGameModeString(Rules*rules) const;
			String getGameModeLabelString(Rules*rules) const;
			unsigned int getGameModeValue(Rules*rules) const;
			WinCondition* getGameModeWinCondition(unsigned int value) const;
			
			MenuBarListener* listener;
			Rules* rules;
			StockWinCondition* stockWinCondition;
			TimeLimitWinCondition* timeLimitWinCondition;

			AutoLayoutManager autoOptionsLayoutMgr;
			
			MenuBarValueAdjust* gameModeBar;
			Number gameMode;
			RulesBar*gameModeValueBar;
		};
	}
}
