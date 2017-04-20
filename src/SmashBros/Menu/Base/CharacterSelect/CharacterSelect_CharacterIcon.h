
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
			class CharacterIcon : public SpriteActor
			{
				friend class ::SmashBros::Menu::CharacterSelectScreen;
			private:
				CharacterInfo* info;
				AutoLayoutManager autoLayoutMgr;

			public:
				CharacterIcon(CharacterInfo&info, double x, double y, AssetManager*assetManager);
				virtual ~CharacterIcon();
				
				virtual void draw(ApplicationData appData, Graphics graphics) const override;
				
				bool equals(const CharacterIcon&) const;
				
				const String& getName() const;
				const String& getCreator() const;
				CharacterInfo* getCharacterInfo() const;
			};
		}
	}
}
