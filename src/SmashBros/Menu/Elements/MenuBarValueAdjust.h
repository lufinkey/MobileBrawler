
#pragma once

#include "MenuBar.h"
#include "ArrowButton.h"

namespace SmashBros
{
	namespace Menu
	{
		class MenuBarValueAdjust : public MenuBar
		{
		public:
			MenuBarValueAdjust(float x, float y, const String&label, const String&valueLabel, Number*value, const Number&min, const Number&max, const Number&increment, AssetManager*assetManager);
			virtual ~MenuBarValueAdjust();
			
			virtual void update(ApplicationData appData) override;
			virtual void draw(ApplicationData appData, Graphics graphics) const override;
			
			virtual void onValueChange();
			
			void setValueLabel(const String&);
			
			const String& getValueLabel() const;
			
		private:
			ArrowButton* arrow_less;
			ArrowButton* arrow_more;
			TextActor* value_label_actor;
			RectF value_label_bounds;
			Number*value;
			Number min;
			Number max;
			Number incr;
		};
	}
}
