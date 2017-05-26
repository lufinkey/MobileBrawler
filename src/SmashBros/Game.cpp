
#include "Game.hpp"

namespace SmashBros
{
	Game::Game()
	{
		moduleManager = nullptr;
		menuManager = nullptr;
		screenManager = nullptr;
		fgl::Graphics::setDefaultFontPath("assets/fonts/default.ttf");
	}
	
	Game::~Game()
	{
		if(screenManager!=nullptr)
		{
			delete screenManager;
		}
		if(menuManager!=nullptr)
		{
			delete menuManager;
		}
		if(moduleManager!=nullptr)
		{
			delete moduleManager;
		}
	}
	
	void Game::initialize()
	{
		getWindow()->getViewport()->setMatchesWindow(true);
		setFPS(60);
	}
	
	void Game::loadContent(fgl::AssetManager* assetMgr)
	{
		auto rootDir = assetMgr->getRootDirectory();
		auto assetsRoot = fgl::FileTools::combinePathStrings(rootDir, "assets");
		auto window = getWindow();

		moduleManager = new ModuleManager(window, assetsRoot);
		menuManager = new Menu::MenuManager(assetMgr, moduleManager);
		screenManager = new fgl::ScreenManager(window, menuManager);

		menuManager->load();
	}
	
	void Game::unloadContent(fgl::AssetManager* assetMgr)
	{
		//
	}
	
	void Game::update(fgl::ApplicationData appData)
	{
		screenManager->update(appData);
	}
	
	void Game::draw(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		screenManager->draw(appData, graphics);
	}
}
