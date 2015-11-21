
#include "Screen.h"
#include "ScreenManager.h"
#include "Transition/PopoverTransition.h"

namespace GameLibrary
{
	const Transition* const Screen::defaultPresentTransition = new PopoverTransition(PopoverTransition::POPOVER_UP);
	
	void Screen::updateFrame(Window*window)
	{
		if(window != nullptr)
		{
			View*view = window->getView();
			Vector2d size;
			if(view != nullptr)
			{
				if(view->matchesWindow())
				{
					size = (Vector2d)window->getSize();
				}
				else
				{
					size = view->getSize();
				}
			}
			else
			{
				size = (Vector2d)window->getSize();
			}
			if(framesize.x!=size.x || framesize.y!=size.y)
			{
				RectangleD oldFrame(0, 0, framesize.x, framesize.y);
				RectangleD newFrame(0, 0, size.x, size.y);
				framesize = size; //setFrame(RectangleD(frame.x, frame.y, size.x, size.y));
				ScreenElement* mainElement = getElement();
				mainElement->setFrame(RectangleD(0,0,size.x,size.y));
				onFrameChange(oldFrame, newFrame);
			}
		}
	}
	
	void Screen::setWindow(Window*win)
	{
		if(window!=win)
		{
			if(window!=nullptr)
			{
				if(childScreen!=nullptr)
				{
					childScreen->setWindow(nullptr);
				}
				window = nullptr; //ScreenElement::setWindow(nullptr);
			}
			if(win != nullptr)
			{
				updateFrame(win);
				window = win; //ScreenElement::setWindow(win);
				if(childScreen!=nullptr)
				{
					childScreen->setWindow(win);
				}
			}
			updateFrame(win);
		}
	}
	
	void Screen::TransitionData_clear(Screen::TransitionData&data)
	{
		data.screen = nullptr;
		data.transitionScreen = nullptr;
		data.action = TRANSITION_NONE;
		data.requiresInitializing = false;
		data.startTime = 0;
		data.transition = nullptr;
		data.progress = 0;
		data.duration = 0;
		data.completion = nullptr;
		data.caller = nullptr;
	}
	
	void Screen::TransitionData_begin(TransitionData&data, Screen*screen, Screen*transitionScreen, TransitionAction action, const Transition*transition, unsigned long long duration, CompletionCallback completion, void*caller)
	{
		data.screen = screen;
		data.transitionScreen = transitionScreen;
		data.action = action;
		data.requiresInitializing = true;
		data.startTime = 0;
		data.transition = transition;
		data.progress = 0;
		data.duration = duration;
		data.completion = completion;
		data.caller = caller;
	}
	
	void Screen::TransitionData_checkInitialization(ApplicationData& appData, Screen::TransitionData&data)
	{
		if(data.requiresInitializing)
		{
			data.startTime = appData.getTime().getMilliseconds();
			data.requiresInitializing = false;
		}
	}
	
	byte Screen::TransitionData_applyProgress(ApplicationData& appData, Screen::TransitionData&data)
	{
		byte finishedAction = TRANSITION_NONE;
		if(data.action != TRANSITION_NONE)
		{
			TransitionData_checkInitialization(appData, data);
			long long currentTime = appData.getTime().getMilliseconds();
			long long timeDif = currentTime - data.startTime;
			data.progress = (double)(((double)timeDif) / ((double)data.duration));
			if(data.progress >= 1)
			{
				finishedAction = data.action;
			}
		}
		return finishedAction;
	}
	
	void Screen::TransitionData_checkFinished(ApplicationData& appData, Screen::TransitionData&data, Screen**onDidDisappearCaller, Screen**onDidAppearCaller)
	{
		//apply any progress to the presenting transition
		byte finishedAction = TransitionData_applyProgress(appData, data);
		if(finishedAction == TRANSITION_HIDE)
		{
			*onDidDisappearCaller = data.transitionScreen;
			*onDidAppearCaller = data.screen;
			TransitionData_clear(data);
		}
		else if(finishedAction == TRANSITION_SHOW)
		{
			*onDidDisappearCaller = data.screen;
			*onDidAppearCaller = data.transitionScreen;
			TransitionData_clear(data);
		}
	}
	
	void Screen::TransitionData_callVirtualFunctions(TransitionData&data, Screen*onDidDisappearCaller, Screen*onDidAppearCaller)
	{
		if(onDidDisappearCaller!=nullptr || onDidAppearCaller!=nullptr)
		{
			const Transition* transition = data.transition;
			CompletionCallback completion = data.completion;
			void* caller = data.caller;
			TransitionData_clear(data);
			if(onDidDisappearCaller!=nullptr && !onDidDisappearCaller->isOnTop())
			{
				onDidDisappearCaller->getTopScreen()->onDidDisappear(transition);
			}
			if(onDidAppearCaller!=nullptr && onDidAppearCaller->isOnTop())
			{
				onDidAppearCaller->getTopScreen()->onDidAppear(transition);
			}
			if(completion != nullptr)
			{
				completion(caller);
			}
		}
	}
	
	Screen::Screen(Window*wndw)
	{
		element = nullptr;
		screenManager = nullptr;
		parentScreen = nullptr;
		childScreen = nullptr;
		drawingOverlayTransition = false;
		isshown = false;
		backgroundColor = Color::TRANSPARENT;

		TransitionData_clear(overlayData);

		window = wndw;
		if(window != nullptr)
		{
			View*view = window->getView();
			if(view != nullptr)
			{
				const Vector2d& size = view->getSize();
				if(framesize.x!=size.x || framesize.y!=size.y)
				{
					framesize = size; //frame = RectangleD(frame.x, frame.y, size.x, size.y);
					ScreenElement* mainElement = getElement();
					mainElement->setFrame(RectangleD(0,0,size.x,size.y));
				}
			}
		}
	}
	
	Screen::Screen() : Screen(nullptr)
	{
		//
	}
	
	Screen::~Screen()
	{
		if(childScreen!=nullptr)
		{
			//childScreen->parentElement = nullptr;
			childScreen->parentScreen = nullptr;
			childScreen = nullptr;
		}
		if(element != nullptr)
		{
			delete element;
			element = nullptr;
		}
	}
	
	void Screen::onFrameChange(const RectangleD& oldFrame, const RectangleD& newFrame)
	{
		//Open for implementation
	}
	
	void Screen::onWillAppear(const Transition*transition)
	{
		//Open for implementation
	}
	
	void Screen::onDidAppear(const Transition*transition)
	{
		//Open for implementation
	}
	
	void Screen::onWillDisappear(const Transition*transition)
	{
		//Open for implementation
	}
	
	void Screen::onDidDisappear(const Transition*transition)
	{
		//Open for implementation
	}
	
	void Screen::update(ApplicationData appData)
	{
		if(!isshown)
		{
			isshown = true;
			if(window != nullptr && parentScreen == nullptr && screenManager == nullptr)
			{
				onWillAppear(nullptr);
				onDidAppear(nullptr);
			}
		}

		Screen* updateCaller = nullptr;
		Screen* overlay_onDidDisappearCaller = nullptr;
		Screen* overlay_onDidAppearCaller = nullptr;
		
		TransitionData_checkFinished(appData, overlayData, &overlay_onDidDisappearCaller, &overlay_onDidAppearCaller);
		
		if(childScreen!=nullptr)
		{
			updateCaller = childScreen;
		}
		
		updateFrame(window);
		
		TransitionData_callVirtualFunctions(overlayData, overlay_onDidDisappearCaller, overlay_onDidAppearCaller);
		
		updateFrame(window);
		
		if(updateCaller != nullptr)
		{
			updateCaller->update(appData);
		}
		else
		{
			if(element == nullptr)
			{
				getElement();
			}
			onUpdate(appData);
			if(Multitouch::isAvailable())
			{
				updateElementTouch(appData);
			}
			else
			{
				updateElementMouse(appData);
			}
			element->update(appData);
		}
		
		TransitionData_checkInitialization(appData, overlayData);
		
		updateFrame(window);
	}
	
	void Screen::onUpdate(ApplicationData appData)
	{
		//Open for implementation
	}
	
	void Screen::drawBackground(ApplicationData appData, Graphics graphics) const
	{
		if(childScreen == nullptr || overlayData.action != TRANSITION_NONE)
		{
			//ScreenElement::drawBackground(appData, graphics);
			if(!backgroundColor.equals(Color::TRANSPARENT))
			{
				RectangleD frame = getFrame();
				graphics.setColor(backgroundColor);
				graphics.fillRect(frame.x, frame.y, frame.width, frame.height);
			}
		}
	}
	
	void Screen::drawElements(ApplicationData appData, Graphics graphics) const
	{
		if(childScreen == nullptr || overlayData.action != TRANSITION_NONE)
		{
			if(element != nullptr)
			{
				element->draw(appData, graphics);
			}
			//ScreenElement::drawElements(appData, graphics);
			onDraw(appData, graphics);
		}
	}
	
	void Screen::drawOverlay(ApplicationData appData, Graphics graphics) const
	{
		if(childScreen!=nullptr || overlayData.action!=TRANSITION_NONE)
		{
			RectangleD frame = getFrame();
			graphics.translate(frame.x, frame.y);
			
			if(overlayData.action == TRANSITION_NONE)
			{
				RectangleD overlayFrame = childScreen->getFrame();
				double xOff = (overlayFrame.width - frame.width)/2;
				double yOff = (overlayFrame.height - frame.height)/2;
				graphics.translate(xOff, yOff);
				childScreen->draw(appData, graphics);
			}
			else
			{
				double progress = overlayData.progress;
				
				if(overlayData.action == TRANSITION_HIDE)
				{
					progress = 1 - progress;
				}
				
				overlayData.transition->draw(appData, graphics, progress, static_cast<Drawable*>(overlayData.screen), static_cast<Drawable*>(overlayData.transitionScreen));
			}
		}
	}
	
	void Screen::draw(ApplicationData appData, Graphics graphics) const
	{
		if(overlayData.action==TRANSITION_NONE)
		{
			drawBackground(appData, graphics);
			drawElements(appData, graphics);
			drawOverlay(appData, graphics);
		}
		else if(drawingOverlayTransition)
		{
			drawBackground(appData, graphics);
			drawElements(appData, graphics);
		}
		else
		{
			drawingOverlayTransition = true;
			drawOverlay(appData, graphics);
			drawingOverlayTransition = false;
		}
	}
	
	void Screen::onDraw(ApplicationData appData, Graphics graphics) const
	{
		//Open for implementation
	}
	
	RectangleD Screen::getFrame() const
	{
		return RectangleD(0,0,framesize.x,framesize.y);
	}
	
	void Screen::present(Screen*screen, const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(!isshown)
		{
			isshown = true;
			if(window != nullptr && parentScreen == nullptr && screenManager == nullptr)
			{
				onWillAppear(nullptr);
				onDidAppear(nullptr);
			}
		}
		
		if(screen == nullptr)
		{
			throw IllegalArgumentException("screen", "null");
		}
		else if(screen->parentScreen != nullptr)
		{
			throw IllegalArgumentException("screen", "already presenting on another Screen");
		}
		/*else if(screen->parentElement != nullptr)
		{
			throw IllegalArgumentException("screen", "already displaying on another ScreenElement");
		}*/
		else if(screen->screenManager != nullptr)
		{
			throw IllegalArgumentException("screen", "already displaying in a ScreenManager");
		}
		else if(screen->window != nullptr)
		{
			throw IllegalArgumentException("screen", "already belongs to a Window");
		}
		else if(childScreen != nullptr)
		{
			//if(overlayData.action != TRANSITION_NONE)
			//{
				throw ScreenNavigationException("Cannot present Screen on top of a screen that is currently presenting or dismissing");
			//}
			//childScreen->present(screen, transition, duration);
		}
		else
		{
			Screen* topScreen = screen->getTopScreen();
			bool visible = isOnTop();
			TransitionData_begin(overlayData, this, screen, TRANSITION_SHOW, transition, duration, completion, (void*)this);
			childScreen = screen;
			childScreen->setWindow(window);
			childScreen->parentScreen = this;
			//childScreen->parentElement = this;
			if(transition == nullptr || duration==0)
			{
				if(visible)
				{
					onWillDisappear(transition);
					topScreen->onWillAppear(transition);
					
					TransitionData_clear(overlayData);
					
					onDidDisappear(transition);
					topScreen->onDidAppear(transition);
					
					if(completion != nullptr)
					{
						completion((void*)this);
					}
				}
				else
				{
					TransitionData_clear(overlayData);
					
					if(completion != nullptr)
					{
						completion((void*)this);
					}
				}
			}
			else
			{
				if(visible)
				{
					onWillDisappear(transition);
					topScreen->onWillAppear(transition);
				}
			}
		}
	}
	
	void Screen::dismiss(const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(childScreen == nullptr)
		{
			if(parentScreen==nullptr)
			{
				throw ScreenNavigationException("Cannot dismiss a Screen that is not presenting another Screen, or being presented on another Screen");
			}
			else
			{
				Screen* topScreen = getTopScreen();
				Screen* ownerScreen = parentScreen;
				bool visible = topScreen->isOnTop();
				TransitionData_begin(ownerScreen->overlayData, ownerScreen, this, TRANSITION_HIDE, transition, duration, completion, (void*)this);
				ownerScreen->childScreen = nullptr;
				setWindow(nullptr);
				parentScreen = nullptr;
				//parentElement = nullptr;
				
				if(transition == nullptr || duration==0)
				{
					if(visible)
					{
						topScreen->onWillDisappear(transition);
						ownerScreen->onWillAppear(transition);
						
						TransitionData_clear(ownerScreen->overlayData);
						
						topScreen->onDidDisappear(transition);
						ownerScreen->onDidAppear(transition);
						
						if(completion != nullptr)
						{
							completion((void*)this);
						}
					}
					else
					{
						TransitionData_clear(ownerScreen->overlayData);
						
						if(completion != nullptr)
						{
							completion((void*)this);
						}
					}
				}
				else
				{
					if(visible)
					{
						topScreen->onWillDisappear(transition);
						ownerScreen->onWillAppear(transition);
					}
				}
			}
		}
		else if(overlayData.action==TRANSITION_HIDE)
		{
			throw ScreenNavigationException("Cannot dismiss a Screen that is already dismissing");
		}
		else if(overlayData.action==TRANSITION_SHOW)
		{
			throw ScreenNavigationException("Cannot dismiss a Screen that is in the transition of presenting");
		}
		else
		{
			Screen* topScreen = childScreen->getTopScreen();
			bool visible = topScreen->isOnTop();
			TransitionData_begin(overlayData, this, childScreen, TRANSITION_HIDE, transition, duration, completion, (void*)this);
			childScreen->setWindow(nullptr);
			childScreen->parentScreen = nullptr;
			//childScreen->parentElement = nullptr;
			childScreen = nullptr;
			
			if(transition == nullptr || duration==0)
			{
				if(visible)
				{
					topScreen->onWillDisappear(transition);
					onWillAppear(transition);
					
					TransitionData_clear(overlayData);
					
					topScreen->onDidDisappear(transition);
					onDidAppear(transition);
					
					if(completion != nullptr)
					{
						completion((void*)this);
					}
				}
				else
				{
					TransitionData_clear(overlayData);
					
					if(completion != nullptr)
					{
						completion((void*)this);
					}
				}
			}
			else
			{
				if(visible)
				{
					topScreen->onWillDisappear(transition);
					onWillAppear(transition);
				}
			}
		}
	}
	
	ScreenElement* Screen::getElement()
	{
		if(element == nullptr)
		{
			RectangleD screenFrame = getFrame();
			element = new ScreenElement(RectangleD(0,0, screenFrame.width, screenFrame.height));
		}
		return element;
	}
	
	ScreenManager* Screen::getScreenManager() const
	{
		return screenManager;
	}
	
	Screen* Screen::getParentScreen() const
	{
		return parentScreen;
	}
	
	Screen* Screen::getChildScreen() const
	{
		return childScreen;
	}
	
	Screen* Screen::getTopScreen()
	{
		if(childScreen == nullptr)
		{
			return this;
		}
		return childScreen->getTopScreen();
	}
	
	Screen* Screen::getBottomScreen()
	{
		if(parentScreen == nullptr)
		{
			return this;
		}
		return parentScreen->getBottomScreen();
	}
	
	Screen* Screen::getRootScreen()
	{
		Screen* bottomScreen = getBottomScreen();
		if(bottomScreen->screenManager == nullptr)
		{
			return bottomScreen;
		}
		return bottomScreen->screenManager->getRootScreen();
	}
	
	bool Screen::isOnTop()
	{
		if(childScreen!=nullptr)
		{
			return false;
		}
		else if(screenManager!=nullptr)
		{
			size_t index = screenManager->screens.indexOf(this);
			if(index == ARRAYLIST_NOTFOUND)
			{
				throw IllegalStateException("Screen is not contained in its ScreenManager");
			}
			else
			{
				if(index != (screenManager->screens.size() - 1))
				{
					return false;
				}
				return screenManager->isOnTop();
			}
		}
		else if(window != nullptr)
		{
			return true;
		}
		return false;
	}
	
	bool Screen::isPresenting() const
	{
		if(overlayData.action == TRANSITION_SHOW)
		{
			return true;
		}
		return false;
	}
	
	bool Screen::isDismissing() const
	{
		if(overlayData.action == TRANSITION_HIDE)
		{
			return true;
		}
		return false;
	}
	
	void Screen::setBackgroundColor(const Color&color)
	{
		backgroundColor = color; //ScreenElement::setBackgroundColor(color);
	}
	
	const Color& Screen::getBackgroundColor() const
	{
		return backgroundColor; //return ScreenElement::getBackgroundColor();
	}
	
#define MOUSEBUTTONS_COUNT 4
	
	size_t Screen::getTouchDataIndex(ArrayList<Screen::MouseTouchData>& touches, unsigned int touchID)
	{
		for(size_t touches_size=touches.size(), i=0; i<touches_size; i++)
		{
			if(touches[i].touchID==touchID)
			{
				return i;
			}
		}
		return SIZE_MAX;
	}
	
	ArrayList<unsigned int> Screen::getUnlistedTouchIDs(ArrayList<Screen::MouseTouchData>& touches, ArrayList<unsigned int>& touchIDs)
	{
		ArrayList<unsigned int> unlisted;
		for(size_t touches_size=touches.size(), i=0; i<touches_size; i++)
		{
			MouseTouchData& touchData = touches.get(i);
			bool found = false;
			for(size_t j=0; j<touchIDs.size(); j++)
			{
				if(touchIDs.get(i) == touchData.touchID)
				{
					found = true;
					j = touchIDs.size();
				}
			}

			if(!found)
			{
				unlisted.add(touchData.touchID);
			}
		}
		return unlisted;
	}
	
	void Screen::updateElementMouse(ApplicationData& appData)
	{
		Window* window = appData.getWindow();
		ScreenElement* element = getElement();
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		TransformD mouseTransform = appData.getTransform().getInverse();
		
		ArrayList<unsigned int> mouseIndexes;
		unsigned int mouseCount = Mouse::getTotalMouseInstances(window);
		mouseIndexes.resize((size_t)mouseCount);
		for(unsigned int i=0; i<mouseCount; i++)
		{
			mouseIndexes[i] = i;
		}
		
		ArrayList<unsigned int> unlistedIDs = getUnlistedTouchIDs(currentTouches, mouseIndexes);
		for(size_t unlistedIDs_size=unlistedIDs.size(), i=0; i<unlistedIDs_size; i++)
		{
			unsigned int touchID = unlistedIDs.get(i);
			size_t touch_index = getTouchDataIndex(currentTouches, touchID);
			if(touch_index!=SIZE_MAX)
			{
				MouseTouchData& touchData = currentTouches[touch_index];
				for(size_t j=1; j<MOUSEBUTTONS_COUNT; j++)
				{
					if(touchData.state[j])
					{
						element->handleMouseRelease(appData, touchData.touchID, (Mouse::Button)j, touchData.pos);
					}
				}
				element->handleMouseDisconnect(appData, touchData.touchID);
				currentTouches.remove(touch_index);
			}
		}
		
		for(size_t mouseIndexes_size=mouseIndexes.size(), i=0; i<mouseIndexes_size; i++)
		{
			unsigned int mouseIndex = mouseIndexes.get(i);
			size_t touch_index = getTouchDataIndex(currentTouches, mouseIndex);
			MouseTouchData* touchData_ptr = nullptr;
			if(touch_index==SIZE_MAX)
			{
				MouseTouchData touchData;
				touchData.touchID = mouseIndex;
				touchData.pos = mouseTransform.transform(Mouse::getPosition(window, mouseIndex));
				//TODO add mouse connect handler
				element->handleMouseMove(appData, touchData.touchID, touchData.pos);
				for(size_t j=0; j<MOUSEBUTTONS_COUNT; j++)
				{
					touchData.state[j] = Mouse::isButtonPressed(window, mouseIndex, (Mouse::Button)j);
					if(touchData.state[j] && j!=0)
					{
						element->handleMousePress(appData, touchData.touchID, (Mouse::Button)j, touchData.pos);
					}
				}
				currentTouches.add(touchData);
				touchData_ptr = &currentTouches[currentTouches.size()-1];
			}
			else
			{
				touchData_ptr = &currentTouches[touch_index];
				Vector2d mousepos = mouseTransform.transform(Mouse::getPosition(window, touchData_ptr->touchID));
				if(mousepos!=touchData_ptr->pos)
				{
					//mouse moved
					element->handleMouseMove(appData, touchData_ptr->touchID, mousepos);
				}
				touchData_ptr->pos = mousepos;
			}
			
			MouseTouchData& touchData = *touchData_ptr;
			
			for(size_t j=1; j<MOUSEBUTTONS_COUNT; j++)
			{
				bool state = Mouse::isButtonPressed(window, touchData.touchID, (Mouse::Button)j);
				if(touchData.state[j]!=state)
				{
					if(state)
					{
						element->handleMousePress(appData, touchData.touchID, (Mouse::Button)j, touchData.pos);
					}
					else
					{
						element->handleMouseRelease(appData, touchData.touchID, (Mouse::Button)j, touchData.pos);
					}
					touchData.state[j] = state;
				}
			}
		}
	}
	
	void Screen::updateElementTouch(ApplicationData& appData)
	{
		Window* window = appData.getWindow();
		ScreenElement* element = getElement();
		RectangleD frame = getFrame();
		appData.getTransform().translate(frame.x, frame.y);
		TransformD touchTransform = appData.getTransform().getInverse();

		ArrayList<unsigned int> touchIDs = Multitouch::getTouchIDs(window);

		ArrayList<unsigned int> unlistedIDs = getUnlistedTouchIDs(currentTouches, touchIDs);
		for(size_t unlistedIDs_size=unlistedIDs.size(), i=0; i<unlistedIDs_size; i++)
		{
			unsigned int touchID = unlistedIDs.get(i);
			size_t touch_index = getTouchDataIndex(currentTouches, touchID);
			if(touch_index!=SIZE_MAX)
			{
				MouseTouchData& touchData = currentTouches[touch_index];
				element->handleTouchEnd(appData, touchData.touchID, touchData.pos);
				currentTouches.remove(touch_index);
			}
		}
		
		for(size_t touchIDs_size=touchIDs.size(), i=0; i<touchIDs_size; i++)
		{
			unsigned int touchID = touchIDs.get(i);
			size_t touch_index = getTouchDataIndex(currentTouches, touchID);
			if(touch_index==SIZE_MAX)
			{
				MouseTouchData touchData;
				touchData.touchID = touchID;
				touchData.pos = touchTransform.transform(Multitouch::getPosition(window, touchID));
				for(size_t j=0; j<MOUSEBUTTONS_COUNT; j++)
				{
					touchData.state[j] = false;
				}
				touchData.state[Mouse::BUTTON_LEFT] = true; //for backwards compatibility
				element->handleTouchBegin(appData, touchData.touchID, touchData.pos);
				currentTouches.add(touchData);
			}
			else
			{
				MouseTouchData& touchData = currentTouches[touch_index];
				Vector2d touchpos = touchTransform.transform(Multitouch::getPosition(window, touchData.touchID));
				if(touchpos!=touchData.pos)
				{
					//touch moved
					element->handleTouchMove(appData, touchData.touchID, touchpos);
				}
				touchData.pos = touchpos;
			}
		}
	}
}
