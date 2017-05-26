
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "Menu/MenuManager.hpp"

namespace SmashBros
{
	class Game : public fgl::Application
	{
	public:
		Game();
		virtual ~Game();

		virtual void initialize() override;
		virtual void loadContent(fgl::AssetManager*assetManager) override;
		virtual void unloadContent(fgl::AssetManager*assetManager) override;
		virtual void update(fgl::ApplicationData appData) override;
		virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;

	private:
		ModuleManager* moduleManager;

		fgl::ScreenManager* screenManager;
		Menu::MenuManager* menuManager;
	};
}
