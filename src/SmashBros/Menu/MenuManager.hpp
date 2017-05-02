
#pragma once

#include "MenuLoadScreen.hpp"

namespace SmashBros
{
	class MenuManager : public fgl::ScreenManager
	{
	public:
		MenuManager(fgl::AssetManager* assetManager);
		virtual ~MenuManager();

	private:
		MenuLoadScreen* initialize();

		fgl::AssetManager* assetManager;
		MenuLoadScreen* loadScreen;
	};
}
