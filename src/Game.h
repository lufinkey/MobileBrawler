
#include "GameLibrary/GameLibrary.h"

#pragma once

class Game : public GameLibrary::Application
{
public:
	Game();
	virtual ~Game();

	virtual void initialize();
	virtual void loadContent();
	virtual void unloadContent();
	virtual void update(GameLibrary::AppData appData);
	virtual void draw(GameLibrary::AppData appData, GameLibrary::Graphics g);
};