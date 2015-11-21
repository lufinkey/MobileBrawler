
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
	
	ScreenElement::ScreenElement() : ScreenElement(RectangleD(0, 0, 0, 0))
	{
		//
	}
	
	ScreenElement::ScreenElement(const RectangleD& frame_arg)
	{
		frame = frame_arg;
		window = nullptr;
		screen = nullptr;
		parentElement = nullptr;
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
		for(size_t i=0; i<children.size(); i++)
		{
			ScreenElement* element = children.get(i);
			element->update(appData);
		}
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
		for(size_t i=0; i<children.size(); i++)
		{
			ScreenElement* element = children.get(i);
			element->draw(appData, graphics);
		}
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
			size_t index = parentElement->childElements.indexOf(this);
			if(index == ARRAYLIST_NOTFOUND)
			{
				throw IllegalStateException("Child ScreenElement not found in parent ScreenElement");
			}
			else
			{
				parentElement->childElements.remove(index);
				parentElement = nullptr;
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
			childElements.add(0, element);
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
	
	ScreenElement* ScreenElement::handleMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos)
	{
		return tellChildrenHandleMouseMove(appData, mouseIndex, mousepos);
		//Open for implementation
	}
	void ScreenElement::elementHandledMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos, ScreenElement* element)
	{
		tellChildrenElementHandledMouseMove(appData, mouseIndex, mousepos, element);
		//Open for implementation
	}
	
	ScreenElement* ScreenElement::handleMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos)
	{
		return tellChildrenHandleMousePress(appData, mouseIndex, button, mousepos);
		//Open for implementation
	}
	void ScreenElement::elementHandledMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element)
	{
		tellChildrenElementHandledMousePress(appData, mouseIndex, button, mousepos, element);
		//Open for implementation
	}
	
	ScreenElement* ScreenElement::handleMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos)
	{
		return tellChildrenHandleMouseRelease(appData, mouseIndex, button, mousepos);
		//Open for implementation
	}
	void ScreenElement::elementHandledMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element)
	{
		tellChildrenElementHandledMouseRelease(appData, mouseIndex, button, mousepos, element);
		//Open for implementation
	}
	
	void ScreenElement::handleMouseDisconnect(const ApplicationData& appData, unsigned int mouseIndex)
	{
		tellChildrenHandleMouseDisconnect(appData, mouseIndex);
		//Open for implementation
	}
	
	
	ScreenElement* ScreenElement::handleTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		return tellChildrenHandleTouchMove(appData, touchID, touchpos);
		//Open for implementation
	}
	void ScreenElement::elementHandledTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		tellChildrenElementHandledTouchMove(appData, touchID, touchpos, element);
		//Open for implementation
	}
	
	ScreenElement* ScreenElement::handleTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		return tellChildrenHandleTouchBegin(appData, touchID, touchpos);
		//Open for implementation
	}
	void ScreenElement::elementHandledTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		tellChildrenElementHandledTouchBegin(appData, touchID, touchpos, element);
		//Open for implementation
	}
	
	ScreenElement* ScreenElement::handleTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		return tellChildrenHandleTouchEnd(appData, touchID, touchpos);
		//Open for implementation
	}
	void ScreenElement::elementHandledTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		tellChildrenElementHandledTouchEnd(appData, touchID, touchpos, element);
		//Open for implementation
	}
	
	
	
	ScreenElement* ScreenElement::tellChildrenHandleMouseMove(ApplicationData appData, unsigned int mouseIndex, Vector2d mousepos)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		mousepos.x -= frame.x;
		mousepos.y -= frame.y;
		
		ScreenElement* handler = nullptr;
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			ScreenElement* child = childElements.get(i);
			if(handler==nullptr)
			{
				handler = child->handleMouseMove(appData, mouseIndex, mousepos);
			}
			else
			{
				child->elementHandledMouseMove(appData, mouseIndex, mousepos, handler);
			}
		}
		return handler;
	}
	void ScreenElement::tellChildrenElementHandledMouseMove(ApplicationData appData, unsigned int mouseIndex, Vector2d mousepos, ScreenElement* element)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		mousepos.x -= frame.x;
		mousepos.y -= frame.y;
		
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->elementHandledMouseMove(appData, mouseIndex, mousepos, element);
		}
	}
	
	ScreenElement* ScreenElement::tellChildrenHandleMousePress(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		mousepos.x -= frame.x;
		mousepos.y -= frame.y;
		
		ScreenElement* handler = nullptr;
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			ScreenElement* child = childElements.get(i);
			if(handler==nullptr)
			{
				handler = child->handleMousePress(appData, mouseIndex, button, mousepos);
			}
			else
			{
				child->elementHandledMousePress(appData, mouseIndex, button, mousepos, handler);
			}
		}
		return handler;
	}
	void ScreenElement::tellChildrenElementHandledMousePress(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos, ScreenElement* element)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		mousepos.x -= frame.x;
		mousepos.y -= frame.y;
		
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->elementHandledMousePress(appData, mouseIndex, button, mousepos, element);
		}
	}
	
	ScreenElement* ScreenElement::tellChildrenHandleMouseRelease(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		mousepos.x -= frame.x;
		mousepos.y -= frame.y;
		
		ScreenElement* handler = nullptr;
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			ScreenElement* child = childElements.get(i);
			if(handler==nullptr)
			{
				handler = child->handleMouseRelease(appData, mouseIndex, button, mousepos);
			}
			else
			{
				child->elementHandledMouseRelease(appData, mouseIndex, button, mousepos, handler);
			}
		}
		return handler;
	}
	void ScreenElement::tellChildrenElementHandledMouseRelease(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos, ScreenElement* element)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		mousepos.x -= frame.x;
		mousepos.y -= frame.y;
		
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->elementHandledMouseRelease(appData, mouseIndex, button, mousepos, element);
		}
	}
	
	void ScreenElement::tellChildrenHandleMouseDisconnect(ApplicationData appData, unsigned int mouseIndex)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);

		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->handleMouseDisconnect(appData, mouseIndex);
		}
	}
	
	
	ScreenElement* ScreenElement::tellChildrenHandleTouchMove(ApplicationData appData, unsigned int touchID, Vector2d touchpos)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		touchpos.x -= frame.x;
		touchpos.y -= frame.y;
		
		ScreenElement* handler = nullptr;
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			ScreenElement* child = childElements.get(i);
			if(handler==nullptr)
			{
				handler = child->handleTouchMove(appData, touchID, touchpos);
			}
			else
			{
				child->elementHandledTouchMove(appData, touchID, touchpos, handler);
			}
		}
		return handler;
	}
	void ScreenElement::tellChildrenElementHandledTouchMove(ApplicationData appData, unsigned int touchID, Vector2d touchpos, ScreenElement* element)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		touchpos.x -= frame.x;
		touchpos.y -= frame.y;
		
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->elementHandledTouchMove(appData, touchID, touchpos, element);
		}
	}
	
	ScreenElement* ScreenElement::tellChildrenHandleTouchBegin(ApplicationData appData, unsigned int touchID, Vector2d touchpos)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		touchpos.x -= frame.x;
		touchpos.y -= frame.y;
		
		ScreenElement* handler = nullptr;
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			ScreenElement* child = childElements.get(i);
			if(handler==nullptr)
			{
				handler = child->handleTouchBegin(appData, touchID, touchpos);
			}
			else
			{
				child->elementHandledTouchBegin(appData, touchID, touchpos, handler);
			}
		}
		return handler;
	}
	void ScreenElement::tellChildrenElementHandledTouchBegin(ApplicationData appData, unsigned int touchID, Vector2d touchpos, ScreenElement* element)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		touchpos.x -= frame.x;
		touchpos.y -= frame.y;
		
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->elementHandledTouchBegin(appData, touchID, touchpos, element);
		}
	}
	
	ScreenElement* ScreenElement::tellChildrenHandleTouchEnd(ApplicationData appData, unsigned int touchID, Vector2d touchpos)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		touchpos.x -= frame.x;
		touchpos.y -= frame.y;
		
		ScreenElement* handler = nullptr;
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			ScreenElement* child = childElements.get(i);
			if(handler==nullptr)
			{
				handler = child->handleTouchEnd(appData, touchID, touchpos);
			}
			else
			{
				child->elementHandledTouchEnd(appData, touchID, touchpos, handler);
			}
		}
		return handler;
	}
	void ScreenElement::tellChildrenElementHandledTouchEnd(ApplicationData appData, unsigned int touchID, Vector2d touchpos, ScreenElement* element)
	{
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		touchpos.x -= frame.x;
		touchpos.y -= frame.y;
		
		for(size_t i=(childElements.size()-1); i!=SIZE_MAX; i--)
		{
			childElements.get(i)->elementHandledTouchEnd(appData, touchID, touchpos, element);
		}
	}
}