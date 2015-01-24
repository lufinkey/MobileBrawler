
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
			class PlayerPanel : public SpriteActor
			{
			private:
				unsigned int playerNum;
				
				SpriteActor* portrait;
				Animation* portrait_anim;
				SpriteActor* overlay;
				TextActor* namebox;
				WireframeActor* tapRegion;
				
				CharacterSelectScreen*charSelectScreen;
				
				RectF portrait_bounds;
				RectF overlay_bounds;
				RectF namebox_bounds;
				
				static void applyPlacementDict(RectF*bounds, const Dictionary&dict);
				static RectangleF getPlacementFrame(const RectangleF&container, const RectF&bounds);
				
			public:
				PlayerPanel(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, const Dictionary&placementDict, AssetManager*assetManager);
				virtual ~PlayerPanel();
				
				virtual void update(ApplicationData appData);
				virtual void draw(ApplicationData appData, Graphics graphics) const;
				
				unsigned int getPlayerNum() const;
				
				void applyPlacementProperties(const Dictionary&placementDict);
				void applyCharacterInfo(CharacterInfo*characterInfo);
			};
		}
	}
}
