
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
		
		
		/*! Adds an Actor to be laid out. If the Actor is already stored, the new bounds are set and the function returns.
			\param bounds the ratio in the frame where the Actor will be laid out
			\param actor an Actor pointer
			\throws GameLibrary::IllegalArgumentException if the actor argument is null*/
		void add(const RectF&bounds, Actor*actor);
		/*! Adds a ScreenElement to be laid out. If the ScreenElement is already stored, the new bounds are set and the function returns.
			\param bounds the ratio in the frame where the ScreenElement will be laid out
			\param element a ScreenElement pointer
			\throws GameLibrary::IllegalArgumentException if the element argument is null*/
		void add(const RectF&bounds, ScreenElement*element);
		
		
		/*! Sets a new set of bounds for an already stored Actor.
			\param actor an Actor pointer
			\param bounds the ratio in the frame where the Actor will be laid out
			\throws GameLibrary::IllegalArgumentException if the given Actor is null or is not stored*/
		void set(Actor*actor, const RectF&bounds);
		/*! Sets a new set of bounds for an already stored ScreenElement.
			\param element a ScreenElement pointer
			\param bounds the ratio in the frame where the ScreenElement will be laid out
			\throws GameLibrary::IllegalArgumentException if the given ScreenElement is null or is not stored*/
		void set(ScreenElement*element, const RectF&bounds);
		
		
		/*! Gets the bounds for a given Actor.
			\param actor an Actor pointer
			\throws GameLibrary::IllegalArgumentException if the the given Actor is null or is not stored*/
		const RectF& get(Actor*actor) const;
		/*! Gets the bounds for a given ScreenElement.
			\param element an ScreenElement pointer
			\throws GameLibrary::IllegalArgumentException if the the given ScreenElement is null or is not stored*/
		const RectF& get(ScreenElement*element) const;
		
		
		/*! Tells whether a given Actor is stored.
			\param actor an Actor pointer
			\returns true if the Actor is stored, or false if otherwise*/
		bool contains(Actor*actor) const;
		/*! Tells whether a given ScreenElement is stored.
			\param actor an ScreenElement pointer
			\returns true if the ScreenElement is stored, or false if otherwise*/
		bool contains(ScreenElement*element) const;
		
		
		/*! Removes a previously added Actor.
			\param actor the Actor pointer*/
		void remove(Actor*actor);
		/*! Removes a previously added ScreenElement.
			\param element the ScreenElement pointer*/
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
