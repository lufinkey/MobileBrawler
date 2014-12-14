
#include "GameLibrary/GameLibrary.h"

#pragma once

class Game : public GameLibrary::Application
{
private:
	GameLibrary::Screen* rootScrn;
	GameLibrary::ScreenManager* screenMgr;
public:
	Game();
	virtual ~Game();

	virtual void initialize();
	virtual void loadContent();
	virtual void unloadContent();
	virtual void update(GameLibrary::AppData appData);
	virtual void draw(GameLibrary::AppData appData, GameLibrary::Graphics graphics);
};