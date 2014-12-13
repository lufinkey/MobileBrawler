
#include "ScreenManager.h"
#include "Transition/SlideTransition.h"

namespace GameLibrary
{
	const Transition* const ScreenManager::defaultPushTransition = new SlideTransition(SlideTransition::SLIDE_LEFT);

	ScreenManager::ScreenManager(Window*window, Screen*rootScreen) : Screen(window)
	{
		if(rootScreen == nullptr)
		{
			//TODO replace with more specific exception type
			throw IllegalArgumentException("Cannot construct a ScreenManager with a null root Screen");
		}
		TransitionData_clear(pushpopData);
		screens.add(rootScreen);
	}

	ScreenManager::ScreenManager(Screen*rootScreen) : ScreenManager(nullptr, rootScreen)
	{
		//
	}

	ScreenManager::~ScreenManager()
	{
		//
	}

	void ScreenManager::willAppear(const Transition*transition)
	{
		Screen::willAppear(transition);
		if(pushpopData.action!=TRANSITION_NONE)
		{
			screens.get(screens.size()-1)->willAppear(transition);
		}
	}

	void ScreenManager::didAppear(const Transition*transition)
	{
		Screen::didAppear(transition);
		if(pushpopData.action!=TRANSITION_NONE)
		{
			screens.get(screens.size()-1)->didAppear(transition);
		}
	}

	void ScreenManager::willDisappear(const Transition*transition)
	{
		Screen::willDisappear(transition);
		screens.get(screens.size()-1)->willDisappear(transition);
	}

	void ScreenManager::didDisappear(const Transition*transition)
	{
		Screen::didDisappear(transition);
		screens.get(screens.size()-1)->didDisappear(transition);
	}

	void ScreenManager::update(ApplicationData appData)
	{
		Screen* updateCaller = nullptr;
		Screen* pushpop_didDisappearCaller = nullptr;
		Screen* pushpop_didAppearCaller = nullptr;

		TransitionData_checkFinished(appData, pushpopData, &pushpop_didDisappearCaller, &pushpop_didAppearCaller);

		if(childScreen==nullptr)
		{
			if(pushpopData.action==TRANSITION_NONE)
			{
				updateCaller = screens.get(screens.size()-1);
			}
			TransitionData_callVirtualFunctions(pushpopData, pushpop_didDisappearCaller, pushpop_didAppearCaller);
		}

		if(updateCaller != nullptr)
		{
			updateCaller->update(appData);
		}

		Screen::update(appData);

		TransitionData_checkInitialization(appData, pushpopData);
	}

	void ScreenManager::drawScreens(ApplicationData&appData, Graphics&graphics) const
	{
		if(childScreen==nullptr || overlayData.action!=TRANSITION_NONE)
		{
			if(pushpopData.action == TRANSITION_NONE)
			{
				screens.get(screens.size()-1)->draw(appData, graphics);
			}
			else
			{
				float progress = pushpopData.progress;

				if(pushpopData.action == TRANSITION_HIDE)
				{
					progress = 1 - progress;
				}

				pushpopData.transition->draw(appData, graphics, progress, pushpopData.screen, pushpopData.transitionScreen);
			}
		}
	}

	void ScreenManager::draw(ApplicationData appData, Graphics graphics) const
	{
		if(overlayData.action==TRANSITION_NONE)
		{
			graphics.translate(x, y);
			drawBackground(appData, graphics);
			drawScreens(appData, graphics);
			drawElements(appData, graphics);
			drawOverlay(appData, graphics);
		}
		else if(drawingOverlayTransition)
		{
			drawBackground(appData, graphics);
			drawScreens(appData, graphics);
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

	void ScreenManager::set(const ArrayList<Screen*>& newScreens, const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(pushpopData.action != TRANSITION_NONE)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot set a ScreenManager's screens while the ScreenManager is performing a transition");
		}
		else if(newScreens.size()==0)
		{
			//TODO replace with more specific exception type
			throw IllegalArgumentException("Cannot set a ScreenManager with no Screens. A ScreenManager must have atleast 1 Screen");
		}
		else
		{
			for(unsigned int i=0; i<newScreens.size(); i++)
			{
				Screen* screen = newScreens.get(i);
				if(screen == nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot set a ScreenManager with a null Screen");
				}
				else if(screen->screenManager != nullptr && screen->screenManager!=this)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot set a ScreenManager with a Screen that is already a part of another ScreenManager");
				}
				else if(screen->parentScreen != nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot set a ScreenManager with a Screen that is already presented on another Screen");
				}
				else if(screen->parentElement != nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot set a ScreenManager with a Screen that is already added to a ScreenElement");
				}
				else
				{
					for(unsigned int j=(i+1); j<newScreens.size(); j++)
					{
						Screen* screen2 = newScreens.get(j);
						if(screen == screen2)
						{
							//TODO replace with more specific exception type
							throw Exception("Cannot set a ScreenManager with a list of Screens that contain duplicates");
						}
					}
				}
			}

			Screen* lastNewScreen = newScreens.get(newScreens.size()-1);
			Screen* currentScreen = screens.get(screens.size() - 1);
			if(lastNewScreen == currentScreen)
			{
				for(unsigned int i=0; i<screens.size(); i++)
				{
					screens.get(i)->screenManager = nullptr;
					screens.get(i)->parentElement = nullptr;
				}
				screens = newScreens;
				for(unsigned int i=0; i<screens.size(); i++)
				{
					screens.get(i)->screenManager = this;
					screens.get(i)->parentElement = this;
				}

				if(completion != nullptr)
				{
					completion((void*)this);
				}
			}
			else
			{
				Screen* topOldScreen = currentScreen->getTopScreen();
				Screen* topNewScreen = lastNewScreen->getTopScreen();
				bool visible = isVisible();
				if(screens.contains(lastNewScreen))
				{
					//pop animation
					TransitionData_begin(pushpopData, lastNewScreen, currentScreen, TRANSITION_HIDE, transition, duration, completion, (void*)this);
				}
				else
				{
					//push animation
					TransitionData_begin(pushpopData, currentScreen, lastNewScreen, TRANSITION_SHOW, transition, duration, completion, (void*)this);
				}
				for(unsigned int i=0; i<screens.size(); i++)
				{
					screens.get(i)->screenManager = nullptr;
					screens.get(i)->parentElement = nullptr;
				}
				screens = newScreens;
				for(unsigned int i=0; i<screens.size(); i++)
				{
					screens.get(i)->screenManager = this;
					screens.get(i)->parentElement = this;
				}

				if(transition == nullptr || duration == 0)
				{
					if(visible)
					{
						topOldScreen->willDisappear(transition);
						topNewScreen->willAppear(transition);

						TransitionData_clear(pushpopData);

						topOldScreen->didDisappear(transition);
						topNewScreen->didAppear(transition);

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
						topOldScreen->willDisappear(transition);
						topNewScreen->willAppear(transition);
					}
				}
			}
		}
	}

	void ScreenManager::push(Screen*screen, const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		ArrayList<Screen*> screens(1);
		screens.set(0, screen);
		push(screens, transition, duration, completion);
	}

	void ScreenManager::push(const ArrayList<Screen*>& newScreens, const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(pushpopData.action != TRANSITION_NONE)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot push Screens on a ScreenManager while the ScreenManager is performing a transition");
		}
		else if(newScreens.size()==0)
		{
			//TODO replace with more specific exception type
			throw IllegalArgumentException("Cannot push an empty Screen list onto a ScreenManager");
		}
		else
		{
			for(unsigned int i=0; i<newScreens.size(); i++)
			{
				Screen* screen = newScreens.get(i);
				if(screen == nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot push a null Screen onto ScreenManager");
				}
				else if(screen->screenManager != nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot push a Screen that is already a part of a ScreenManager");
				}
				else if(screen->parentScreen != nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot push a Screen that is already presented on another Screen");
				}
				else if(screen->parentElement != nullptr)
				{
					//TODO replace with more specific exception type
					throw Exception("Cannot push a Screen that is already added to a ScreenElement");
				}
				else
				{
					for(unsigned int j=(i+1); j<newScreens.size(); j++)
					{
						Screen* screen2 = newScreens.get(j);
						if(screen == screen2)
						{
							//TODO replace with more specific exception type
							throw Exception("Cannot push a list of Screens contining duplicates");
						}
					}
				}
			}

			Screen* lastNewScreen = newScreens.get(newScreens.size()-1);
			Screen* currentScreen = screens.get(screens.size() - 1);

			Screen* topOldScreen = currentScreen->getTopScreen();
			Screen* topNewScreen = lastNewScreen->getTopScreen();

			bool visible = isVisible();
			TransitionData_begin(pushpopData, currentScreen, lastNewScreen, TRANSITION_SHOW, transition, duration, completion, (void*)this);
			for(unsigned int i=0; i<newScreens.size(); i++)
			{
				Screen* screen = newScreens.get(i);
				screen->screenManager = this;
				screen->parentElement = this;
				screens.add(screen);
			}
			if(transition == nullptr || duration == 0)
			{
				if(visible)
				{
					topOldScreen->willDisappear(transition);
					topNewScreen->willAppear(transition);

					TransitionData_clear(pushpopData);

					topOldScreen->didDisappear(transition);
					topNewScreen->didAppear(transition);

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
					topOldScreen->willDisappear(transition);
					topNewScreen->willAppear(transition);
				}
			}
		}
	}

	Screen* ScreenManager::pop(const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(pushpopData.action != TRANSITION_NONE)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot pop a Screen on a ScreenManager while the ScreenManager is performing a transition");
		}
		else if(screens.size() == 1)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot pop any more Screens from ScreenManager; A ScreenManager must have atleast 1 Screen");
		}
		else
		{
			return popTo(screens.get(screens.size()-2), transition, duration, completion).get(0);
		}
	}
	
	ArrayList<Screen*> ScreenManager::popTo(Screen*screen, const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(pushpopData.action != TRANSITION_NONE)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot pop a Screen on a ScreenManager while the ScreenManager is performing a transition");
		}
		else if(screen == screens.get(screens.size() - 1))
		{
			return ArrayList<Screen*>();
		}
		else
		{
			unsigned int index = screens.indexOf(screen);
			if(index == ARRAYLIST_NOTFOUND)
			{
				//TODO replace with more specific exception type
				throw IllegalArgumentException("Screen to pop to is not contained within the ScreenManager");
			}

			ArrayList<Screen*> popped;
			for(unsigned int i=(index+1); i<screens.size(); i++)
			{
				Screen* screen = screens.get(i);
				screen->parentElement = nullptr;
				screen->screenManager = nullptr;
				popped.add(screen);
			}
			while(screens.size()>(index + 1))
			{
				screens.remove(screens.size()-1);
			}

			Screen* newScreen = screen;
			Screen* currentScreen = screens.get(screens.size()-1);

			Screen* topOldScreen = currentScreen->getTopScreen();
			Screen* topNewScreen = newScreen->getTopScreen();

			bool visible = isVisible();
			TransitionData_begin(pushpopData, newScreen, currentScreen, TRANSITION_HIDE, transition, duration, completion, (void*)this);

			if(transition == nullptr || duration == 0)
			{
				if(visible)
				{
					topOldScreen->willDisappear(transition);
					topNewScreen->willAppear(transition);

					TransitionData_clear(pushpopData);

					topOldScreen->didDisappear(transition);
					topNewScreen->didAppear(transition);

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
					topOldScreen->willDisappear(transition);
					topNewScreen->willAppear(transition);
				}
			}

			return popped;
		}
	}

	ArrayList<Screen*> ScreenManager::popToRoot(const Transition*transition, unsigned long long duration, CompletionCallback completion)
	{
		if(pushpopData.action != TRANSITION_NONE)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot pop a Screen on a ScreenManager while the ScreenManager is performing a transition");
		}
		else
		{
			return popTo(screens.get(0), transition, duration, completion);
		}
	}
}