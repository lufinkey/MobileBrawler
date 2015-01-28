
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	using namespace BrawlerLibrary;

	namespace Menu
	{
		namespace CharacterSelect
		{
			class CharacterIcon : public SpriteActor
			{
			private:
				CharacterInfo* info;

			public:
				CharacterIcon(CharacterInfo&info, float x, float y, AssetManager*assetManager);
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