
#pragma once

#include "ArrowButton.h"

namespace SmashBros
{
	namespace Menu
	{
		class RulesBar : public SpriteActor
		{
		private:
			ArrowButton* less_button;
			ArrowButton* more_button;
			Number*value;
			Number min;
			Number max;
			Number incr;
			
		public:
			RulesBar(float x, float y, Number*value, const Number&min, const Number&max, const Number&increment, AssetManager*assetManager, const Color&hoverColor=Color::LIGHTBLUE, const Color&pressColor=Color::BLUE);
			virtual ~RulesBar();
		};
	}
}
