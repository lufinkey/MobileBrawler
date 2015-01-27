
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	namespace Menu
	{
		class ArrowButton : public SpriteActor
		{
		public:
			typedef enum
			{
				DIRECTION_UP,
				DIRECTION_DOWN,
				DIRECTION_LEFT,
				DIRECTION_RIGHT
			} Direction;
			
			ArrowButton(float x, float y, Number*value, const Number&min, const Number&max, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hoverColor=Color::LIGHTBLUE, const Color&pressColor=Color::BLUE);
			virtual ~ArrowButton();
			
			virtual void update(ApplicationData appData) override;
			
			virtual void onMousePress(ApplicationData appData, unsigned int touchID) override;
			virtual void onMouseRelease(ApplicationData appData, unsigned int touchID) override;
			
			virtual void onValueChange();
			
			void setDirection(const ArrowButton::Direction&dir);
			const ArrowButton::Direction& getDirection() const;
			
		private:
			Direction dir;
			bool selecting;
			Number*value;
			Number min;
			Number max;
			Number incr;
			Color hoverColor;
			Color pressColor;
		};
	}
}
