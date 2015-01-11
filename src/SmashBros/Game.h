
#include <GameLibraryImport.hpp>

#pragma once

namespace SmashBros
{
	class Game : public GameLibrary::Application
	{
	private:
		Screen* rootScrn;
		ScreenManager* screenMgr;
		Actor* actor;
		TextActor* textActor;
		WireframeActor* wireframeActor;

	public:
		Game();
		virtual ~Game();

		virtual void initialize();
		virtual void loadContent(AssetManager*assetManager);
		virtual void unloadContent(AssetManager*assetManager);
		virtual void update(AppData appData);
		virtual void draw(AppData appData, Graphics graphics) const;
	};
}
