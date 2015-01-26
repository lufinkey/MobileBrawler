
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "Menu/TitleScreen.h"
#include "Load/MenuLoad.h"
#include "Load/ModuleLoad.h"

namespace SmashBros
{
	using namespace GameLibrary;
	
	class Game : public GameLibrary::Application
	{
	private:
		SmashData* smashData;
		MenuLoad* menuLoad;
		ModuleLoad* moduleLoad;

		Menu::TitleScreen* titleScreen;
		ScreenManager* menuScreenMgr;
		
	public:
		Game();
		virtual ~Game();

		virtual void initialize() override;
		virtual void loadContent(AssetManager*assetManager) override;
		virtual void unloadContent(AssetManager*assetManager) override;
		virtual void update(AppData appData) override;
		virtual void draw(AppData appData, Graphics graphics) const override;
	};
}
