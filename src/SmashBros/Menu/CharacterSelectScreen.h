
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
			
		protected:
			class CharacterIcon : public SpriteActor
			{
			public:
				CharacterIcon(float x, float y);
				virtual ~CharacterIcon();
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
			ActorGrid iconGrid;
			ArrayList<CharacterIcon*> icons;
		};
	}
}
