
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
		ElementContainer container;
		container.bounds = bounds;
		container.element = element;
		layout(bounds, element);
		elements.add(container);
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
			}
		}
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
		actor->scaleToFit(convertFrame(frame,bounds));
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
