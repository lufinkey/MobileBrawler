
#include "Application.h"
#include "../Utilities/PlatformChecks.h"
#include "../Utilities/Thread.h"
#include <SDL.h>
#include <ctime>
#include <mutex>

namespace GameLibrary
{
	void ApplicationEventHandler(void*userdata, unsigned int eventtype);
	int ApplicationEventFilter(void*userdata, SDL_Event*event);

	Application::Application()
	{
		window = nullptr;
		app_running = false;

		unsigned int flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS;
		if(!SDL_WasInit(flags))
		{
			if(SDL_Init(flags) != 0)
			{
				//TODO replace with more specific exception type
				throw Exception(SDL_GetError());
			}
		}

		listenermutex = (void*)(new std::mutex());

		window = new Window();
	}

	Application::~Application()
	{
		delete window;
		delete ((std::mutex*)listenermutex);
	}

	void Application::initialize()
	{
		//
	}

	void Application::loadContent()
	{
		//
	}

	void Application::unloadContent()
	{
		//
	}

	void Application::update(const ApplicationData&appData)
	{
		//
	}

	void Application::draw(const ApplicationData&appData, Graphics&g)
	{
		//
	}

	void Application::run(const WindowSettings&windowSettings, byte orientations, bool borderless)
	{
		std::srand((unsigned int)std::time(nullptr));

		if(!Thread::isMainThread() || app_running)
		{
			return;
		}

		app_running = true;

		//window creation
		{
			Rectangle displayRect = Window::getDisplayBounds(0);

			unsigned int bigger;
			unsigned int smaller;
				
			if(displayRect.width > displayRect.height)
			{
				bigger = displayRect.width;
				smaller = displayRect.height;
			}
			else
			{
				bigger = displayRect.height;
				smaller = displayRect.width;
			}

			WindowSettings settings = windowSettings;
			#if TARGETPLATFORM_MOBILE
				settings.setPosition(Vector2i(0,0));
				if(((orientations & ORIENTATION_PORTRAIT) == ORIENTATION_PORTRAIT)
				|| ((orientations & ORIENTATION_PORTRAITUPSIDEDOWN) == ORIENTATION_PORTRAITUPSIDEDOWN)
				|| (orientations == ORIENTATION_ALL))
				{
					windowSettings.setSize(Vector2u(smaller,bigger));
				}
				else
				{
					windowSettings.setSize(Vector2u(bigger,smaller));
				}
			#endif

			ArrayList<String> hints;
			if(orientations == ORIENTATION_ALL)
			{
				hints.add("Portrait");
				hints.add("PortraitUpsideDown");
				hints.add("LandscapeLeft");
				hints.add("LandscapeRight");
			}
			else
			{
				if((orientations & ORIENTATION_PORTRAIT) == ORIENTATION_PORTRAIT)
				{
					hints.add("Portrait");
				}
				if((orientations & ORIENTATION_PORTRAITUPSIDEDOWN) == ORIENTATION_PORTRAITUPSIDEDOWN)
				{
					hints.add("PortraitUpsideDown");
				}
				if((orientations & ORIENTATION_LANDSCAPELEFT) == ORIENTATION_LANDSCAPELEFT)
				{
					hints.add("LandscapeLeft");
				}
				if((orientations & ORIENTATION_LANDSCAPERIGHT) == ORIENTATION_LANDSCAPERIGHT)
				{
					hints.add("LandscapeRight");
				}
			}

			String hintString;
			for(unsigned int i=0; i<hints.size(); i++)
			{
				hintString += hints.get(i);
				if(i != (hints.size() - 1))
				{
					hintString += ' ';
				}
			}
			SDL_SetHintWithPriority("SDL_HINT_ORIENTATIONS", hintString, SDL_HINT_OVERRIDE);
			SDL_SetEventFilter(&ApplicationEventFilter, this);

			window->create(settings);
		}

		initialize();

		//application refresh loop
		while(app_running)
		{
			TimeInterval apptime;
			apptime.start();

			//TODO add game loop logic
		}
	}

	void Application::callListenerEvent(unsigned int eventtype)
	{
		((std::mutex*)listenermutex)->lock();
		ArrayList<ApplicationEventListener*> listeners = eventListeners;
		((std::mutex*)listenermutex)->unlock();

		for(unsigned int i=0; i<listeners.size(); i++)
		{
			ApplicationEventListener* listener = listeners.get(i);

			switch(eventtype)
			{
				case SDL_APP_WILLENTERBACKGROUND:
				listener->onApplicationWillEnterBackground(this);
				break;

				case SDL_APP_DIDENTERBACKGROUND:
				listener->onApplicationDidEnterBackground(this);
				break;

				case SDL_APP_WILLENTERFOREGROUND:
				listener->onApplicationWillEnterForeground(this);
				break;

				case SDL_APP_DIDENTERFOREGROUND:
				listener->onApplicationDidEnterForeground(this);
				break;

				case SDL_APP_LOWMEMORY:
				listener->onApplicationLowMemory(this);
				break;
				
				case SDL_APP_TERMINATING:
				listener->onApplicationTerminating(this);
				break;
			}
		}
	}

	int ApplicationEventFilter(void*userdata, SDL_Event*event)
	{
		ApplicationEventHandler(userdata, event->type);
		return 1;
	}

	void ApplicationEventHandler(void*userdata, unsigned int eventtype)
	{
		Application*application = (Application*)userdata;
		switch(eventtype)
		{
			case SDL_APP_WILLENTERBACKGROUND:
			break;

			case SDL_APP_DIDENTERBACKGROUND:
			break;

			case SDL_APP_WILLENTERFOREGROUND:
			break;

			case SDL_APP_DIDENTERFOREGROUND:
			break;

			case SDL_APP_LOWMEMORY:
			break;
			
			case SDL_APP_TERMINATING:
			break;
		}
		application->callListenerEvent(eventtype);
	}
}