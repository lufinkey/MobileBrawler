
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	class MenuLoadScreen : public fgl::Screen
	{
	public:
		MenuLoadScreen(fgl::AssetManager* assetManager);
		virtual ~MenuLoadScreen();

	protected:
		virtual void onUpdate(const fgl::ApplicationData& appData) override;
	};
}
