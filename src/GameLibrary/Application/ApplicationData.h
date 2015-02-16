
#pragma once

#include "AssetManager.h"
#include "../Utilities/Geometry/Transform.h"
#include "../Utilities/Time/TimeInterval.h"
#include "../Window/Window.h"

namespace GameLibrary
{
	class Application;
	class Window;
	
	/*! Holds information about an Application, such as the Window or the AssetManager.*/
	class ApplicationData
	{
	public:
		/*! Constructs an ApplicationData object with an Application, Window, AssetManager, elapsed time, View Transform, and framespeed multiplier.
			\param application the Application
			\param window the Application's Window
			\param assetManager the current AssetManager
			\param timeInterval the elapsed time of the Application
			\param transform the view transform of the Application
			\param framespeedMult the frame speed multiplier of the Application*/
		ApplicationData(Application*application, Window*window, AssetManager*assetManager, const TimeInterval&timeInterval, const TransformF&transform, float framespeedMult);
		/*! copy constructor*/
		ApplicationData(const ApplicationData&);
		/*! assignment operator*/
		ApplicationData& operator=(const ApplicationData&);
		
		
		/*! Gets the Application being used.
			\returns an Application pointer*/
		Application* getApplication() const;
		/*! Gets the Window being used.
			\returns a Window pointer*/
		Window* getWindow() const;
		/*! Gets the AssetManager being used.
			\returns an AssetManager pointer*/
		AssetManager* getAssetManager() const;
		/*! Gets the current elapsed time of the Application
			\returns a TimeInterval reference*/
		TimeInterval& getTime();
		/*! Gets the current elapsed time of the Application
			\returns a const TimeInterval reference*/
		const TimeInterval& getTime() const;
		/*! Gets the view transform of the Window
			\returns a Transform reference*/
		TransformF& getTransform();
		/*! Gets the View Transform of the Window
			\returns a const Transform reference*/
		const TransformF& getTransform() const;
		/*! Gets the frame speed multiplier of the Application
			\returns a float value*/
		float getFrameSpeedMultiplier() const;
		
		
		/*! Sets the current Application.
			\param application the Application pointer*/
		void setApplication(Application*application);
		/*! Sets the current Window.
			\param window the Window pointer*/
		void setWindow(Window*window);
		/*! Sets the current AssetManager.
			\param assetManager the AssetManager pointer*/
		void setAssetManager(AssetManager*assetManager);
		/*! Sets the elapsed time of the Application
			\param time a constant TimeInterval reference*/
		void setTime(const TimeInterval&time);
		/*! Sets the current View Transform
			\param transform a const Transform reference*/
		void setTransform(const TransformF&transform);
		
	private:
		Application* application;
		Window* window;
		AssetManager* assetManager;
		TimeInterval timeInterval;
		TransformF transform;
		float framespeedMult;
	};
}