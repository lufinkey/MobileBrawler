
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
			CharacterLoader* getCharacterLoader() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPlayerPanels(const SmashData&smashData);

			virtual void updateItems(ApplicationData appData);
			virtual void drawItems(ApplicationData appData, Graphics graphics) const;
			
		private:
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
			
			void whenPlayerCharacterChanges(unsigned int playerNum, CharacterInfo*characterInfo);

			Rules*rules;
			CharacterLoader* characterLoader;
			RectangleF iconGridFrame;
			ActorGrid*iconGrid;
			ArrayList<CharacterIcon*> icons;
			ArrayList<PlayerPanel*> panels;
			ArrayList<PlayerChip*> chips;
		};
	}
}
