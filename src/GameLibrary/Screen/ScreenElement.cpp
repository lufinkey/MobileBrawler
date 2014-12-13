
#include "ScreenElement.h"

namespace GameLibrary
{
	ScreenElement::ScreenElement()
	{
		x = 0;
		y = 0;
		parentElement = nullptr;
		updatingElements = false;
		relativePosition = true;
	}

	ScreenElement::~ScreenElement()
	{
		if(parentElement != nullptr)
		{
			removeFromParentElement();
		}
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

	void ScreenElement::draw(ApplicationData appData, Graphics graphics) const
	{
		ArrayList<ScreenElement*> children = childElements;
		updatingElements = true;

		Graphics relativeGraphics(graphics);
		graphics.translate(x,y);

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

	Vector2f ScreenElement::getCenter() const
	{
		Vector2f size = getSize();
		return Vector2f(x+(size.x/2), y+(size.y/2));
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

	bool ScreenElement::relativePositioningEnabled()
	{
		return relativePosition;
	}
}