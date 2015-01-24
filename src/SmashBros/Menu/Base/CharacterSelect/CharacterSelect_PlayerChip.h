
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
			class PlayerChip : public SpriteActor
			{
			private:
				unsigned int playerNum;
				CharacterSelectScreen*charSelectScreen;
				unsigned int dragTouchID;
				bool dragging;
				
			public:
				PlayerChip(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, AssetManager*assetManager);
				virtual ~PlayerChip();
				virtual void onMousePress(Window*window, unsigned int touchID);
				virtual void update(ApplicationData appData);
			};
		}
	}
}
