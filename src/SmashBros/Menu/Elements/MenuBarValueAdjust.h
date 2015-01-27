
#pragma once

#include "MenuBar.h"
#include "ArrowButton.h"

namespace SmashBros
{
	namespace Menu
	{
		class MenuBarValueAdjust : public MenuBar
		{
		private:
			TextActor* value_label_actor;
			ArrowButton* arrow_less;
			ArrowButton* arrow_more;
			
			RectF value_label_bounds;
			Color value_label_color;
			RectF arrow_less_bounds;
			RectF arrow_more_bounds;
			String arrow_less_dir;
			String arrow_more_dir;

			Number*value;
			Number min;
			Number max;
			Number incr;
			
			void applyProperties(const Dictionary&properties);
			
		public:
			MenuBarValueAdjust(float x, float y, const String&label, const String&valueLabel, Number*value, const Number&min, const Number&max, const Number&increment, AssetManager*assetManager, const Dictionary&properties);
			virtual ~MenuBarValueAdjust();
			
			virtual void update(ApplicationData appData) override;
			virtual void draw(ApplicationData appData, Graphics graphics) const override;
			
			virtual void onValueChange();
			
			void setValueLabel(const String&);
			
			const String& getValueLabel() const;
		};
	}
}
