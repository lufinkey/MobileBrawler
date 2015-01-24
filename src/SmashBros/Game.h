
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "Menu/TitleScreen.h"

namespace SmashBros
{
	using namespace GameLibrary;
	
	class Game : public GameLibrary::Application
	{
	private:
		SmashData* smashData;
		
		AssetManager* menuAssetManager;
		CharacterLoader* characterLoader;
		
		Menu::TitleScreen* titleScreen;
		ScreenManager* menuScreenMgr;
		
		Image characterselect_iconmask;

	public:
		Game();
		virtual ~Game();

		virtual void initialize() override;
		virtual void loadContent(AssetManager*assetManager) override;
		virtual void unloadContent(AssetManager*assetManager) override;
		virtual void update(AppData appData) override;
		virtual void draw(AppData appData, Graphics graphics) const override;
		
		void loadMenuAssets(AssetManager*assetManager);
	};
}
