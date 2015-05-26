
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	using namespace BrawlerLibrary;
	
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class ReadyToFightBanner : public SpriteActor
			{
			private:
				CharacterSelectScreen* charSelectScreen;
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
