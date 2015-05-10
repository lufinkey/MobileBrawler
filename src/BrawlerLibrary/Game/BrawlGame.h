
#pragma once

#include "Utilities/Camera.h"

namespace BrawlerLibrary
{
	class BrawlGame : GameLibrary::ScreenElement
	{
	public:
		explicit BrawlGame(const GameLibrary::RectangleD&frame, const GameLibrary::Vector2d&naturalSize=GameLibrary::Vector2d(900,600));
		virtual ~BrawlGame();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void drawMain(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
		
		virtual void startGame();
		virtual void stopGame();
		
		Camera* getCamera() const;
		const GameLibrary::Vector2d& getNaturalSize() const;
		
		void addGameObject(GameObject*object);
		void removeGameObject(GameObject*object);
		
	private:
		Camera* camera;
		GameLibrary::Vector2d naturalSize;
		
		GameLibrary::ArrayList<GameObject*> objects;
	};
}
