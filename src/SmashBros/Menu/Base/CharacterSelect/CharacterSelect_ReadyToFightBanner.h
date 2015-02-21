
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
				
				virtual void onMousePress(ApplicationData appData, unsigned int touchID) override;
				virtual void onMouseRelease(ApplicationData appData, unsigned int touchID) override;
			};
		}
	}
}
