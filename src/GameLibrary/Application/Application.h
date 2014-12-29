
#include "ApplicationData.h"
#include "../Exception/InitializeLibraryException.h"
#include "../Graphics/Graphics.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/PlatformChecks.h"
#include "../Utilities/Time/TimeInterval.h"
#include "../Window/Window.h"
#include <mutex>

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
		std::mutex listenermutex;

		TimeInterval apptime;

		unsigned int fps;
		unsigned long long sleeptime;

		int exitcode;

		bool app_running;
		bool app_closing;
		
		void callListenerEvent(unsigned int eventType);

		int loadMainWindow(const WindowSettings&windowSettings, int orientations);
		int runMainLoop();

	public:
		enum Orientation
		{
			ORIENTATION_ALL = 0x00,
			ORIENTATION_LANDSCAPELEFT = 0x01,
			ORIENTATION_LANDSCAPERIGHT = 0x02,
			ORIENTATION_PORTRAIT = 0x04,
			ORIENTATION_PORTRAITUPSIDEDOWN = 0x08,
			ORIENTATION_LANDSCAPE = 0x01 | 0x02,
		};

		enum ExitCode
		{
			EXITCODE_ALREADYRUNNING = 1,
			EXITCODE_SUCCESS = 0,
			EXITCODE_ERROR = -1,
			EXITCODE_FATALERROR = -2,
			EXITCODE_NOTMAINTHREAD = -3,
		};

		Application();
		virtual ~Application();

		virtual void initialize();
		virtual void loadContent(AssetManager*assetManager);
		virtual void unloadContent(AssetManager*assetManager);
		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics g) const;

#if TARGETPLATFORM_MOBILE
		int run(const WindowSettings&windowSettings = Window::defaultMobileSettings, int orientations = ORIENTATION_ALL);
#else
		int run(const WindowSettings&windowSettings = Window::defaultDesktopSettings, int orientations = ORIENTATION_ALL);
#endif

		void close(int exitcode);

		void setFPS(unsigned int fps);
		unsigned int getFPS();
		Window* getWindow();
		TimeInterval& getTime();
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