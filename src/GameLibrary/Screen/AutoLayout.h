
#pragma once

#include "../Utilities/ArrayList.h"
#include "../Utilities/Geometry/Rectangle.h"

namespace GameLibrary
{
	class Actor;
	class ScreenElement;
	
	/*! Automatically lays out Actor and ScreenElement objects based on a given frame*/
	class AutoLayout
	{
	public:
		/*! default constructor*/
		AutoLayout();
		/*! copy constructor*/
		AutoLayout(const AutoLayout&);
		/*! Constructs an AutoLayout with a given frame.
			\param frame a RectangleF frame*/
		AutoLayout(const RectangleF&frame);
		/*! assignment operator*/
		AutoLayout& operator=(const AutoLayout&);
		
		
		/*! Adds an Actor to be laid out.
			\param bounds the ratio in the frame where the Actor will be laid out
			\param actor an Actor pointer*/
		void add(const RectF&bounds, Actor*actor);
		/*! Adds a ScreenElement to be laid out.
			\param bounds the ratio in the frame where the ScreenElement will be laid out
			\param element a ScreenElement pointer*/
		void add(const RectF&bounds, ScreenElement*element);
		
		
		/*! Removes a previously added Actor.
			\param actor the Actor pointer*/
		void remove(Actor*actor);
		/*! Removes a previously added ScreenElement.
			\param actor the ScreenElement pointer*/
		void remove(ScreenElement*element);
		
		
		/*! Automatically lays out all stored Actor and ScreenElement objects based on the given frame.
			\param frame a RectangleF frame*/
		void setFrame(const RectangleF&frame);
		
		
		/*! Automatically resizes and places the given Actor.
			\param bounds the ratio in the frame where the Actor will be laid out
			\param actor an Actor pointer*/
		void layout(const RectF&bounds, Actor*actor) const;
		
		
		/*! Automatically resizes and places the given ScreenElement.
			\param bounds the ratio in the frame where the ScreenElement will be laid out
			\param element a ScreenElement pointer*/
		void layout(const RectF&bounds, ScreenElement*actor) const;
		
	private:
		static RectangleF convertFrame(const RectangleF&frame, const RectF&bounds);
		
		typedef struct
		{
			RectF bounds;
			Actor* actor;
		} ActorContainer;
		
		typedef struct
		{
			RectF bounds;
			ScreenElement* element;
		} ElementContainer;
		
		RectangleF frame;
		
		ArrayList<ActorContainer> actors;
		ArrayList<ElementContainer> elements;
	};
}
