
#include "MenuManager.hpp"
#include "Base/BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MenuManager::MenuManager(fgl::AssetManager* parentAssetManager, ModuleManager* moduleManager)
			: ScreenManager(initialize(parentAssetManager, moduleManager)),
			titleScreen(nullptr),
			menuData(nullptr)
		{
			//
		}

		fgl::Screen* MenuManager::initialize(fgl::AssetManager* parentAssetManager, ModuleManager* moduleManager_arg)
		{
			auto window = parentAssetManager->getWindow();
			auto rootDir = parentAssetManager->getRootDirectory();
			rootDir = fgl::FileTools::combinePathStrings(rootDir, "assets/menu");

			assetManager = new fgl::AssetManager(window, rootDir);
			moduleManager = moduleManager_arg;
			emptyScreen = new fgl::Screen();

			return emptyScreen;
		}

		MenuManager::~MenuManager()
		{
			delete emptyScreen;
			if(titleScreen!=nullptr)
			{
				delete titleScreen;
			}
			if(menuData!=nullptr)
			{
				delete menuData;
			}

			delete assetManager;
		}

		void MenuManager::setMenuPath(const MenuPath& menuPath)
		{
			if(getScreens()[0]==emptyScreen)
			{
				throw fgl::IllegalStateException("cannot set the menuPath before the MenuManager has loaded");
			}
			popToFirstScreen(nullptr);
			BaseMenuScreen* screen = static_cast<BaseMenuScreen*>(getScreens()[0]);
			for(auto& pathElement : menuPath)
			{
				screen->setState(pathElement.state);
				if(pathElement.nextScreen.length() != 0)
				{
					auto nextScreen = screen->getScreen(pathElement.nextScreen);
					if(nextScreen==nullptr)
					{
						size_t screenIndex = (getScreens().size()-1);
						throw fgl::IllegalArgumentException("menuPath", (fgl::String)"screen at index "+screenIndex+" does not have a screen with the name \""+pathElement.nextScreen+"\"");
					}
					screen->goToScreen(pathElement.nextScreen, nullptr);
					screen = nextScreen;
				}
			}
		}

		MenuPath MenuManager::getMenuPath() const
		{
			if(getScreens()[0]==emptyScreen)
			{
				return MenuPath();
			}

			MenuPath menuPath;
			auto& screens = getScreens();
			menuPath.reserve(screens.size());
			size_t screenIndex = 0;
			for(auto screen : screens)
			{
				auto menuScreen = static_cast<BaseMenuScreen*>(screen);
				MenuPathElement pathElement;
				if(screenIndex < (screens.size()-1))
				{
					auto nextScreen = screens[screenIndex+1];
					for(auto& screenPair : menuScreen->getScreens())
					{
						if(screenPair.second==nextScreen)
						{
							pathElement.nextScreen = screenPair.first;
							break;
						}
					}
				}
				pathElement.state = menuScreen->getState();
				menuPath.add(pathElement);
				screenIndex++;
			}
			return menuPath;
		}

		void MenuManager::load()
		{
			if(menuData!=nullptr)
			{
				return;
			}

			//TODO add some sort of loading animation or some shit idk
			moduleManager->loadAssets();
			menuData = new MenuData(assetManager, moduleManager);
			titleScreen = new TitleScreen(menuData);

			setScreens({titleScreen}, nullptr);
		}

		void MenuManager::unload()
		{
			if(menuData==nullptr)
			{
				return;
			}

			delete titleScreen;
			titleScreen = nullptr;
			delete menuData;
			menuData = nullptr;
			moduleManager->unloadAssets();

			setScreens({emptyScreen}, nullptr);
		}
	}
}
