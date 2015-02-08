
#pragma once

#include "../../Types.h"
#include "../Drawable.h"

namespace GameLibrary
{
	/*! An interface class for creating a custom transition between two Drawable objects*/
	class Transition
	{
	public:
		/*! The default transition duration, in milliseconds (250 milliseconds)*/
		static const unsigned long long defaultDuration = 250ULL;
		
		/*! default constructor*/
		Transition(){}
		/*! virtual destructor*/
		virtual ~Transition(){}
		
		/*! Draws the two Drawable objects in their transition state. For best results, the two Drawable objects should have the same frame (bounding box), or be set at the same coordinates.
			\param appData specifies information about the Application drawing the Transition, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Actor
			\param progress the current Transition progress, from 0 to 1; Making this a value other than 0 through 1 causes undefined behavior
			\param element1 the first Drawable being transitioned
			\param element2 the second Drawable being transitioned*/
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const = 0;
	};
}