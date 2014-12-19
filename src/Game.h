
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
	virtual void loadContent(GameLibrary::AssetManager*assetManager);
	virtual void unloadContent(GameLibrary::AssetManager*assetManager);
	virtual void update(GameLibrary::AppData appData);
	virtual void draw(GameLibrary::AppData appData, GameLibrary::Graphics graphics) const;
};