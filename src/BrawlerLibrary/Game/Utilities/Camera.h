
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
		Camera(BrawlGame*gameInstance, const fgl::Vector2d&position, double zoom);
		virtual ~Camera();
		
		virtual void update(fgl::ApplicationData appData);
		virtual void updateGraphics(fgl::Graphics*graphics) const;
		
		void addFocusedObject(GameObject*object);
		void removeFocusedObject(GameObject*object);
		
	private:
		static fgl::RectangleD calculateFocusRect(BrawlGame*gameInstance, const fgl::ArrayList<GameObject*>& objects);
		
		BrawlGame* gameInstance;
		
		double x;
		double y;
		double zoom;
		CameraMode mode;
		
		fgl::RectangleD focusRect;
		fgl::ArrayList<GameObject*> focusedObjects;
	};
}
