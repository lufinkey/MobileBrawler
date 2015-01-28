
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
			if(view != nullptr)
			{
				const Vector2f& size = view->getSize();
				if(framesize.x!=size.x || framesize.y!=size.y)
				{
					framesize = size; //setFrame(RectangleF(frame.x, frame.y, size.x, size.y));
					ScreenElement* mainElement = getElement();
					mainElement->setFrame(RectangleF(0,0,size.x,size.y));
				}
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
		}
		else
		{
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
			data.progress = (float)(((double)timeDif) / ((double)data.duration));
			if(data.progress >= 1)
			{
				finishedAction = data.action;
				TransitionData_clear(data);
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
		}
		else if(finishedAction == TRANSITION_SHOW)
		{
			*onDidDisappearCaller = data.screen;
			*onDidAppearCaller = data.transitionScreen;
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
			if(onDidDisappearCaller!=nullptr && !onDidDisappearCaller->isVisible())
			{
				onDidDisappearCaller->getTopScreen()->onDidDisappear(transition);
			}
			if(onDidAppearCaller!=nullptr && onDidAppearCaller->isVisible())
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
				const Vector2f& size = view->getSize();
				if(framesize.x!=size.x || framesize.y!=size.y)
				{
					framesize = size; //frame = RectangleF(frame.x, frame.y, size.x, size.y);
					ScreenElement* mainElement = getElement();
					mainElement->setFrame(RectangleF(0,0,size.x,size.y));
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
	
	void Screen::onWillAppear(const Transition*transition)
	{
		//
	}
	
	void Screen::onDidAppear(const Transition*transition)
	{
		//
	}
	
	void Screen::onWillDisappear(const Transition*transition)
	{
		//
	}
	
	void Screen::onDidDisappear(const Transition*transition)
	{
		//
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
			element->update(appData);
			onUpdate(appData);
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
				RectangleF frame = getFrame();
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
			RectangleF frame = getFrame();
			graphics.translate(frame.x, frame.y);
			
			if(overlayData.action == TRANSITION_NONE)
			{
				RectangleF overlayFrame = childScreen->getFrame();
				float xOff = (overlayFrame.width - frame.width)/2;
				float yOff = (overlayFrame.height - frame.height)/2;
				graphics.translate(xOff, yOff);
				childScreen->draw(appData, graphics);
			}
			else
			{
				float progress = overlayData.progress;
				
				if(overlayData.action == TRANSITION_HIDE)
				{
					progress = 1 - progress;
				}
				
				overlayData.transition->draw(appData, graphics, progress, overlayData.screen, overlayData.transitionScreen);
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
	
	RectangleF Screen::getFrame() const
	{
		return RectangleF(0,0,framesize.x,framesize.y);
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
			throw IllegalArgumentException("Cannot present a null Screen");
		}
		else if(screen->parentScreen != nullptr)
		{
			throw IllegalArgumentException("Cannot present Screen that is already presenting on another Screen");
		}
		/*else if(screen->parentElement != nullptr)
		{
			throw IllegalArgumentException("Cannot present Screen that is already displaying on another ScreenElement");
		}*/
		else if(screen->screenManager != nullptr)
		{
			throw IllegalArgumentException("Cannot present Screen that is already displaying in a ScreenManager");
		}
		else if(screen->window != nullptr)
		{
			throw IllegalArgumentException("Cannot present Screen that already belongs to a Window");
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
			bool visible = isVisible();
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
				bool visible = topScreen->isVisible();
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
			bool visible = topScreen->isVisible();
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
			RectangleF screenFrame = getFrame();
			element = new ScreenElement(RectangleF(0,0, screenFrame.width, screenFrame.height));
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
	
	bool Screen::isVisible()
	{
		if(childScreen!=nullptr)
		{
			return false;
		}
		else if(screenManager!=nullptr)
		{
			unsigned int index = screenManager->screens.indexOf(this);
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
				else if(screenManager->pushpopData.action==TRANSITION_NONE)
				{
					return screenManager->isVisible();
				}
				return false;
			}
		}
		else if(parentScreen!=nullptr)
		{
			Screen* bottomScreen = getBottomScreen();
			return bottomScreen->isVisible();
		}
		else
		{
			if(window != nullptr)
			{
				return true;
			}
			return false;
		}
	}
	
	void Screen::setBackgroundColor(const Color&color)
	{
		backgroundColor = color; //ScreenElement::setBackgroundColor(color);
	}
	
	const Color& Screen::getBackgroundColor() const
	{
		return backgroundColor; //return ScreenElement::getBackgroundColor();
	}
}