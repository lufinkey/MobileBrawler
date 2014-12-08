
#include "../Utilities/Time/TimeInterval.h"

#pragma once

namespace GameLibrary
{
	class Application;
	class Window;

	class ApplicationData
	{
		friend class Application;
	private:
		Application* application;
		Window* window;
		TimeInterval timeInterval;

		ApplicationData(Application*application,Window*window,const TimeInterval&timeInterval);

	public:
		ApplicationData(const ApplicationData&);

		Application* getApplication() const;
		Window* getWindow() const;
		const TimeInterval& getTime() const;
	};

	typedef ApplicationData AppData;
}