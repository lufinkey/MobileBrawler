
#include "BrawlGame.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	BrawlGame::BrawlGame(const RectangleD&frame, const GameLibrary::Vector2d&natSize) : ScreenElement(frame)
	{
		camera = nullptr; //TODO BrawlGame instantiate Camera
		naturalSize = natSize;
	}
	
	BrawlGame::~BrawlGame()
	{
		//TODO BrawlGame delete camera
	}
	
	void BrawlGame::update(ApplicationData appData)
	{
		for(size_t i=0; i<objects.size(); i++)
		{
			objects.get(i)->update(appData);
		}
	}
	
	void BrawlGame::drawMain(ApplicationData appData, Graphics graphics) const
	{
		ArrayList<GameObject*> objs = objects;
		size_t objects_size = objects.size();
		for(size_t i=0; i<objects_size; i++)
		{
			for(size_t j=1; j<(objects_size-i); j++)
			{
				GameObject*object1 = objs.get(j-1);
				GameObject*object2 = objs.get(j);
				if(object1->getZDepth() > object2->getZDepth())
				{
					objs.set(j-1, object2);
					objs.set(j, object1);
				}
			}
		}
		
		graphics.setClipRect(getFrame());
		camera->updateGraphics(&graphics);
		
		for(size_t i=0; i<objects_size; i++)
		{
			objs.get(i)->draw(appData, graphics);
		}
	}
	
	void BrawlGame::startGame()
	{
		//TODO BrawlGame::startGame
	}
	
	void BrawlGame::stopGame()
	{
		//TODO BrawlGame::stopGame
	}
	
	Camera* BrawlGame::getCamera() const
	{
		return camera;
	}
	
	const Vector2d& BrawlGame::getNaturalSize() const
	{
		return naturalSize;
	}
	
	void BrawlGame::addGameObject(GameObject*object)
	{
		if(object == nullptr)
		{
			throw IllegalArgumentException("object", "null");
		}
		size_t objects_size = objects.size();
		for(size_t i=0; i<objects_size; i++)
		{
			if(object==objects.get(i))
			{
				throw IllegalArgumentException("object", "already contained in BrawlGame");
			}
		}
		objects.add(object);
	}
	
	void BrawlGame::removeGameObject(GameObject*object)
	{
		if(object == nullptr)
		{
			return;
		}
		size_t objects_size = objects.size();
		for(size_t i=0; i<objects_size; i++)
		{
			if(object==objects.get(i))
			{
				objects.remove(i);
				return;
			}
		}
		throw IllegalArgumentException("object", "not contained in BrawlGame");
	}
}
