
#include "Camera.h"
#include "../BrawlGame.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	Camera::Camera(BrawlGame*gameInst) : Camera(gameInst, Vector2d(0, 0), 1)
	{
		//
	}
	
	Camera::Camera(BrawlGame*gameInst, const Vector2d&pos, double z)
	{
		gameInstance = gameInst;
		x = pos.x;
		y = pos.y;
		zoom = z;
		mode = Camera::MODE_ZOOM;
	}
	
	Camera::~Camera()
	{
		//
	}
	
	void Camera::update(ApplicationData appData)
	{
		//TODO Camera::update
		switch(mode)
		{
			case Camera::MODE_FIXED:
			{
				//TODO Camera::update MODE_FIXED
			}
			break;
			
			case Camera::MODE_ZOOM:
			{
				//TODO Camera::update MODE_ZOOM
			}
			break;
			
			case Camera::MODE_FOLLOW:
			{
				//TODO Camera::update MODE_FOLLOW
			}
			break;
		}
	}
	
	void Camera::updateGraphics(Graphics*graphics) const
	{
		//TODO Camera::updateGraphics
	}
	
	void Camera::addFocusedObject(GameObject*object)
	{
		if(object == nullptr)
		{
			throw IllegalArgumentException("object", "cannot be null");
		}
		if(!focusedObjects.contains(object))
		{
			focusedObjects.add(object);
		}
	}
	
	void Camera::removeFocusedObject(GameObject*object)
	{
		if(object == nullptr)
		{
			return;
		}
		else
		{
			size_t index = focusedObjects.indexOf(object);
			if(index != ARRAYLIST_NOTFOUND)
			{
				focusedObjects.remove(index);
			}
		}
	}
	
	RectangleD Camera::calculateFocusRect(BrawlGame*gameInstance, const GameLibrary::ArrayList<GameObject*>& objects)
	{
		if(gameInstance == nullptr)
		{
			throw IllegalArgumentException("gameInstance", "cannot be null");
		}
		size_t objects_size = objects.size();
		if(objects_size == 0)
		{
			const Vector2d& naturalSize = gameInstance->getNaturalSize();
			return RectangleD(-(naturalSize.x/2), -(naturalSize.y/2), naturalSize.x, naturalSize.y);
		}
		else
		{
			RectangleD focusRect = objects.get(0)->getFrame();
			for(size_t i=1; i<objects_size; i++)
			{
				GameObject* object = objects.get(i);
				if(object == nullptr)
				{
					throw IllegalArgumentException("objects", "cannot contain null object");
				}
				focusRect.combine(object->getFrame());
			}
			return focusRect;
		}
	}
}
