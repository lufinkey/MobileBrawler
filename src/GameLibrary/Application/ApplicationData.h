
#include "../Utilities/Time/TimeInterval.h"

#pragma once

namespace GameLibrary
{
	class Application;
	class Window;

	class ApplicationData
	{
	private:
		Application* application;
		Window* window;
		TimeInterval timeInterval;

	public:
		ApplicationData(Application*application,Window*window,const TimeInterval&timeInterval);
		ApplicationData(const ApplicationData&);

		Application* getApplication() const;
		Window* getWindow() const;
		TimeInterval& getTime();
		const TimeInterval& getTime() const;
	};

	typedef ApplicationData AppData;
}