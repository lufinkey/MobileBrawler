
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class ReadyToFightBanner : public fgl::ButtonElement
			{
				friend class ::SmashBros::Menu::CharacterSelectScreen;
			public:
				ReadyToFightBanner(CharacterSelectScreen* charSelectScreen, fgl::AssetManager* assetManager);

			private:
				CharacterSelectScreen* charSelectScreen;
			};
		}
	}
}
