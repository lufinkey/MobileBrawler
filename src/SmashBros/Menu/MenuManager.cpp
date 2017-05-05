
#include "MenuManager.hpp"
#include "Base/BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
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

		void MenuManager::setMenuPath(const MenuPath& menuPath)
		{
			popToRoot(nullptr);
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
					screen->goToScreen(pathElement.nextScreen, false);
					screen = nextScreen;
				}
			}
		}

		MenuPath MenuManager::getMenuPath() const
		{
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
	}
}
