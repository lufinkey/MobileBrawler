
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
				WireframeActor* tapRegion_mode;
				
				CharacterSelectScreen*charSelectScreen;
				
				void applyProperties(const Dictionary&properties);
				
			protected:
				AutoLayout autoLayout;
				
				static void applyPlacementDict(RectF*bounds, const Dictionary&dict);
				
			public:
				PlayerPanel(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, const Dictionary&properties, AssetManager*assetManager);
				virtual ~PlayerPanel();
				
				virtual void updateSize() override;
				
				virtual void update(ApplicationData appData) override;
				virtual void draw(ApplicationData appData, Graphics graphics) const override;
				
				unsigned int getPlayerNum() const;
				
				void applyCharacterInfo(CharacterInfo*characterInfo);
			};
		}
	}
}
