
#pragma once

#include "../Base/BaseMenuScreen.hpp"
#include "../Elements/MenuBarValueAdjust.hpp"
#include "../Elements/RulesBar.hpp"
#include "../MenuData/GroupSmashData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class GroupRulesMenu : public BaseMenuScreen
		{
		public:
			GroupRulesMenu(const SmashData&smashData, const GroupSmashData&groupSmashData);
			virtual ~GroupRulesMenu();
			
			virtual void onSizeChange(const Vector2d& oldSize, const Vector2d& newSize) override;
			
			virtual void onWillAppear(const Transition*transition) override;
			
		protected:
			virtual void onUpdate(const ApplicationData& appData) override;
			virtual void onDraw(const ApplicationData& appData, Graphics graphics) const override;
			
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
			
			MenuBarValueAdjust* gameModeBar;
			Number gameMode;
			AutoLayoutManager gameModeBarAutoLayoutMgr;
			
			RulesBar*gameModeValueBar;
			AutoLayoutManager gameModeValueBarAutoLayoutMgr;
		};
	}
}
