
#pragma once

#include "MenuBar.hpp"
#include "ArrowButton.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class MenuBarValueAdjustEventListener;
		
		class MenuBarValueAdjust : public MenuBar
		{
		private:
			TextActor* value_label_actor;
			ArrowButton* arrow_less;
			ArrowButton* arrow_more;
			
			AutoLayoutManager value_label_autoLayoutMgr;
			AutoLayoutManager arrow_less_autoLayoutMgr;
			AutoLayoutManager arrow_more_autoLayoutMgr;
			
			Color value_label_color;
			String arrow_less_dir;
			String arrow_more_dir;

			Number*value;
			Number min;
			Number max;
			Number incr;
			
			MenuBarValueAdjustEventListener* listener;
			
			void applyProperties(const Dictionary&properties);
			
		public:
			MenuBarValueAdjust(const String&label, const String&valueLabel, Number*value, const Number&min, const Number&max, const Number&increment, AssetManager*assetManager, const Dictionary&properties);
			MenuBarValueAdjust(double x, double y, const String&label, const String&valueLabel, Number*value, const Number&min, const Number&max, const Number&increment, AssetManager*assetManager, const Dictionary&properties);
			virtual ~MenuBarValueAdjust();
			
			virtual void update(ApplicationData appData) override;
			virtual void draw(ApplicationData appData, Graphics graphics) const override;
			
			virtual void onValueChange();
			
			void setEventListener(MenuBarValueAdjustEventListener* listener);
			void setValueLabel(const String&);
			MenuBarValueAdjustEventListener* getEventListener() const;
			const String& getValueLabel() const;
			
			void setValueProperties(Number*value, const Number&min, const Number&max, const Number&incr);
			
			virtual void updateSize() override;
		};
		
		class MenuBarValueAdjustEventListener
		{
		public:
			MenuBarValueAdjustEventListener(){}
			virtual ~MenuBarValueAdjustEventListener(){}
			
			virtual void onMenuBarValueAdjustValueChanged(MenuBarValueAdjust*menuBarValueAdjust) = 0;
		};
	}
}
