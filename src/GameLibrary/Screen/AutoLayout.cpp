
#include "AutoLayout.h"
#include "../Actor/Actor.h"
#include "ScreenElement.h"

namespace GameLibrary
{
	AutoLayout::AutoLayout() : AutoLayout(RectangleD(0,0,0,0))
	{
		//
	}
	
	AutoLayout::AutoLayout(const AutoLayout&autoLayout)
	{
		frame = autoLayout.frame;
		actors = autoLayout.actors;
		elements = autoLayout.elements;
	}
	
	AutoLayout::AutoLayout(const RectangleD&frame_arg)
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
	
	void AutoLayout::add(const RectD&bounds, Actor*actor)
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("actor", "null");
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
	
	void AutoLayout::add(const RectD&bounds, ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element", "null");
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
	
	void AutoLayout::set(Actor*actor, const RectD&bounds)
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("actor", "null");
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
		throw IllegalArgumentException("actor", "not stored in the calling AutoLayout");
	}
	
	void AutoLayout::set(ScreenElement*element, const RectD&bounds)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element", "null");
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
		throw IllegalArgumentException("element", "not stored in the calling AutoLayout");
	}
	
	const RectD& AutoLayout::get(Actor*actor) const
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("actor", "null");
		}
		for(unsigned int i=0; i<actors.size(); i++)
		{
			const ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				return container.bounds;
			}
		}
		throw IllegalArgumentException("actor", "not stored in the calling AutoLayout");
	}
	
	const RectD& AutoLayout::get(ScreenElement*element) const
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element", "null");
		}
		for(unsigned int i=0; i<elements.size(); i++)
		{
			const ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				return container.bounds;
			}
		}
		throw IllegalArgumentException("element", "not stored in the calling AutoLayout");
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
	
	void AutoLayout::setFrame(const RectangleD&frame_arg)
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
	
	void AutoLayout::layout(const RectD&bounds, Actor*actor) const
	{
		actor->setScale(1);
		RectangleD rect = convertFrame(frame, bounds);
		actor->scaleToFit(rect);
	}
	
	void AutoLayout::layout(const RectD&bounds, ScreenElement*element) const
	{
		element->setFrame(convertFrame(frame, bounds));
	}
	
	RectangleD AutoLayout::convertFrame(const RectangleD&frame, const RectD&bounds)
	{
		double left = bounds.left*frame.width;
		double top = bounds.top*frame.height;
		double right = bounds.right*frame.width;
		double bottom = bounds.bottom*frame.height;
		return RectangleD(frame.x+left, frame.y+top, right-left, bottom-top);
	}
}
