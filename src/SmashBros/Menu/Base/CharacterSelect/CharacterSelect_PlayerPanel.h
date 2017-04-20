
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include <BrawlerLibrary/BrawlerLibrary.h>

using namespace fgl;
using namespace BrawlerLibrary;

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class PlayerPanel : public SpriteActor
			{
				friend class ::SmashBros::Menu::CharacterSelectScreen;
			private:
				unsigned int playerNum;
				
				AutoLayoutManager autoLayoutMgr;
				
				SpriteActor* portrait;
				Animation* portrait_anim;
				SpriteActor* overlay;
				TextActor* namebox;
				WireframeActor* tapRegion_mode;
				
				CharacterSelectScreen*charSelectScreen;
				
				void applyProperties(const Dictionary&properties);
				
			protected:
				AutoLayoutManager portraitLayoutMgr;
				AutoLayoutManager overlayLayoutMgr;
				AutoLayoutManager nameboxLayoutMgr;
				
				static void applyPlacementDict(const Dictionary&dict, AutoLayoutManager*layoutMgr);
				
			public:
				PlayerPanel(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, double x, double y, const Dictionary&properties, AssetManager*assetManager);
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
