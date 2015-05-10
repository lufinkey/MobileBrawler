
#pragma once

#include "../Elements/GameObject.h"

namespace BrawlerLibrary
{
	class Camera
	{
	public:
		typedef enum
		{
			MODE_FIXED,
			MODE_ZOOM,
			MODE_FOLLOW
		} CameraMode;
		
		explicit Camera(BrawlGame*gameInstance);
		Camera(BrawlGame*gameInstance, const GameLibrary::Vector2d&position, double zoom);
		virtual ~Camera();
		
		virtual void update(GameLibrary::ApplicationData appData);
		virtual void updateGraphics(GameLibrary::Graphics*graphics) const;
		
		void addFocusedObject(GameObject*object);
		void removeFocusedObject(GameObject*object);
		
	private:
		static GameLibrary::RectangleD calculateFocusRect(BrawlGame*gameInstance, const GameLibrary::ArrayList<GameObject*>& objects);
		
		BrawlGame* gameInstance;
		
		double x;
		double y;
		double zoom;
		CameraMode mode;
		
		GameLibrary::RectangleD focusRect;
		GameLibrary::ArrayList<GameObject*> focusedObjects;
	};
}
