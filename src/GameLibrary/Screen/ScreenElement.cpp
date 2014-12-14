
#include "ScreenElement.h"

namespace GameLibrary
{
	ScreenElement::ScreenElement()
	{
		parentElement = nullptr;
		updatingElements = false;
		relativePosition = true;
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
		ArrayList<ScreenElement*> children = childElements;
		updatingElements = true;

		for(unsigned int i=0; i<children.size(); i++)
		{
			ScreenElement* element = children.get(i);

			bool element_notremoved = true;
			for(unsigned int j=0; j<removedChildElements.size(); j++)
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
	}
	
	void ScreenElement::drawBackground(ApplicationData appData, Graphics graphics) const
	{
		if(!backgroundColor.equals(Color::TRANSPARENT))
		{
			Vector2f center = getCenter();
			Vector2f size = getSize();

			graphics.setColor(backgroundColor);
			graphics.fillRect(center.x-(size.x/2), center.y-(size.y/2), size.x, size.y);
		}
	}

	void ScreenElement::drawElements(ApplicationData appData, Graphics graphics) const
	{
		ArrayList<ScreenElement*> children = childElements;
		updatingElements = true;

		RectangleF frame = getFrame();

		Graphics relativeGraphics(graphics);
		relativeGraphics.translate(frame.x, frame.y);

		for(unsigned int i=0; i<children.size(); i++)
		{
			ScreenElement* element = children.get(i);

			bool element_notremoved = true;
			for(unsigned int j=0; j<removedChildElements.size(); j++)
			{
				if(removedChildElements.get(j)==element)
				{
					element_notremoved = false;
					j = removedChildElements.size();
				}
			}

			if(element_notremoved)
			{
				if(element->relativePosition)
				{
					element->draw(appData,relativeGraphics);
				}
				else
				{
					element->draw(appData,graphics);
				}
			}
		}
		updatingElements = false;
	}

	void ScreenElement::draw(ApplicationData appData, Graphics graphics) const
	{
		drawBackground(appData, graphics);
		drawElements(appData, graphics);
	}

	RectangleF ScreenElement::getFrame() const
	{
		Vector2f size = getSize();
		return RectangleF(0,0,size.x,size.y);
	}

	Vector2f ScreenElement::getCenter() const
	{
		RectangleF frame = getFrame();
		return Vector2f(frame.x+(frame.width/2), frame.y+(frame.height/2));
	}

	Vector2f ScreenElement::getSize() const
	{
		return Vector2f(0,0);
	}

	void ScreenElement::addChildElement(ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("Cannot add a null ScreenElement to a ScreenElement");
		}
		childElements.add(element);
	}

	void ScreenElement::removeFromParentElement()
	{
		if(parentElement != nullptr)
		{
			if(parentElement->updatingElements)
			{
				parentElement->removedChildElements.add(this);
			}
			unsigned int index = parentElement->childElements.indexOf(this);
			if(index == ARRAYLIST_NOTFOUND)
			{
				//TODO replace with more specific exception type
				throw Exception("Fatal Error: child ScreenElement not found in parent ScreenElement");
			}
			else
			{
				parentElement->childElements.remove(index);
			}
		}
	}

	void ScreenElement::bringChildElementToFront(ScreenElement*element)
	{
		if(element->parentElement != this)
		{
			throw IllegalArgumentException("specified ScreenElement is not a child of this ScreenElement");
		}
		
		unsigned int index = childElements.indexOf(element);
		if(index == ARRAYLIST_NOTFOUND)
		{
			//TODO replace with more specific exception type
			throw Exception("Fatal Error: child ScreenElement not found in parent ScreenElement");
		}
		else
		{
			ScreenElement* element = childElements.get(index);
			childElements.remove(index);
			childElements.add(element);
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

	void ScreenElement::enableRelativePositioning(bool toggle)
	{
		relativePosition = toggle;
	}

	bool ScreenElement::relativePositioningEnabled() const
	{
		return relativePosition;
	}

	void ScreenElement::setBackgroundColor(const Color&color)
	{
		backgroundColor = color;
	}

	const Color& ScreenElement::getBackgroundColor() const
	{
		return backgroundColor;
	}
}