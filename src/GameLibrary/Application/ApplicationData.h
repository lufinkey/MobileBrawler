
#pragma once

#include "AssetManager.h"
#include "../Utilities/Geometry/Transform.h"
#include "../Utilities/Time/TimeInterval.h"
#include "../Window/Window.h"

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
		Transform transform;
		float framespeedMult;

	public:
		ApplicationData(Application*application, Window*window, AssetManager*assetManager, const TimeInterval&timeInterval, const Transform&transform, float framespeedMult);
		ApplicationData(const ApplicationData&);

		ApplicationData& operator=(const ApplicationData&);

		Application* getApplication() const;
		Window* getWindow() const;
		AssetManager* getAssetManager() const;
		TimeInterval& getTime();
		const TimeInterval& getTime() const;
		Transform& getTransform();
		const Transform& getTransform() const;
		float getFrameSpeedMultiplier() const;

		void setApplication(Application*application);
		void setWindow(Window*window);
		void setAssetManager(AssetManager*assetManager);
		void setTime(const TimeInterval&time);
		void setTransform(const Transform&transform);
	};

	typedef ApplicationData AppData;
}