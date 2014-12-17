
#include "AssetManager.h"
#include "../Utilities/Time/TimeInterval.h"
#include "../Window/Window.h"

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
		AssetManager* assetManager;
		TimeInterval timeInterval;

	public:
		ApplicationData(Application*application, Window*window, AssetManager*assetManager, const TimeInterval&timeInterval);
		ApplicationData(const ApplicationData&);

		ApplicationData& operator=(const ApplicationData&);

		Application* getApplication() const;
		Window* getWindow() const;
		AssetManager* getAssetManager() const;
		TimeInterval& getTime();
		const TimeInterval& getTime() const;
	};

	typedef ApplicationData AppData;
}