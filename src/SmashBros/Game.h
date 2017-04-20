
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "Menu/TitleScreen.h"
#include "Load/MenuLoad.h"
#include "Load/ModuleLoad.h"

namespace SmashBros
{
	using namespace fgl;
	
	class Game : public fgl::Application
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
		virtual void update(ApplicationData appData) override;
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
	};
}
