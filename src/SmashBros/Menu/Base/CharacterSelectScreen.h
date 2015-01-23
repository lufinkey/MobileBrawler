
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
			
			Rules* getRules() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPlayerPanels(const SmashData&smashData);

			virtual void updateItems(ApplicationData appData);
			virtual void drawItems(ApplicationData appData, Graphics graphics) const;

			class CharacterIcon : public SpriteActor
			{
			private:
				CharacterInfo* info;

			public:
				CharacterIcon(CharacterInfo&info, float x, float y, AssetManager*assetManager);
				virtual ~CharacterIcon();
				
				bool equals(const CharacterIcon&) const;
				
				const String& getName() const;
				const String& getCreator() const;
				CharacterInfo* getCharacterInfo() const;
			};
			
			class PlayerPanel : public SpriteActor
			{
			private:
				unsigned int playerNum;
				TextActor* characterName;

				CharacterSelectScreen*charSelectScreen;
			public:
				PlayerPanel(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, float x, float y, AssetManager*assetManager);
				virtual ~PlayerPanel();
				
				virtual void update(ApplicationData appData);
				virtual void draw(ApplicationData appData, Graphics graphics) const;
			};
			
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
			
		private:
			Rules*rules;
			RectangleF iconGridFrame;
			ActorGrid*iconGrid;
			ArrayList<CharacterIcon*> icons;
			ArrayList<PlayerPanel*> panels;
			ArrayList<PlayerChip*> chips;
		};
	}
}
