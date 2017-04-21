
#pragma once

#include "MenuButton.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class ArrowButton : public MenuButton
		{
		public:
			typedef enum
			{
				DIRECTION_UP,
				DIRECTION_DOWN,
				DIRECTION_LEFT,
				DIRECTION_RIGHT
			} Direction;
			
			ArrowButton(fgl::AssetManager* assetManager, ArrowButton::Direction direction);
			
			ArrowButton::Direction getDirection() const;
			
		private:
			static fgl::String getDirectionImagePath(ArrowButton::Direction direction);
			
			ArrowButton::Direction direction;
		};
	}
}
