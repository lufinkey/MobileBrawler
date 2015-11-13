
#include "ScreenElement.h"

namespace GameLibrary
{
	void ScreenElement::setWindow(Window*win)
	{
		Window*oldWindow = window;
		
		if(oldWindow!=win)
		{
			window = nullptr;
			
			if(oldWindow!=nullptr)
			{
				for(size_t i=0; i<childElements.size(); i++)
				{
					childElements.get(i)->setWindow(nullptr);
				}

				onRemoveFromWindow(oldWindow);
			}
			
			window = win;
			
			if(win!=nullptr)
			{
				onAddToWindow(win);
				
				for(size_t i=0; i<childElements.size(); i++)
				{
					childElements.get(i)->setWindow(win);
				}
			}
		}
	}

	void ScreenElement::onRemoveFromWindow(Window*window)
	{
		//
	}

	void ScreenElement::onAddToWindow(Window*window)
	{
		//
	}
	
	void ScreenElement::autoLayoutFrame()
	{
		if(parentElement!=nullptr)
		{
			setFrame(autoLayoutMgr.calculateFrame(frame, parentElement->getFrame()));
		}
	}

	ScreenElement::ScreenElement() : ScreenElement(RectangleD(0,0,0,0))
	{
		//
	}

	ScreenElement::ScreenElement(const RectangleD& frame_arg)
	{
		frame = frame_arg;
		window = nullptr;
		screen = nullptr;
		parentElement = nullptr;
		updatingElements = false;
		visible = true;
		backgroundColor = Color::TRANSPARENT;
	}

	ScreenElement::~ScreenElement()
	{
		while(childElements.size()>0)
		{
			childElements.get(childElements.size()-1)->removeFromParentElement();
		}
	}

	void ScreenElement::update(ApplicationData appData)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		updateElements(appData);
	}
	
	void ScreenElement::updateElements(ApplicationData appData)
	{
		ArrayList<ScreenElement*> children = childElements;
		updatingElements = true;

		for(size_t i=0; i<children.size(); i++)
		{
			ScreenElement* element = children.get(i);

			bool element_notremoved = true;
			for(size_t j=0; j<removedChildElements.size(); j++)
			{
				if(removedChildElements.get(j)==element)
				{
					element_notremoved = false;
					j = removedChildElements.size();
				}
			}

			if(element_notremoved)
			{
				element->update(appData);
			}
		}
		
		updatingElements = false;
	}
	
	void ScreenElement::drawBackground(ApplicationData appData, Graphics graphics) const
	{
		if(visible && !backgroundColor.equals(Color::TRANSPARENT))
		{
			RectangleD rect = getFrame();
			graphics.setColor(backgroundColor);
			graphics.fillRect(rect.x, rect.y, rect.width, rect.height);
		}
	}
	
	void ScreenElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		//Open for implementation
	}
	
	void ScreenElement::drawElements(ApplicationData appData, Graphics graphics) const
	{
		ArrayList<ScreenElement*> children = childElements;
		updatingElements = true;
		
		for(size_t i=0; i<children.size(); i++)
		{
			ScreenElement* element = children.get(i);
			
			bool element_notremoved = true;
			for(size_t j=0; j<removedChildElements.size(); j++)
			{
				if(removedChildElements.get(j)==element)
				{
					element_notremoved = false;
					j = removedChildElements.size();
				}
			}
			
			if(element_notremoved)
			{
				element->draw(appData,graphics);
			}
		}
		updatingElements = false;
	}
	
	void ScreenElement::draw(ApplicationData appData, Graphics graphics) const
	{
		RectangleD frame = getFrame();
		if(clipsToFrame)
		{
			graphics.clip(frame);
		}
		drawBackground(appData, graphics);
		drawMain(appData, graphics);
		graphics.translate(frame.x, frame.y);
		drawElements(appData, graphics);
	}
	
	void ScreenElement::setFrame(const RectangleD&frame_arg)
	{
		frame = frame_arg;
		for(size_t childElements_size=childElements.size(), i=0; i<childElements_size; i++)
		{
			ScreenElement* childElement = childElements.get(i);
			if(childElement->hasLayoutRules())
			{
				childElement->autoLayoutFrame();
			}
		}
	}
	
	RectangleD ScreenElement::getFrame() const
	{
		return frame;
	}
	
	Vector2d ScreenElement::getCenter() const
	{
		RectangleD frame = getFrame();
		return Vector2d(frame.x+(frame.width/2), frame.y+(frame.height/2));
	}
	
	void ScreenElement::addChildElement(ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element", "null");
		}
		else if(element->parentElement != nullptr)
		{
			throw IllegalArgumentException("element", "already added to another ScreenElement");
		}
		element->parentElement = this;
		childElements.add(element);
		if(element->hasLayoutRules())
		{
			element->autoLayoutFrame();
		}
	}
	
	void ScreenElement::removeFromParentElement()
	{
		if(parentElement != nullptr)
		{
			if(parentElement->updatingElements)
			{
				parentElement->removedChildElements.add(this);
			}
			size_t index = parentElement->childElements.indexOf(this);
			if(index == ARRAYLIST_NOTFOUND)
			{
				throw IllegalStateException("Child ScreenElement not found in parent ScreenElement");
			}
			else
			{
				parentElement->childElements.remove(index);
			}
		}
	}
	
	void ScreenElement::bringChildElementToFront(ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element", "null");
		}
		else if(element->parentElement != this)
		{
			throw IllegalArgumentException("element", "not a child of the calling element");
		}
		
		size_t index = childElements.indexOf(element);
		if(index == ARRAYLIST_NOTFOUND)
		{
			throw IllegalStateException("Child ScreenElement not found in parent ScreenElement");
		}
		else
		{
			ScreenElement* element = childElements.get(index);
			childElements.remove(index);
			childElements.add(element);
		}
	}
	
	void ScreenElement::sendChildElementToBack(ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("element", "null");
		}
		else if(element->parentElement != this)
		{
			throw IllegalArgumentException("element", "not a child of the calling element");
		}
		
		size_t index = childElements.indexOf(element);
		if(index == ARRAYLIST_NOTFOUND)
		{
			throw IllegalStateException("Child ScreenElement not found in parent ScreenElement");
		}
		else
		{
			ScreenElement* element = childElements.get(index);
			childElements.remove(index);
			childElements.add(0,element);
		}
	}
	
	const ArrayList<ScreenElement*>& ScreenElement::getChildElements() const
	{
		return childElements;
	}
	
	ScreenElement* ScreenElement::getParentElement() const
	{
		return parentElement;
	}
	
	void ScreenElement::setLayoutRule(const LayoutRuleType& ruleType, double value, const LayoutValueType& valueType)
	{
		autoLayoutMgr.setRule(ruleType, value, valueType);
		autoLayoutFrame();
	}
	
	bool ScreenElement::hasLayoutRules() const
	{
		return autoLayoutMgr.hasRules();
	}
	
	void ScreenElement::removeAllLayoutRules()
	{
		autoLayoutMgr.removeAllRules();
	}
	
	const AutoLayoutManager& ScreenElement::getAutoLayoutManager() const
	{
		return autoLayoutMgr;
	}
	
	void ScreenElement::setBackgroundColor(const Color&color)
	{
		backgroundColor = color;
	}
	
	const Color& ScreenElement::getBackgroundColor() const
	{
		return backgroundColor;
	}
	
	void ScreenElement::setVisible(bool toggle, bool applyToChildren)
	{
		visible = toggle;
		if(applyToChildren)
		{
			for(size_t i=0; i<childElements.size(); i++)
			{
				childElements.get(i)->setVisible(toggle, applyToChildren);
			}
		}
	}
	
	bool ScreenElement::isVisible() const
	{
		return visible;
	}
	
	void ScreenElement::setClippedToFrame(bool toggle)
	{
		clipsToFrame = toggle;
	}
	
	bool ScreenElement::isClippedToFrame() const
	{
		return clipsToFrame;
	}

	bool ScreenElement::isHandlingMouseEvents() const
	{
		return false;
	}
	
	bool ScreenElement::doesHandleMouseInput() const
	{
		return false;
	}
	
	bool ScreenElement::isTouchableAtPoint(const Vector2d& point) const
	{
		if(doesHandleMouseInput())
		{
			RectangleD frame = getFrame();
			if(!frame.contains(point))
			{
				return false;
			}
			for(size_t i=0; i<childElements.size(); i++)
			{
				if(childElements[i]->isTouchableAtPoint(point))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
}