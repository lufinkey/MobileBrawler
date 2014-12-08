
#include "ApplicationData.h"
#include "../Graphics/Graphics.h"
#include "../Utilities/ArrayList.h"
#include "../Window/Window.h"

#pragma once

namespace GameLibrary
{
	class ApplicationEventListener;

	class Application
	{
		friend void ApplicationEventHandler(void*, unsigned int);
	private:
		Window* window;
		ArrayList<ApplicationEventListener*> eventListeners;
		void* listenermutex;

		bool app_running;
		
		void callListenerEvent(unsigned int eventType);

	public:
		enum Orientation : byte
		{
			ORIENTATION_ALL = 0x00,
			ORIENTATION_LANDSCAPELEFT = 0x01,
			ORIENTATION_LANDSCAPERIGHT = 0x02,
			ORIENTATION_PORTRAIT = 0x04,
			ORIENTATION_PORTRAITUPSIDEDOWN = 0x08,
			ORIENTATION_LANDSCAPE = 0x01 | 0x02,
		};

		Application();
		virtual ~Application();

		virtual void initialize();
		virtual void loadContent();
		virtual void unloadContent();
		virtual void update(const ApplicationData&appData);
		virtual void draw(const ApplicationData&appData, Graphics&g);

		void run(const WindowSettings&windowSettings, byte orientations = ORIENTATION_ALL, bool borderless = false);

	};

	class ApplicationEventListener
	{
	public:
		virtual ~ApplicationEventListener();
		virtual void onApplicationWillEnterBackground(Application*application);
		virtual void onApplicationDidEnterBackground(Application*application);
		virtual void onApplicationWillEnterForeground(Application*application);
		virtual void onApplicationDidEnterForeground(Application*application);
		virtual void onApplicationTerminating(Application*application);
		virtual void onApplicationLowMemory(Application*application);
	};
}