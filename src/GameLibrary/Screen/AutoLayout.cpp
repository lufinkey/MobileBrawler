
#include "AutoLayout.h"
#include "../Actor/Actor.h"
#include "ScreenElement.h"

namespace GameLibrary
{
	AutoLayout::AutoLayout() : AutoLayout(RectangleF(0,0,0,0))
	{
		//
	}
	
	AutoLayout::AutoLayout(const AutoLayout&autoLayout)
	{
		frame = autoLayout.frame;
		actors = autoLayout.actors;
		elements = autoLayout.elements;
	}
	
	AutoLayout::AutoLayout(const RectangleF&frame_arg)
	{
		frame = frame_arg;
	}
	
	AutoLayout& AutoLayout::operator=(const AutoLayout&autoLayout)
	{
		frame = autoLayout.frame;
		actors = autoLayout.actors;
		elements = autoLayout.elements;
		return *this;
	}
	
	void AutoLayout::add(const RectF&bounds, Actor*actor)
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("actor argument cannot be null");
		}
		for(unsigned int i=0; i<actors.size(); i++)
		{
			ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				container.bounds = bounds;
				layout(container.bounds, container.actor);
				return;
			}
		}
		ActorContainer container;
		container.bounds = bounds;
		container.actor = actor;
		layout(bounds,actor);
		actors.add(container);
	}
	
	void AutoLayout::add(const RectF&bounds, ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element argument cannot be null");
		}
		for(unsigned int i=0; i<elements.size(); i++)
		{
			ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				container.bounds = bounds;
				layout(container.bounds, container.element);
				return;
			}
		}
		ElementContainer container;
		container.bounds = bounds;
		container.element = element;
		layout(bounds, element);
		elements.add(container);
	}
	
	void AutoLayout::set(Actor*actor, const RectF&bounds)
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("actor argument cannot be null");
		}
		for(unsigned int i=0; i<actors.size(); i++)
		{
			ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				container.bounds = bounds;
				layout(container.bounds, container.actor);
				return;
			}
		}
		throw IllegalArgumentException("the given Actor is not stored in this AutoLayout");
	}
	
	void AutoLayout::set(ScreenElement*element, const RectF&bounds)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element argument cannot be null");
		}
		for(unsigned int i=0; i<elements.size(); i++)
		{
			ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				container.bounds = bounds;
				layout(container.bounds, container.element);
				return;
			}
		}
		throw IllegalArgumentException("the given ScreenElement is not stored in this AutoLayout");
	}
	
	const RectF& AutoLayout::get(Actor*actor) const
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("element argument cannot be null");
		}
		for(unsigned int i=0; i<actors.size(); i++)
		{
			const ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				return container.bounds;
			}
		}
		throw IllegalArgumentException("the given Actor is not stored in this AutoLayout");
	}
	
	const RectF& AutoLayout::get(ScreenElement*element) const
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element argument cannot be null");
		}
		for(unsigned int i=0; i<elements.size(); i++)
		{
			const ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				return container.bounds;
			}
		}
		throw IllegalArgumentException("the given ScreenElement is not stored in this AutoLayout");
	}
	
	bool AutoLayout::contains(Actor*actor) const
	{
		for(unsigned int i=0; i<actors.size(); i++)
		{
			const ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				return true;
			}
		}
		return false;
	}
	
	bool AutoLayout::contains(ScreenElement*element) const
	{
		for(unsigned int i=0; i<elements.size(); i++)
		{
			const ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				return true;
			}
		}
		return false;
	}
	
	void AutoLayout::remove(Actor*actor)
	{
		if(actor == nullptr)
		{
			return;
		}
		for(unsigned int i=(actors.size()-1); i!=UINT_MAX; i--)
		{
			ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				actors.remove(i);
				return;
			}
		}
	}
	
	void AutoLayout::remove(ScreenElement*element)
	{
		if(element == nullptr)
		{
			return;
		}
		for(unsigned int i=(elements.size()-1); i!=UINT_MAX; i--)
		{
			ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				elements.remove(i);
				return;
			}
		}
	}
	
	void AutoLayout::clear()
	{
		actors.clear();
		elements.clear();
	}
	
	void AutoLayout::setFrame(const RectangleF&frame_arg)
	{
		frame = frame_arg;
		for(unsigned int i=0; i<actors.size(); i++)
		{
			ActorContainer& container = actors.get(i);
			layout(container.bounds, container.actor);
		}
		for(unsigned int i=0; i<elements.size(); i++)
		{
			ElementContainer& container = elements.get(i);
			layout(container.bounds, container.element);
		}
	}
	
	void AutoLayout::layout(const RectF&bounds, Actor*actor) const
	{
		actor->setScale(1);
		RectangleF rect = convertFrame(frame, bounds);
		actor->scaleToFit(rect);
	}
	
	void AutoLayout::layout(const RectF&bounds, ScreenElement*element) const
	{
		element->setFrame(convertFrame(frame, bounds));
	}
	
	RectangleF AutoLayout::convertFrame(const RectangleF&frame, const RectF&bounds)
	{
		float left = bounds.left*frame.width;
		float top = bounds.top*frame.height;
		float right = bounds.right*frame.width;
		float bottom = bounds.bottom*frame.height;
		return RectangleF(frame.x+left, frame.y+top, right-left, bottom-top);
	}
}
