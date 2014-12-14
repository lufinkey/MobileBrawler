
#include "Screen.h"
#include "ScreenManager.h"
#include "Transition/PopoverTransition.h"

namespace GameLibrary
{
	const Transition* const Screen::defaultPresentTransition = new PopoverTransition(PopoverTransition::POPOVER_UP);

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

	void Screen::TransitionData_begin(TransitionData&data, Screen*screen, Screen*transitionScreen, byte action, const Transition*transition, unsigned long long duration, CompletionCallback completion, void*caller)
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

	void Screen::TransitionData_checkFinished(ApplicationData& appData, Screen::TransitionData&data, Screen**didDisappearCaller, Screen**didAppearCaller)
	{
		//apply any progress to the presenting transition
		byte finishedAction = TransitionData_applyProgress(appData, data);
		if(finishedAction == TRANSITION_HIDE)
		{
			*didDisappearCaller = data.transitionScreen;
			*didAppearCaller = data.screen;
		}
		else if(finishedAction == TRANSITION_SHOW)
		{
			*didDisappearCaller = data.screen;
			*didAppearCaller = data.transitionScreen;
		}
	}

	void Screen::TransitionData_callVirtualFunctions(TransitionData&data, Screen*didDisappearCaller, Screen*didAppearCaller)
	{
		if(didDisappearCaller!=nullptr || didAppearCaller!=nullptr)
		{
			const Transition* transition = data.transition;
			CompletionCallback completion = data.completion;
			void* caller = data.caller;
			TransitionData_clear(data);
			if(didDisappearCaller!=nullptr && !didDisappearCaller->isVisible())
			{
				didDisappearCaller->getTopScreen()->didDisappear(transition);
			}
			if(didAppearCaller!=nullptr && didAppearCaller->isVisible())
			{
				didAppearCaller->getTopScreen()->didAppear(transition);
			}
			if(completion != nullptr)
			{
				completion(caller);
			}
		}
	}

	Screen::Screen(Window*wndw)
	{
		screenManager = nullptr;
		parentScreen = nullptr;
		childScreen = nullptr;
		drawingOverlayTransition = false;

		TransitionData_clear(overlayData);

		setWindow(wndw);
	}

	Screen::Screen() : Screen(nullptr)
	{
		//
	}

	Screen::~Screen()
	{
		if(childScreen!=nullptr)
		{
			childScreen->parentElement = nullptr;
			childScreen->parentScreen = nullptr;
			childScreen = nullptr;
		}
	}

	void Screen::willAppear(const Transition*transition)
	{
		//
	}

	void Screen::didAppear(const Transition*transition)
	{
		//
	}

	void Screen::willDisappear(const Transition*transition)
	{
		//
	}

	void Screen::didDisappear(const Transition*transition)
	{
		//
	}

	void Screen::update(ApplicationData appData)
	{
		Screen* updateCaller = nullptr;
		Screen* overlay_didDisappearCaller = nullptr;
		Screen* overlay_didAppearCaller = nullptr;

		TransitionData_checkFinished(appData, overlayData, &overlay_didDisappearCaller, &overlay_didAppearCaller);

		if(childScreen!=nullptr)
		{
			updateCaller = childScreen;
		}

		TransitionData_callVirtualFunctions(overlayData, overlay_didDisappearCaller, overlay_didAppearCaller);

		if(updateCaller != nullptr)
		{
			updateCaller->update(appData);
		}
		else
		{
			ScreenElement::update(appData);
		}

		TransitionData_checkInitialization(appData, overlayData);
	}

	void Screen::drawBackground(ApplicationData appData, Graphics graphics) const
	{
		if(childScreen == nullptr || overlayData.action != TRANSITION_NONE)
		{
			ScreenElement::drawBackground(appData, graphics);
		}
	}

	void Screen::drawElements(ApplicationData appData, Graphics graphics) const
	{
		if(childScreen == nullptr || overlayData.action != TRANSITION_NONE)
		{
			ScreenElement::drawElements(appData, graphics);
		}
	}

	void Screen::drawOverlay(ApplicationData appData, Graphics graphics) const
	{
		if(childScreen!=nullptr || overlayData.action!=TRANSITION_NONE)
		{
			if(overlayData.action == TRANSITION_NONE)
			{
				Vector2f size = getSize();
				Vector2f overlaySize = childScreen->getSize();
				float xOff = (overlaySize.x - size.x)/2;
				float yOff = (overlaySize.y - size.y)/2;
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
			graphics.translate(x, y);
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
			graphics.translate(x, y);
			drawingOverlayTransition = true;
			drawOverlay(appData, graphics);
			drawingOverlayTransition = false;
		}
	}

	Vector2f Screen::getSize() const
	{
		if(window != nullptr)
		{
			View*view = window->getView();
			if(view != nullptr)
			{
				return view->getSize();
			}
		}
		return size;
	}

	void Screen::present(Screen*screen, const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(screen == nullptr)
		{
			//TODO replace with more specific exception type
			throw IllegalArgumentException("Cannot present a null Screen");
		}
		else if(screen->parentScreen != nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot present Screen that is already presenting on another Screen");
		}
		else if(screen->parentElement != nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot present Screen that is already displaying on another ScreenElement");
		}
		else if(screen->screenManager != nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot present Screen that is already displaying in a ScreenManager");
		}
		else if(screen->window != nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot present Screen that already belongs to a Window");
		}
		else if(childScreen != nullptr)
		{
			//if(overlayData.action != TRANSITION_NONE)
			//{
				//TODO replace with more specific exception type
				throw Exception("Cannot present Screen on top of a screen that is currently presenting or dismissing");
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
			childScreen->parentElement = this;
			if(transition == nullptr || duration==0)
			{
				if(visible)
				{
					willDisappear(transition);
					topScreen->willAppear(transition);

					TransitionData_clear(overlayData);

					didDisappear(transition);
					topScreen->didAppear(transition);

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
					willDisappear(transition);
					topScreen->willAppear(transition);
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
				//TODO replace with more specific exception type
				throw Exception("Cannot dismiss a Screen that is not presenting another Screen, or being presented on another Screen");
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
				parentElement = nullptr;

				if(transition == nullptr || duration==0)
				{
					if(visible)
					{
						topScreen->willDisappear(transition);
						ownerScreen->willAppear(transition);

						TransitionData_clear(ownerScreen->overlayData);

						topScreen->didDisappear(transition);
						ownerScreen->didAppear(transition);

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
						topScreen->willDisappear(transition);
						ownerScreen->willAppear(transition);
					}
				}
			}
		}
		else if(overlayData.action==TRANSITION_HIDE)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot dismiss a Screen that is already dismissing");
		}
		else if(overlayData.action==TRANSITION_SHOW)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot dismiss a Screen that is in the transition of presenting");
		}
		else
		{
			Screen* topScreen = childScreen->getTopScreen();
			bool visible = topScreen->isVisible();
			TransitionData_begin(overlayData, this, childScreen, TRANSITION_HIDE, transition, duration, completion, (void*)this);
			childScreen->setWindow(nullptr);
			childScreen->parentScreen = nullptr;
			childScreen->parentElement = nullptr;
			childScreen = nullptr;

			if(transition == nullptr || duration==0)
			{
				if(visible)
				{
					topScreen->willDisappear(transition);
					willAppear(transition);

					TransitionData_clear(overlayData);

					topScreen->didDisappear(transition);
					didAppear(transition);

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
					topScreen->willDisappear(transition);
					willAppear(transition);
				}
			}
		}
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
				//TODO replace with more specific exception type
				throw Exception("Fatal error: Screen is not contained in its ScreenManager");
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

	void Screen::setWindow(Window*win)
	{
		window = win;
		if(window != nullptr)
		{
			View* view = win->getView();
			if(view != nullptr)
			{
				size = view->getSize();
			}
		}
		if(childScreen!=nullptr)
		{
			childScreen->setWindow(window);
		}
	}

	void Screen::setBackgroundColor(const Color&color)
	{
		ScreenElement::setBackgroundColor(color);
	}

	const Color& Screen::getBackgroundColor() const
	{
		return ScreenElement::getBackgroundColor();
	}
}