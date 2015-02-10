
#pragma once

#include "ApplicationData.h"
#include "../Exception/InitializeLibraryException.h"
#include "../Graphics/Graphics.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/PlatformChecks.h"
#include "../Utilities/Time/TimeInterval.h"
#include "../Window/Window.h"
#include <mutex>

namespace GameLibrary
{
	class ApplicationEventListener;
	
	
	/*! Creates a Window object, and runs a refresh loop to redraw to the Window.*/
	class Application
	{
		friend void ApplicationEventHandler(void*, unsigned int);
	public:
		/*! The orientation the screen is be allowed to rotate on a mobile device.*/
		enum Orientation
		{
			/*! A bitmask value representing a mobile device rotated to the left.*/
			ORIENTATION_LANDSCAPELEFT = 0x01,
			/*! A bitmask value representing a mobile device rotated to the right.*/
			ORIENTATION_LANDSCAPERIGHT = 0x02,
			/*! A bitmask value representing a mobile device standing straight up and down.*/
			ORIENTATION_PORTRAIT = 0x04,
			/*! A bitmask value representing a mobile device rotated upside down.*/
			ORIENTATION_PORTRAITUPSIDEDOWN = 0x08,
			/*! A bitmask value representing a mobile device rotated to the left or rotated to the right.*/
			ORIENTATION_LANDSCAPE = ORIENTATION_LANDSCAPELEFT | ORIENTATION_LANDSCAPERIGHT,
			/*! A bitmask value representing a mobile device rotated in any direction.*/
			ORIENTATION_ALL = ORIENTATION_LANDSCAPELEFT | ORIENTATION_LANDSCAPERIGHT | ORIENTATION_PORTRAIT | ORIENTATION_PORTRAITUPSIDEDOWN
		};
		
		/*! An exit code to use to exit the Application. \see GameLibrary::Application::close(int)*/
		enum ExitCode
		{
			/*! Exit code used when an Application is already running.*/
			EXITCODE_ALREADYRUNNING = 1,
			/*! Exit code used when the Application finishes running successfully.*/
			EXITCODE_SUCCESS = 0,
			/*! Exit code used when the Application encounters an error.*/
			EXITCODE_ERROR = -1,
			/*! Exit code used when the Application encounters a fatal error.*/
			EXITCODE_FATALERROR = -2,
			/*! Exit code used when the Application is not running inside of the main thread.*/
			EXITCODE_NOTMAINTHREAD = -3,
		};
		
		/*! default constructor*/
		Application();
		/*! Application objects are non-copyable.*/
		Application(const Application&) = delete;
		/*! virtual destructor*/
		virtual ~Application();
		/*! Application objects are non-copyable.*/
		Application& operator=(const Application&) = delete;
		
		
		/*! Called after the Application begins running and creates the Window. Use this function to initialize any modules.*/
		virtual void initialize();
		/*! Called after initialize finishes. Use this function to load any files or assets from the filesystem.
			\param assetManager the Window's AssetManager, used to load resources from the filesystem.*/
		virtual void loadContent(AssetManager*assetManager);
		/*! Called right before the Window closes. Use this function to unload any assets or save any files to the filesystem.
			\param assetManager the Window's AssetManager, used to unload the loaded resources.*/
		virtual void unloadContent(AssetManager*assetManager);
		/*! Called once every frame. Use this function to update or change any values during the frame.
			\param appData specifies information about the Application, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void update(ApplicationData appData);
		/*! Called once every frame. Use this function to draw to the Window.
			\param appData specifies information about the Application, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw to the Window*/
		virtual void draw(ApplicationData appData, Graphics g) const;
		

		/*! Runs the Application. This should only be called once, and not called again until the Application loop ends. This function MUST be run within the main thread.
			\param windowSettings the Window configuration for the Application \see GameLibrary::WindowSettings
			\param orientations the supported interface orientations of the Application. This setting is only used on mobile.
			\returns an integer representing an exit code*/
		int run(const WindowSettings&windowSettings = Window::getDefaultSettings(), int orientations = ORIENTATION_ALL);
		
		
		/*! Closes the running Application with an exit code, which is then returned by Application::run.
			\param exitcode the exit code of the Application.*/
		void close(int exitcode);
		
		
		/*! Sets the refresh rate of the Application in frames per second. This specifies how often update and draw are called.
			\param fps the frame rate of the Application in frames per second*/
		void setFPS(unsigned int fps);
		/*! Gets the refresh rate of the Application in frames per second. This specifies how often update and draw are called.
			\returns the frame rate of the Application in frames per second*/
		unsigned int getFPS();
		/*! Gets the current Window being used by the Application.
			\returns a pointer to the Window object being used by the Application.*/
		Window* getWindow();
		/*! Gets the current elapsed time since the Application's refresh loop began running.
			\returns a reference to a TimeInterval object*/
		TimeInterval& getTime();
		
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
	};
	
	
	/*! An event listener for an Application's events. These events are only used on mobile.*/
	class ApplicationEventListener
	{
	public:
		/*! virtual destructor*/
		virtual ~ApplicationEventListener(){}
		/*! Called when the application is entering the background.
			\param application the current Application.*/
		virtual void onApplicationWillEnterBackground(Application*application){}
		/*! Called when the application has entered the background.
			\param application the current Application.*/
		virtual void onApplicationDidEnterBackground(Application*application){}
		/*! Called when the application is entering the foreground.
			\param application the current Application.*/
		virtual void onApplicationWillEnterForeground(Application*application){}
		/*! Called when the application has entered the foreground.
			\param application the current Application.*/
		virtual void onApplicationDidEnterForeground(Application*application){}
		/*! Called when the OS is terminating the application.
			\param application the current Application.*/
		virtual void onApplicationTerminating(Application*application){}
		/*! Called when the OS is low on memory. This function should be used to free memory that is not being used.*/
		virtual void onApplicationLowMemory(Application*application){}
	};
}