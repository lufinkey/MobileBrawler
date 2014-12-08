
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
	virtual void update(const GameLibrary::AppData&appData);
	virtual void draw(const GameLibrary::AppData&appData, GameLibrary::Graphics&g);
};