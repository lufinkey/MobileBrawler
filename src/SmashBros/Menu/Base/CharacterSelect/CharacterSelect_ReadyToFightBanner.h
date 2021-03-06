
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

using namespace GameLibrary;
using namespace BrawlerLibrary;

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class ReadyToFightBanner : public SpriteActor
			{
				friend class ::SmashBros::Menu::CharacterSelectScreen;
			private:
				CharacterSelectScreen* charSelectScreen;
				AutoLayoutManager autoLayoutMgr;
				bool selected;
				
			public:
				ReadyToFightBanner(CharacterSelectScreen*charSelectScreen, double x, double y, AssetManager*assetManager);
				
				virtual void update(ApplicationData appData) override;
				
				virtual void onMousePress(const ActorMouseEvent& evt) override;
				virtual void onMouseRelease(const ActorMouseEvent& evt) override;
			};
		}
	}
}
