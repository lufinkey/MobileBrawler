
#include "ApplicationData.h"

namespace GameLibrary
{
	ApplicationData::ApplicationData(Application*app, Window*win, const TimeInterval&time)
	{
		application = app;
		window = win;
		timeInterval = time;
	}

	ApplicationData::ApplicationData(const ApplicationData&appdata)
	{
		application = appdata.application;
		window = appdata.window;
		timeInterval = appdata.timeInterval;
	}

	Application* ApplicationData::getApplication() const
	{
		return application;
	}

	Window* ApplicationData::getWindow() const
	{
		return window;
	}

	TimeInterval& ApplicationData::getTime()
	{
		return timeInterval;
	}

	const TimeInterval& ApplicationData::getTime() const
	{
		return timeInterval;
	}
}