
#pragma once

#include "Utilities/Camera.h"

namespace BrawlerLibrary
{
	class BrawlGame : fgl::ScreenElement
	{
	public:
		explicit BrawlGame(const fgl::RectangleD&frame, const fgl::Vector2d&naturalSize=fgl::Vector2d(900,600));
		virtual ~BrawlGame();
		
		virtual void update(fgl::ApplicationData appData) override;
		virtual void drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
		
		virtual void startGame();
		virtual void stopGame();
		
		Camera* getCamera() const;
		const fgl::Vector2d& getNaturalSize() const;
		
		void addGameObject(GameObject*object);
		void removeGameObject(GameObject*object);
		
	private:
		Camera* camera;
		fgl::Vector2d naturalSize;
		
		fgl::ArrayList<GameObject*> objects;
	};
}
