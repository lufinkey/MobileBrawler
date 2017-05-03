
#include "MenuManager.hpp"

namespace SmashBros
{
	MenuManager::MenuManager(fgl::AssetManager* assetManager_arg)
		: ScreenManager(initialize(assetManager_arg))
	{
		//
	}

	MenuLoadScreen* MenuManager::initialize(fgl::AssetManager* assetManager_arg)
	{
		auto window = assetManager_arg->getWindow();
		auto rootDir = assetManager_arg->getRootDirectory();
		rootDir = fgl::FileTools::combinePathStrings(rootDir, "assets/menu");
		assetManager = new fgl::AssetManager(window, rootDir);
		loadScreen = new MenuLoadScreen(assetManager);
		return loadScreen;
	}

	MenuManager::~MenuManager()
	{
		delete loadScreen;
		delete assetManager;
	}
}
