
#pragma once

#include <GameLibrary/GameLibrary.hpp>

using namespace fgl;

namespace SmashBros
{
	namespace Menu
	{
		class ArrowButtonEventListener;
		
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
			
			ArrowButton(Number*value, const Number&min, const Number&max, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hoverColor=Color::LIGHTBLUE, const Color&pressColor=Color::BLUE);
			ArrowButton(double x, double y, Number*value, const Number&min, const Number&max, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hoverColor=Color::LIGHTBLUE, const Color&pressColor=Color::BLUE);
			virtual ~ArrowButton();
			
			virtual void update(ApplicationData appData) override;
			
			virtual void onMousePress(const ActorMouseEvent& evt) override;
			virtual void onMouseRelease(const ActorMouseEvent& evt) override;
			
			virtual void onValueChange();
			
			void setEventListener(ArrowButtonEventListener*listener);
			void setDirection(const ArrowButton::Direction&dir);
			void setValueProperties(Number*value, const Number&min, const Number&max, const Number&incr);
			
			ArrowButtonEventListener* getEventListener() const;
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
			
			ArrowButtonEventListener* listener;
		};
		
		class ArrowButtonEventListener
		{
		public:
			ArrowButtonEventListener(){}
			virtual ~ArrowButtonEventListener(){}
			
			virtual void onArrowButtonValueChange(ArrowButton*button) = 0;
		};
	}
}
