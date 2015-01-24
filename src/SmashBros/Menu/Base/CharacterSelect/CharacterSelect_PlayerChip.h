
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
				
				bool dragging;
				unsigned int dragTouchID;
				Vector2f dragOffset;
				
			public:
				PlayerChip(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, AssetManager*assetManager);
				virtual ~PlayerChip();
				
				virtual void onMousePress(ApplicationData appData, unsigned int touchID) override;
				virtual void update(ApplicationData appData) override;
				
				void updateDragging(ApplicationData appData, Graphics graphics);
				void grabChip(const ApplicationData&appData, unsigned int touchID);
				void releaseChip();
			};
		}
	}
}
