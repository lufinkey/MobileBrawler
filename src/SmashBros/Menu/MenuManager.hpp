
#pragma once

#include "MenuLoadScreen.hpp"

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
			MenuManager(fgl::AssetManager* assetManager);
			virtual ~MenuManager();

			void setMenuPath(const MenuPath& menuPath);
			MenuPath getMenuPath() const;

		private:
			MenuLoadScreen* initialize(fgl::AssetManager* assetManager_arg);

			fgl::AssetManager* assetManager;
			MenuLoadScreen* loadScreen;
		};
	}
}
