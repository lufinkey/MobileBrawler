
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
				for(unsigned int i=0; i<childElements.size(); i++)
				{
					childElements.get(i)->setWindow(nullptr);
				}

				onRemoveFromWindow(oldWindow);
			}

			window = win;

			if(win!=nullptr)
			{
				onAddToWindow(win);

				for(unsigned int i=0; i<childElements.size(); i++)
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

	ScreenElement::ScreenElement() : ScreenElement(RectangleF(0,0,0,0))
	{
		//
	}

	ScreenElement::ScreenElement(const RectangleF&frame_arg)
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
		if(visible && !backgroundColor.equals(Color::TRANSPARENT))
		{
			RectangleF rect = getFrame();
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

		RectangleF frame = getFrame();

		graphics.translate(frame.x, frame.y);

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
				element->draw(appData,graphics);
			}
		}
		updatingElements = false;
	}

	void ScreenElement::draw(ApplicationData appData, Graphics graphics) const
	{
		drawBackground(appData, graphics);
		drawMain(appData, graphics);
		drawElements(appData, graphics);
	}

	void ScreenElement::setFrame(const RectangleF&frame_arg)
	{
		frame = frame_arg;
	}

	RectangleF ScreenElement::getFrame() const
	{
		return frame;
	}

	Vector2f ScreenElement::getCenter() const
	{
		RectangleF frame = getFrame();
		return Vector2f(frame.x+(frame.width/2), frame.y+(frame.height/2));
	}

	void ScreenElement::addChildElement(ScreenElement*element)
	{
		if(element == nullptr)
		{
			throw IllegalArgumentException("Cannot add a null ScreenElement to a ScreenElement");
		}
		else if(element->parentElement != nullptr)
		{
			throw IllegalArgumentException("Cannot add a ScreenElement that is already added to another ScreenElement");
		}
		element->parentElement = this;
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
			throw IllegalArgumentException("element argument cannot be null");
		}
		else if(element->parentElement != this)
		{
			throw IllegalArgumentException("Specified ScreenElement is not a child of this ScreenElement");
		}
		
		unsigned int index = childElements.indexOf(element);
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
			throw IllegalArgumentException("element argument cannot be null");
		}
		else if(element->parentElement != this)
		{
			throw IllegalArgumentException("Specified ScreenElement is not a child of this ScreenElement");
		}
		
		unsigned int index = childElements.indexOf(element);
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
			for(unsigned int i=0; i<childElements.size(); i++)
			{
				childElements.get(i)->setVisible(toggle, applyToChildren);
			}
		}
	}
	
	bool ScreenElement::isVisible() const
	{
		return visible;
	}
}