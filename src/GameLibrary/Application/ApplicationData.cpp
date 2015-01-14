
#include "ApplicationData.h"
#include "Application.h"

namespace GameLibrary
{
	ApplicationData::ApplicationData(Application*app, Window*win, AssetManager*assetMgr, const TimeInterval&time, const Transform&transfrm, float fpsMult)
	{
		application = app;
		window = win;
		assetManager = assetMgr;
		timeInterval = time;
		transform = transfrm;
		framespeedMult = fpsMult;
	}

	ApplicationData::ApplicationData(const ApplicationData&appdata)
	{
		application = appdata.application;
		window = appdata.window;
		assetManager = appdata.assetManager;
		timeInterval = appdata.timeInterval;
		transform = appdata.transform;
		framespeedMult = appdata.framespeedMult;
	}

	ApplicationData& ApplicationData::operator=(const ApplicationData&appdata)
	{
		application = appdata.application;
		window = appdata.window;
		assetManager = appdata.assetManager;
		timeInterval = appdata.timeInterval;
		transform = appdata.transform;
		framespeedMult = appdata.framespeedMult;

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

	Transform& ApplicationData::getTransform()
	{
		return transform;
	}

	const Transform& ApplicationData::getTransform() const
	{
		return transform;
	}
	
	float ApplicationData::getFrameSpeedMultiplier() const
	{
		return framespeedMult;
	}

	void ApplicationData::setApplication(Application*app)
	{
		application = app;
	}

	void ApplicationData::setWindow(Window*win)
	{
		window = win;
	}

	void ApplicationData::setAssetManager(AssetManager*assetMgr)
	{
		assetManager = assetMgr;
	}

	void ApplicationData::setTime(const TimeInterval&time)
	{
		timeInterval = time;
	}

	void ApplicationData::setTransform(const Transform&transfrm)
	{
		transform = transfrm;
	}
}