
#include "AutoLayoutManager.h"
#include "../Actor/Actor.h"
#include "ScreenElement.h"

namespace GameLibrary
{
	AutoLayoutManager::AutoLayoutManager() : AutoLayoutManager(RectangleD(0,0,0,0))
	{
		//
	}
	
	AutoLayoutManager::AutoLayoutManager(const AutoLayoutManager&autoLayoutMgr)
	{
		frame = autoLayoutMgr.frame;
		actors = autoLayoutMgr.actors;
		elements = autoLayoutMgr.elements;
	}
	
	AutoLayoutManager::AutoLayoutManager(const RectangleD&frame_arg)
	{
		frame = frame_arg;
	}
	
	AutoLayoutManager& AutoLayoutManager::operator=(const AutoLayoutManager&autoLayout)
	{
		frame = autoLayout.frame;
		actors = autoLayout.actors;
		elements = autoLayout.elements;
		return *this;
	}
	
	void AutoLayoutManager::add(const RectD&bounds, Actor*actor)
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
	
	void AutoLayoutManager::add(const RectD&bounds, ScreenElement*element)
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
	
	void AutoLayoutManager::set(Actor*actor, const RectD&bounds)
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
	
	void AutoLayoutManager::set(ScreenElement*element, const RectD&bounds)
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
	
	const RectD& AutoLayoutManager::get(Actor*actor) const
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
	
	const RectD& AutoLayoutManager::get(ScreenElement*element) const
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
	
	bool AutoLayoutManager::contains(Actor*actor) const
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
	
	bool AutoLayoutManager::contains(ScreenElement*element) const
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
	
	void AutoLayoutManager::remove(Actor*actor)
	{
		if(actor == nullptr)
		{
			return;
		}
		for(size_t i=(actors.size()-1); i!=SIZE_MAX; i--)
		{
			ActorContainer& container = actors.get(i);
			if(container.actor == actor)
			{
				actors.remove(i);
				return;
			}
		}
	}
	
	void AutoLayoutManager::remove(ScreenElement*element)
	{
		if(element == nullptr)
		{
			return;
		}
		for(size_t i=(elements.size()-1); i!=SIZE_MAX; i--)
		{
			ElementContainer& container = elements.get(i);
			if(container.element == element)
			{
				elements.remove(i);
				return;
			}
		}
	}
	
	void AutoLayoutManager::clear()
	{
		actors.clear();
		elements.clear();
	}
	
	void AutoLayoutManager::setFrame(const RectangleD&frame_arg)
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
	
	void AutoLayoutManager::layout(const RectD&bounds, Actor*actor) const
	{
		actor->setScale(1);
		RectangleD rect = convertFrame(frame, bounds);
		actor->scaleToFit(rect);
	}
	
	void AutoLayoutManager::layout(const RectD&bounds, ScreenElement*element) const
	{
		element->setFrame(convertFrame(frame, bounds));
	}
	
	RectangleD AutoLayoutManager::convertFrame(const RectangleD&frame, const RectD&bounds)
	{
		double left = bounds.left*frame.width;
		double top = bounds.top*frame.height;
		double right = bounds.right*frame.width;
		double bottom = bounds.bottom*frame.height;
		return RectangleD(frame.x+left, frame.y+top, right-left, bottom-top);
	}
}
