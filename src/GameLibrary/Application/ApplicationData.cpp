
#include "ApplicationData.h"

namespace GameLibrary
{
	ApplicationData::ApplicationData(Application*app, Window*win, AssetManager*assetMgr, const TimeInterval&time)
	{
		application = app;
		window = win;
		assetManager = assetMgr;
		timeInterval = time;
	}

	ApplicationData::ApplicationData(const ApplicationData&appdata)
	{
		application = appdata.application;
		window = appdata.window;
		assetManager = appdata.assetManager;
		timeInterval = appdata.timeInterval;
	}

	ApplicationData& ApplicationData::operator=(const ApplicationData&appdata)
	{
		application = appdata.application;
		window = appdata.window;
		assetManager = appdata.assetManager;
		timeInterval = appdata.timeInterval;

		return *this;
	}

	Application* ApplicationData::getApplication() const
	{
		return application;
	}

	Window* ApplicationData::getWindow() const
	{
		return window;
	}

	AssetManager* ApplicationData::getAssetManager() const
	{
		return assetManager;
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