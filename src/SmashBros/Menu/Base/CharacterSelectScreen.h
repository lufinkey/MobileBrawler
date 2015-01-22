
#pragma once

#include "BaseMenuScreen.h"
#include "../Elements/ActorGrid.h"

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen : public BaseMenuScreen
		{
		public:
			CharacterSelectScreen(const SmashData&smashData);
			virtual ~CharacterSelectScreen();
			
			void setPlayerCount(unsigned int count);
			
		protected:
			SmashData const* smashData;
			
			void reloadIcons(const SmashData&smashData);
			void reloadPlayerPanels(const SmashData&smashData);

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
			
			class PlayerPanel : public SpriteActor
			{
			private:
				unsigned int playerNum;
				CharacterSelectScreen*charSelectScreen;
			public:
				PlayerPanel(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, AssetManager*assetManager);
				virtual ~PlayerPanel();
			};
			
			class PlayerChip : public SpriteActor
			{
			private:
				unsigned int playerNum;
				CharacterSelectScreen*charSelectScreen;
			public:
				PlayerChip(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, AssetManager*assetManager);
				virtual ~PlayerChip();
			};
			
		private:
			unsigned int playerCount;
			
			RectangleF iconGridFrame;
			ActorGrid*iconGrid;
			ArrayList<CharacterIcon*> icons;
			ArrayList<PlayerPanel*> panels;
			ArrayList<PlayerChip*> chips;
		};
	}
}
