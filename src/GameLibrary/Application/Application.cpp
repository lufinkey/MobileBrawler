
#include "Application.h"
#include "EventManager.h"
#include "../Utilities/PlatformChecks.h"
#include "../Utilities/Thread.h"
#include <SDL.h>
#include <ctime>

namespace GameLibrary
{
	void ApplicationEventHandler(void*userdata, unsigned int eventtype);
	int ApplicationEventFilter(void*userdata, SDL_Event*event);

	Application::Application()
	{
		window = nullptr;
		app_running = false;
		app_closing = false;
		exitcode = EXITCODE_SUCCESS;
		fps = 30;
		sleeptime = 33;

		unsigned int flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS;
		if(!SDL_WasInit(flags))
		{
			if(SDL_Init(flags) != 0)
			{
				//TODO replace with more specific exception type
				throw Exception(SDL_GetError());
			}
		}

		window = new Window();
	}

	Application::~Application()
	{
		delete window;
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

	int Application::run(const WindowSettings&windowSettings, byte orientations)
	{
		std::srand((unsigned int)std::time(nullptr));

		if(!Thread::isMainThread())
		{
			return EXITCODE_NOTMAINTHREAD;
		}
		else if(app_running)
		{
			return EXITCODE_ALREADYRUNNING;
		}

		app_running = true;

		apptime.reset();

		//window creation
		exitcode = loadMainWindow(windowSettings, orientations);

		if(!app_closing)
		{
			initialize();
		}

		if(!app_closing)
		{
			//application refresh loop
			exitcode = runMainLoop();
		}

		app_running = false;
		app_closing = false;
		return exitcode;
	}

	void Application::close(int code)
	{
		exitcode = code;
		app_closing = true;
	}

	int Application::loadMainWindow(const WindowSettings&windowSettings, byte orientations)
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

		return exitcode;
	}

	int Application::runMainLoop()
	{
		loadContent();

		if(!app_closing) //makes sure Application::close(int) hasn't been called
		{
			window->getGraphics()->reset();
		}

		apptime.start();

		while(app_running && !app_closing)
		{
			long long startFrameTime = apptime.getMilliseconds();

			EventManager::update(this);

			ApplicationData appdata(this,window,apptime);
			if(!app_closing)
			{
				update(appdata);
			}
			if(!app_closing)
			{
				draw(appdata, *(window->getGraphics()));
			}
			if(!app_closing)
			{
				window->update();

				long long endFrameTime = apptime.getMilliseconds();
				unsigned long long totalFrameTime = (unsigned long long)(endFrameTime - startFrameTime);
				if(totalFrameTime > sleeptime || sleeptime==0)
				{
					Thread::sleep(1);
				}
				else
				{
					unsigned long long adjustedSleepTime = sleeptime - totalFrameTime;
					Thread::sleep(adjustedSleepTime);
				}
			}
		}

		apptime.stop();

		unloadContent();

		window->destroy();

		return exitcode;
	}

	void Application::setFPS(unsigned int framerate)
	{
		fps = framerate;
		if(fps==0)
		{
			sleeptime = 1;
		}
		else
		{
			sleeptime = (unsigned long long)(1000/fps);
		}
	}

	unsigned int Application::getFPS()
	{
		return fps;
	}

	Window* Application::getWindow()
	{
		return window;
	}

	TimeInterval& Application::getTime()
	{
		return apptime;
	}

	void Application::callListenerEvent(unsigned int eventtype)
	{
		listenermutex.lock();
		ArrayList<ApplicationEventListener*> listeners = eventListeners;
		listenermutex.unlock();

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