
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "TitleScreen.hpp"
#include "MenuData/MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		struct MenuPathElement
		{
			fgl::String nextScreen;
			fgl::Dictionary state;
		};

		typedef fgl::ArrayList<MenuPathElement> MenuPath;

		class MenuManager : public fgl::ScreenManager
		{
		public:
			MenuManager(fgl::AssetManager* parentAssetManager, ModuleManager* moduleManager);
			virtual ~MenuManager();

			void load();
			void unload();

			void setMenuPath(const MenuPath& menuPath);
			MenuPath getMenuPath() const;

		private:
			fgl::Screen* initialize(fgl::AssetManager* parentAssetManager, ModuleManager* moduleManager);

			fgl::AssetManager* assetManager;
			ModuleManager* moduleManager;

			fgl::Screen* emptyScreen;
			TitleScreen* titleScreen;

			MenuData* menuData;
		};
	}
}
