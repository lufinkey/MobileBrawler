
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
			CharacterSelectScreen(const MenuData&menuData);
			virtual ~CharacterSelectScreen();
			
		protected:
			class CharacterIcon : public SpriteActor
			{
			public:
				CharacterIcon(float x, float y);
				virtual ~CharacterIcon();
			};
			
		private:
			ActorGrid iconGrid;
			ArrayList<CharacterIcon*> icons;

		};
	}
}
