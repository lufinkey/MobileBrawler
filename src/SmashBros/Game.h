
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "Menu/TitleScreen.h"

namespace SmashBros
{
	class Game : public GameLibrary::Application
	{
	private:
		SmashData* smashData;
		
		AssetManager* menuAssetManager;
		CharacterLoader* characterLoader;
		
		Menu::TitleScreen* titleScreen;
		ScreenManager* menuScreenMgr;

	public:
		Game();
		virtual ~Game();

		virtual void initialize();
		virtual void loadContent(AssetManager*assetManager);
		virtual void unloadContent(AssetManager*assetManager);
		virtual void update(AppData appData);
		virtual void draw(AppData appData, Graphics graphics) const;
		
		void loadMenuAssets(AssetManager*assetManager);
	};
}
