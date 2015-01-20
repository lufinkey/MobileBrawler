
#pragma once

#include "BaseMenuScreen.h"
#include "Elements/ActorGrid.h"

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen : public BaseMenuScreen
		{
		public:
			CharacterSelectScreen(const SmashData&smashData);
			virtual ~CharacterSelectScreen();
			
			void reloadIcons(const SmashData&smashData);
			
		protected:
			virtual void updateItems(ApplicationData appData);
			virtual void drawItems(ApplicationData appData, Graphics graphics) const;

			class CharacterIcon : public SpriteActor
			{
			private:
				CharacterInfo const* info;

			public:
				CharacterIcon(const CharacterInfo&info, float x, float y, AssetManager*assetManager);
				virtual ~CharacterIcon();
				
				bool equals(const CharacterIcon&) const;
				
				const String& getName() const;
				const String& getCreator() const;
			};
			
			class PlayerChip : public SpriteActor
			{
			public:
				PlayerChip(float x, float y);
				virtual ~PlayerChip();
			};
			
			class PlayerPanel : public SpriteActor
			{
			public:
				PlayerPanel(float x, float y);
				virtual ~PlayerPanel();
			};
			
		private:
			ActorGrid*iconGrid;
			ArrayList<CharacterIcon*> icons;
		};
	}
}
